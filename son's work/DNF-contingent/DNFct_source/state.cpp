#include "state.h"
#include "planner.h"

/*****************State for Heuristic*************************/

StateH::StateH(boost::dynamic_bitset<>& L)
{   
  m_L = L;
}
  
StateH::~StateH()
{
  
}

/* operators */
int StateH::operator<(const StateH& s) const {	
	return (m_L < s.m_L);  
}

bool StateH::operator==(const StateH& s) const {
  return m_L == s.m_L;
}

StateH StateH::operator=(const StateH& s) {
  m_L = s.m_L;
  m_EF = s.m_EF;

  return *this;
}

/* other functions */
bool StateH::includes(const boost::dynamic_bitset<>& x) const
{
	return x.is_subset_of(m_L);
}

bool StateH::includes(const StateH* s) const
{
  return this->includes(s->m_L);
}

bool StateH::satisfies(const Literals* x) const
{
  Literals::const_iterator it;
  for (it = x->begin(); it != x->end(); it++) {
    if (m_L[*it])
      return true;
  }
  return false;
}


bool StateH::will_include(const Literals* x, const boost::dynamic_bitset<>& L) const
{	
	Literals::const_iterator it;
		for (it = x->begin(); it != x->end(); it++) {
			if ( !(m_L[*it] || L[*it] || m_EF.count(*it)) )
				return false;
		}

	return true;
}


void StateH::insert(const Literals& x)
{
  Literals::const_iterator it;
  for (it = x.begin(); it != x.end(); it++) {
	  if (!m_L[*it])
		m_L[*it] = 1;
  }  
}


bool StateH::intersect(const boost::dynamic_bitset<>& x) const
{
	return (m_L&x).any();
}


/*************************************************************************
 * State Implementation
 *************************************************************************/
State::State(Planner* planner)
{ 
  m_planner = planner;
  m_L.resize(planner->m_literals.size());
  m_hvalue = -1;
  m_gsatisfied = -1;  
  m_hash = -1;
  m_allocated = false;
}
  
State::~State()
{
  
}

void State::clear()
{
  m_hvalue = -1;
  m_gsatisfied = -1;
  m_hash = -1;
  m_L.reset();
}

/* operators */
int State::operator<(const State& s) const {	
	return (m_L < s.m_L);  
}

bool State::operator==(const State& s) const {
  return m_L == s.m_L;
}

State State::operator=(const State& s) {
  m_L = s.m_L;  
  m_planner = s.m_planner;
  m_hvalue = s.m_hvalue;
  m_gsatisfied = s.m_gsatisfied;
  
  return *this;
}

/* other functions */
bool State::is_consistent() const
{
  if ((m_L&(m_L >> 1)).any())
      return false;
  return true;
}

int State::hvalue()
{ 
  if (m_hvalue == -1) {
	Literals::iterator it;
	vector<Literals>::const_iterator its;
	
	m_hvalue = 0;

	for (its = m_planner->m_gd.begin(); its != m_planner->m_gd.end(); its++) {
		if (this->intersect(&(*its)))
			m_hvalue++;
	}
	m_hvalue *= 100;

	m_hvalue += (m_L & m_planner->m_goal).count();

  }

  return m_hvalue;
}

int State::hgvalue()
{ 
  if (m_hvalue == -1) {	
	m_hvalue = (m_L & m_planner->m_goal).count();
  }
  return m_hvalue;
}

int State::hash()
{
  if (m_hash == -1) {    	
	unsigned int l;
	unsigned int hash = 0;
	
	for (l = 0; l < m_L.size(); ) {	
		if (m_L[l])		
			hash += (++l)*l;
		else
			l++;
	}
	m_hash = hash & HASH_BITS;
  }  

  return m_hash;
}


bool State::satisfies(const Literals* x)
{
  Literals::const_iterator it;
  for (it = x->begin(); it != x->end(); it++) {
    if (m_L[*it])
      return true;
  }
  return false;
}

bool State::satisfies(const Literal l)
{  
  if (m_L[l])
      return true;  
  return false;
}

/*
bool State::goal_satisfied() 
{
  set<Literals>::const_iterator it;

  if (m_gsatisfied != -1)
    return m_gsatisfied == 1;

  // goal satisfaction has not been checked
  for (it = (m_planner->m_gd).begin();
       it != (m_planner->m_gd).end(); it++) {
    if (!satisfies(&(*it))) {
      m_gsatisfied = 0;
      return false;
    }
  }

  m_gsatisfied = 1;
  return true;
}
*/


//Below will be used for heuristics also
 
bool State::goal_satisfied() 
{
	if (m_gsatisfied != -1)
		return (m_gsatisfied == m_planner->m_gd.size());
	m_gd_sat.resize(m_planner->m_gd.size());
	vector<Literals>::const_iterator it;
	int i;

	m_gsatisfied = 0;
	//goal satisfaction has not been checked
	for (it = (m_planner->m_gd).begin(), i=0; it != (m_planner->m_gd).end(); it++, i++) {
		if (satisfies(&(*it))) {
			m_gsatisfied++;
			m_gd_sat[i] = 1;
		}
	}
  
	return (m_gsatisfied == m_planner->m_gd.size());
}


bool State::intersect(const Literals* x) const
{
  Literals::const_iterator it_x;

  for (it_x = x->begin(); it_x != x->end(); it_x++) {
    if (m_L[*it_x])
      return true;
  }
  return false;
}

bool State::intersect(const boost::dynamic_bitset<>& x) const
{
	return (m_L&x).any();
}

bool State::intersect(const State* s) const
{
  return intersect(s->m_L);
}

bool State::includes(const Literals* x) const
{
  Literals::const_iterator it_x;

  for (it_x = x->begin(); it_x != x->end(); it_x++) {
	  if (!m_L[*it_x])
		  return false;
  }
  return true;
}

bool State::includes(const boost::dynamic_bitset<>& x) const
{
	return x.is_subset_of(m_L);
}


bool State::includes(const State* s) const
{
  return this->includes(s->m_L);
}

void State::insert(const Literals& x)
{
  Literals::const_iterator it;
  for (it = x.begin(); it != x.end(); it++) {
	m_L[*it] = 1;      
  }    
}


void State::print() const
{
  cout << "{";
  m_planner->print(m_L);
  cout << "}";
}

/*************************************************************************
 * CState Implementation
 *************************************************************************/
/* constructor and destructor */
CState::CState() 
{
  m_hvalue = -1;
  m_hcvalue = -1;
  //m_graph_heuristic = -1;
  m_hgvalue = -1.0;  
  m_status = UNEXPANDED;  
  m_active_in_transitions = 1;
  m_depth = 0;
}

CState::~CState() 
{
	
}

void CState::clear()
{
  m_hvalue = -1;
  //m_graph_heuristic = -1;  
  m_states.clear();
}

bool CState::operator<(const CState& cs) const 
{
  return m_states < cs.m_states;
}

CState CState::operator=(const CState& cs) 
{
  m_states = cs.m_states;
  m_hvalue = cs.m_hvalue;
  //m_graph_heuristic = cs.m_graph_heuristic;  

  return *this;
}

void CState::copy(const CState& cs) 
{
  set<State*>::const_iterator it_s;
  State* s;
  for (it_s = cs.m_states.begin(); it_s != cs.m_states.end(); it_s++) { 
	  s = new State(NULL);
	  *s = *(*it_s);
	  m_states.insert(s);
  }   
}

bool CState::decides(const Literal l)
{
  set<State*>::iterator it;
  Literal l1;
  int l_count = 0, l1_count = 0;

  NEGATE(l, l1);
	
  for (it = m_states.begin(); it != m_states.end(); it++) {
    if ((*it)->satisfies(l)) 
		l_count++;
	else if ((*it)->satisfies(l1)) 
		l1_count++;
	else
		return false;

	if (l_count && l1_count)
		return false;
  }

  return true;
}

bool CState::split(CState* cs1, CState* cs2, const Literal l)
{
  set<State*>::iterator it;
  Literal l1;  
  State *s;

  NEGATE(l, l1);
	
  for (it = m_states.begin(); it != m_states.end(); it++) {
	  if ((*it)->satisfies(l)) {
		  cs1->m_states.insert(*it);
	  }
	  else{
		  if ((*it)->satisfies(l1)) {
			  cs2->m_states.insert(*it);
		  }
		  else {
			s = new State((*it)->m_planner);
			s->m_L = (*it)->m_L;
			s->m_L[l] = 1;	
			cs1->m_states.insert(s->m_planner->add_state(s));

			s = new State((*it)->m_planner);
			s->m_L = (*it)->m_L;
			s->m_L[l1] = 1;
			cs2->m_states.insert(s->m_planner->add_state(s));
		  }		
	  }
  }

  return true;
}

bool CState::goal_satisfied()
{
  set<State*>::iterator it;
  bool goal_sat = true;
	
  for (it = m_states.begin(); it != m_states.end(); it++) {
    if (!(*it)->goal_satisfied() && goal_sat) {
      goal_sat = false;
    }
  }

  return goal_sat;
}


int CState::hgvalue()
{
	if (m_hgvalue == -1) {
		m_hgvalue = 0;
		set<State*>::const_iterator its;
		int d;		
		its = m_states.begin();
		for (its = m_states.begin(); its != m_states.end(); its++) {			
			d = (*its)->m_gd_sat.size() - (*its)->m_gd_sat.count();			
			m_hgvalue += d*d;
		}		
	}	
	return m_hgvalue;
}


int CState::hvalue()
{
	if (m_hvalue == -1) {
		set<State*>::const_iterator its;
		its = m_states.begin();
		boost::dynamic_bitset<> m_gd_sat;				
		m_gd_sat = (*its)->m_gd_sat;				

		for (++its; its != m_states.end(); its++) {						
			m_gd_sat = m_gd_sat & (*its)->m_gd_sat;						
		}		
		m_hvalue = m_gd_sat.count();		
	}	
	return m_hvalue;
}


int CState::hcvalue(boost::dynamic_bitset<>* L) {		
	if (m_hcvalue == -1) {
		set<State*>::const_iterator its;
		its = m_states.begin();		
		*L = (*its)->m_L;

		for (++its; its != m_states.end(); its++) {
			*L = *L & (*its)->m_L;
		}
		m_hcvalue = L->count();	
	}
	return m_hcvalue;
}

int CState::hcvalue() {		
	if (m_hcvalue == -1) {
		boost::dynamic_bitset<> L;
		set<State*>::const_iterator its;
		its = m_states.begin();		
		L = (*its)->m_L;

		for (++its; its != m_states.end(); its++) {
			L = L & (*its)->m_L;
		}
		m_hcvalue = L.count();	
	}
	return m_hcvalue;
}


//Estimate the distance to the goal by number of actions. -2 means infinity - goal-unreachable node, -1 means not computed yet
int CState::graph_heuristic()
{
	if (m_graph_heuristic == -1) {
		vector<pActionList> At; //For action layers
		vector<boost::dynamic_bitset<> > L; //For fluent literal layers
		vector<vector<StateH*> > S; //For Belief State in each layer

		//A, L, P - vectors contain sets of actions, sets of true literals, sets of implication formulae respectively in each layer
		if (!graph_build(&At,&L,&S)) {			
			m_graph_heuristic = -2;
			cout << "Unreachable ";
		}

		else m_graph_heuristic = plan_extract(&At,&L,&S);
		cout <<"h=" << m_graph_heuristic<< " ";
		
		free_graph(&S);		
	}
	
	return m_graph_heuristic;
}

bool CState::graph_build(vector<pActionList >* pA, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS)
{	
	boost::dynamic_bitset<> L;	
	ActionList::const_iterator ita;
	EffectList::const_iterator ite;
	ExecList::const_iterator itx;	
	set<State*>::const_iterator its, its1;	
	vector<StateH*> S;
	StateH* s;	
	
	//Compute known literals in the first layer from the current CState
	
	hcvalue(&L);
	pL->push_back(L);
	pS->push_back(S);
	
	
	for (its = m_states.begin(); its != m_states.end(); its++) {
		s = new StateH((*its)->m_L);
		//s->m_L = (*its)->m_L;
		s->pre = NULL;
		(pS->back()).push_back(s);		
	}
	
	
	/******************************** Relax for one possible state *****************
	for (its = m_states.begin(), its1 = its++; its != m_states.end(); its++) {		
		if (((*its)->m_L & (*its)->m_planner->m_goal).count() < ((*its)->m_L & (*its)->m_planner->m_goal).count())
			its1 = its;
		else
			if ((((*its)->m_L & (*its)->m_planner->m_goal).count() == ((*its)->m_L & (*its)->m_planner->m_goal).count()) &&
				((*its)->m_L & (*its)->m_planner->m_L).count() < ((*its)->m_L & (*its)->m_planner->m_L).count())
					its1 = its;
	}

	//s = new StateH(L);
	s = new StateH((*its1)->m_L);
	s->pre = NULL;

	for (l = 0; l < L.size()/2; l++) {	
		if (!s->m_L[2*l]) {		
			if (!s->m_L[2*l+1]) {				
					s->m_L[2*l+1] = 1;				
			}
		}
	}	

	(pS->back()).push_back(s);		
	*/


		
	int t = 0;

	while (!goal_satisfies(pL->at(t), pS->at(t), (*m_states.begin())->m_planner->m_gd)) {
		//Compute applicable actions in the first layer of the plan graph			
		exec_actions((*m_states.begin())->m_planner->m_actions, pA, pL->at(t));		
		build_layer(t, &pA->at(t), pL, pS);				
		if (pL->at(t) == pL->at(t+1) && pS->at(t) == pS->at(t+1)) {			
			return false;
		}		
		t++;
	}
	return true;
}

int CState::plan_extract(vector<pActionList >* pA, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS)
{
	vector<set<Action*> > A;
	vector<set<Action*> >::iterator itA;
	set<Action*> A1;	
	vector<vector<Literals> > G;
	vector<Literals> G1;
	vector<Literals>::const_iterator itg;
	vector<Literals>::iterator itg1;
	Literals st;
	Literals::const_iterator itl;
	vector<StateH*>::const_iterator its, its1;
	pActionList::const_iterator ita;
	EffectList::const_iterator ite;
	int t, i, N=0;

	t = pS->size()-1; // pA->size() = pS->size()-1

	if (t == 0)
		return N;

	A.assign(pA->size(), A1);
	
	G.assign(pS->size(), G1);
	for (i = 1; i < pS->size(); i++) 
		G[i].assign(pS->at(i).size(), st);

	G1.assign(pS->size(), st);

	for (itg  = (*m_states.begin())->m_planner->m_gd.begin(); itg  != (*m_states.begin())->m_planner->m_gd.end(); itg++) {		
		for (itl = itg->begin(); itl != itg->end(); itl++) {
			if (pL->at(t)[*itl])
				break;
		}

		if (itl != itg->end())
			G1[t].insert(*itl);
		else {
			for (its = pS->at(t).begin(), itg1 = G[t].begin(); its != pS->at(t).end(); its++, itg1++) {
				for (itl = itg->begin(); itl != itg->end(); itl++) {
					if ((*its)->m_L[*itl])
						break;
				}
				itg1->insert(*itl);
			}
		}
	}

	for (; t>0; t--) {
		//Treat for common goals G1
		for (itl = G1[t].begin(); itl != G1[t].end(); itl++) {
			if (pL->at(t-1)[*itl]) {
				if (t > 1)
					G1[t-1].insert(*itl);
				continue;
			}		
			
			for (ita = pA->at(t-1).begin(); ita != pA->at(t-1).end(); ita++) {								
				for (ite = (*ita)->get_effects()->begin(); ite != (*ita)->get_effects()->end(); ++ite) 					
					if (ite->get_head()->count(*itl) && includes(pL->at(t-1), *ite->get_body())) {						
						A[t-1].insert(*ita);
						if (t > 1) {							
							G1[t-1].insert(ite->get_body()->begin(), ite->get_body()->end());	
							if ((*ita)->pre(pL->at(t-1),&st))
								G1[t-1].insert(st.begin(), st.end());
						}
						break;
					}					
				if (ite != (*ita)->get_effects()->end()) //found action
					break;
			}			

			if (ita == pA->at(t-1).end())
				for (itg1 = G[t].begin(); itg1 != G[t].end(); itg1++)
					itg1->insert(*itl);								
		}

		
		//Treat for each individual set s
		for (its = pS->at(t).begin(), itg = G[t].begin(); its != pS->at(t).end(); its++, itg++) {			
			for (itl = itg->begin(); itl != itg->end(); itl++) {				
				if ((*its)->pre->m_L[*itl]) {
					if (t > 1) {
						for (its1 = pS->at(t-1).begin(), itg1 = G[t-1].begin(); its1 != pS->at(t-1).end(); its1++, itg1++) {
							if (*its1 == (*its)->pre) {
								itg1->insert(*itl);
								break;
							}
						}
					}
					continue;
				}

				for (ita = pA->at(t-1).begin(); ita != pA->at(t-1).end(); ita++) {										
					for (ite = (*ita)->get_effects()->begin(); ite != (*ita)->get_effects()->end(); ++ite) {						
						if (ite->get_head()->count(*itl) && includes((*its)->pre->m_L, *ite->get_body())) {							
							A[t-1].insert(*ita);							
							if (t > 1) {								
								//cout << "6  G1.size() = " << G1.size() <<", G1[" << t-1 <<"] = "; fflush(stdout); print_set(G1[t-1]);								
								(*ita)->pre(pL->at(t-1), &st);								
								if ((*ita)->pre(pL->at(t-1), &st))
									G1[t-1].insert(st.begin(), st.end());								
								for (its1 = pS->at(t-1).begin(), itg1 = G[t-1].begin(); its1 != pS->at(t-1).end(); its1++, itg1++) {									
									if (*its1 == (*its)->pre) {										
										itg1->insert(ite->get_body()->begin(), ite->get_body()->end());										
										break;
									}												
								}
							}							
							break;
						}						
					}					
					if (ite != (*ita)->get_effects()->end()) //found action
						break;
				}				
				//If no such action found, *itl appears by splitting
			}
		}
	}
	
	for (itA = A.begin(); itA != A.end(); itA++)
		N += itA->size();	

	return N;
}


bool goal_satisfies(const boost::dynamic_bitset<>& L, const vector<StateH*>& S, const vector<Literals>& goal)
{	
	vector<Literals>::const_iterator itg;
	vector<StateH*>::const_iterator its;	

	for (itg = goal.begin(); itg!=goal.end(); itg++) {		
		if (intersects(L,*itg))
			continue;		
		for (its=S.begin(); its!=S.end(); its++) {			
			if (!(*its)->satisfies(&(*itg)))
				return false;
		}
	}

	return true;
}
	
void exec_actions(ActionList& p_actions, vector<pActionList>* pA, const boost::dynamic_bitset<>& L)
{	
	ActionList::iterator ita;
	pActionList l_actions;
		
	pA->push_back(l_actions);	
	
	for (ita = p_actions.begin(); ita != p_actions.end(); ita++) {	
		//Only consider applicable actions that possiblly affect the next layer
		if (ita->is_executable(L) && !ita->noEffectIn(L))			
			(pA->back()).push_back(&(*ita));		
	}	
}
		
void build_layer(const int t, const pActionList* p_actions, vector<boost::dynamic_bitset<> >* pL, vector<vector<StateH*> >* pS)
{
	pActionList::const_iterator ita;
	EffectList::const_iterator ite;	
	vector<StateH*>::iterator its;
	vector<StateH*> S;
	set<StateH*> S1;
	StateH* s;
	Literals x;		

	pL->push_back(pL->at(t));			
	pS->push_back(S);

	for (its = pS->at(t).begin(); its != pS->at(t).end(); its++) {
		s = new StateH((*its)->m_L);
		//s->m_L = (*its)->m_L;
		s->pre = *its;
		(pS->back()).push_back(s);		
		S1.insert(s);		
	}	
	
	if ( S1.size() != (pS->back()).size())
		cout << "S1.size() = " << S1.size() <<", (pS->back()).size() = " << (pS->back()).size(); fflush(stdout);

	//Compute the next layer by execution of actions
	//Compute the enabling form
	for (ita = p_actions->begin(); ita != p_actions->end(); ita++) {
		for (ite = (*ita)->get_effects()->begin(); ite != (*ita)->get_effects()->end(); ++ite) {			
			//Do not consider for the effect that already contained in the next layer						
			if (includes(pL->back(), *ite->get_head()))
				continue;				
			if (includes(pL->at(t), *ite->get_body()))
				add(&pL->back(), ite->get_head());
			else 
				split_effect(&pS->back(), pL->back(), *ite);			
		}
	}		
	//Compute the next layer
	execute_effect(&pS->back(), &pL->back());	
}


void execute_effect(vector<StateH*>* S, boost::dynamic_bitset<>* L)
{	
	static int times=0, count=0;
	static bool check = true, checkcheck = false;
	Literals::iterator itl;	
	vector<StateH*> S1;
	vector<StateH*>::iterator its, its1;	
	
	if (!check) {
		for (its = S->begin(); its != S->end(); its++) {
			for (itl = (*its)->m_EF.begin(); itl != (*its)->m_EF.end(); itl++) {				
				(*its)->m_L[*itl] = 1;				
			}		
			(*its)->m_EF.clear();				
			(*its)->m_L = (*its)->m_L | *L;
		}
		
		its = S->begin();
		*L = (*its)->m_L;		
		for (++its; its != S->end(); its++) 
			*L = *L & (*its)->m_L;
		
		return;
	}

	for (its = S->begin(); its != S->end(); its++) {
		for (itl = (*its)->m_EF.begin(); itl != (*its)->m_EF.end(); itl++) {		
			(*its)->m_L[*itl] = 1;			
		}
		(*its)->m_L = (*its)->m_L | *L;
	}	

	for (its = S->begin(); its != S->end(); its++) {
		if (!checkcheck) {		
			if (times>500 && count<2) {
				cout << "No check, count(500) = " <<count << endl;
				check = false;
				checkcheck = true;
			}

			if (times>5000) {
				if (10*count<times) {
					cout << "No check, count = " << count << " < times = "<< times <<endl;
					check = false;					
				}
				else {
					cout << "Check, count = " << count << ", times = "<< times <<endl;
					check = true;
				}
				checkcheck = true;
			}
		}
		
		if (check) {
			//cout <<" 1 "; fflush(stdout);
			for (its1=S1.begin(); its1 != S1.end(); its1++) {
				times++;
				if ((*its)->includes(*its1)) {
					count++;
					break;
				}
			}

			//cout <<" 2 "; fflush(stdout);

			if (its1 != S1.end()) {				
				delete *its;
				continue;
			}

			for (its1 = its, its1++ ; its1 != S->end(); its1++) {
				times++;
				if ((*its)->includes(*its1)) {
					count++;
					break;
				}				

				if (!checkcheck && times>1000 && count<10) {
					its1 = S->end();
					break;
				}
			}
			
			//cout <<" 3 "; fflush(stdout);

			if (its1 != S->end()) {			
				delete *its;
				continue;
			}
		}

		//cout <<" 4 "; fflush(stdout);

		(*its)->m_EF.clear();		
		S1.push_back(*its);
		//cout <<" 5 "; fflush(stdout);
	}

	//cout <<" 6 "; fflush(stdout);

	*S = S1;
	its = S->begin();
	*L = (*its)->m_L;	
	for (++its; its != S->end(); its++) 
		*L = *L & (*its)->m_L;	
	//cout <<" 7 "; fflush(stdout);
}



bool includes(const boost::dynamic_bitset<>& L, const Literals& x)
{
	Literals::const_iterator itl;

	for (itl = x.begin(); itl != x.end(); itl++) {
		if (!L[*itl])
			return false;
	}
	return true;
}


bool intersects(const boost::dynamic_bitset<>& L, const Literals& x)
{
	Literals::const_iterator itl;

	for (itl = x.begin(); itl != x.end(); itl++) {
		if (L[*itl])
			return true;
	}
	return false;
}


void add(boost::dynamic_bitset<>* pL, const Literals* s)
{
	Literals::const_iterator itl;

	for (itl = s->begin(); itl != s->end(); itl++) {
		if (!(*pL)[*itl])
			(*pL)[*itl] = 1;
	}	
}


bool add_set(const vector<StateH*>& S, const int i, const int size, StateH& s, set<StateH*>* S1)
{
	set<StateH*>::iterator its;
	int j;

	for (its=S1->begin(); its!=S1->end(); its++) {
		if (s.includes(*its))
			return false;
	}

	for (j = i+1; j<size; j++) {
		if (s.includes(S[j])) 
			return false;		
	}

	S1->insert(&s);
	return true;
}

void split_effect(vector<StateH*> *S, const boost::dynamic_bitset<>& L, const Effect& ef) 
{	
	Literal l;
	int i, size;
	set<StateH*> S1;
	StateH* s;
	vector<StateH*>::iterator its;
	Literals::iterator itl;	
	Literals st;
	
	size = S->size();
	for (i=0; i <size; i++) {		
		if (!sat_value(S->at(i), L, ef, &st)) 
			S1.insert(S->at(i));
		else {
			if (!st.size()) {				
				S->at(i)->m_EF.insert(ef.get_head()->begin(), ef.get_head()->end());
				S1.insert(S->at(i));
			}
			else {				
				for (itl = st.begin(); itl != st.end(); itl++) {					
					NEGATE(*itl, l);
					s = new StateH(S->at(i)->m_L);
					s->pre = S->at(i)->pre;					
					s->m_L[l] = 1;					
					S->push_back(s);
					add_set(*S, i, size, *s, &S1);
				}				
				S->at(i)->insert(st);
				if (add_set(*S, i, size, *S->at(i), &S1))
					S->at(i)->m_EF.insert(ef.get_head()->begin(), ef.get_head()->end());
			}
		}
	}

	//Remove subsumed sets
	for (i=S->size()-1; i!=0; i--) {		
		//cout <<" S->at(" << i << ") = " << S->at(i)<<" ";fflush(stdout);
		if (!S1.count(S->at(i))) {
			//cout <<" delete at " << i << " : " << S->at(i)<<" ";fflush(stdout);
			delete S->at(i);
			S->erase(S->begin()+i);
		}
	}
}

//Return false if not affects, true else. Set st contains unknown truth-value literals
bool sat_value(StateH* s, const boost::dynamic_bitset<>& L, const Effect& ef, Literals* st) {
	Literals::const_iterator it_l;
	Literal l;
	set<State*>::const_iterator its;

	//If the state already includes the head of the effect so we just ignore it.
	if (s->will_include(ef.get_head(), L)) 	
		return false;

	st->clear();
	for (it_l = ef.get_body()->begin(); it_l!= ef.get_body()->end();it_l++) {
		if (s->m_L[*it_l])
			continue;
		NEGATE(*it_l,l);
		if (s->m_L[l])
			return false;
		st->insert(*it_l);		
	}	

	return true;
}

void free_graph(vector<vector<StateH*> >* pS) 
{
	vector<vector<StateH*> >::iterator itS;
	vector<StateH*>::iterator its;

	for (itS = pS->begin(); itS != pS->end(); itS++)
		for (its = itS->begin(); its != itS->end(); its++)
			delete *its;
}

int CState::hash()
{
	set<State*>::iterator its;	
	unsigned int hash = 0;
	for (its = m_states.begin(); its != m_states.end(); its++) {
		hash += (*its)->hash();
	}	
	return hash & HASH_BITS;
}


//Need only one state satisfies goal for the heuristic
bool goal_Satisfied(set<State*>* cs)
{
  set<State*>::iterator it;
  bool goal_sat = true;
	
  for (it = cs->begin(); it != cs->end(); it++) {
    if (!(*it)->goal_satisfied() && goal_sat) {
      goal_sat = false;
    }
  }

  return goal_sat;
}

//Return the action that when executed in cs results in this cstate
const Action* CState::get_action(CState* cs)
{
	map<CState*,const Action*>::iterator it;

	it = m_in_transitions.find(cs);

	if (it != m_in_transitions.end())
		return it->second;

	return NULL;
}

//Return true if : cs x act -> this
bool CState::is_successor(CState* cs, const Action* act)
{
	map<CState*,const Action*>::iterator it;

	it = m_in_transitions.find(cs);

	if (it != m_in_transitions.end() && it->second == act)
		return true;

	return false;
}


//Compute the propagatable incomming transitions of the node: the higher the better
int CState::propagatable_transitions()
{	
	map<CState*, const Action*>::iterator it;
	int transitions=0;	

	for (it = m_in_transitions.begin(); it != m_in_transitions.end(); it++) {	
		if (it->second->m_sensing) 
			transitions++;						
		else
			transitions += 2;
	}

	return transitions;	
}

bool CState::is_better(CState* cs)
{		
	if (hvalue() > cs->hvalue())
		return true;
	if ((hvalue() == cs->hvalue()) && (m_states.size() < cs->m_states.size()))
		return true;

	return false;
}



void CState::set_depth(const int& depth)
{
  m_depth = depth;  
}

int CState::get_depth() const
{
  return m_depth;
}

void CState::print() const
{
  bool comma = false;
  set<State*>::const_iterator it;

  cout << "<{";
  for (it = m_states.begin(); it != m_states.end(); it++) {
    if (comma) {
      //cout << ",";		
    }
    else 
      comma = true;
    (*it)->print();
	cout << endl;
  }
  cout << "}>";
  //cout << "}," << m_hvalue << ">";
}

void CState::solution_print(Planner* planner, const int level)
{  	
	int i;	
	map<CState*,int>::iterator it;	
	const Action* act;	
	
	for (i=0; i<level; i++)	cout << "  ";

	if (this->goal_satisfied()) {		
		if (planner->m_depth < this->m_depth)
			planner->m_depth = this->m_depth;
		return;
	}
	
	if (!m_successors.size()) {
		cout <<"DEAD-END, WRONG PLAN!";
		return;
	}

	act = m_successors[0]->get_action(this);
	cout << planner->m_commandNo.size() <<": " << act->get_name()<<endl;
	planner->m_commandNo.insert(pair<CState*,int>(this,planner->m_commandNo.size()));	
	
	if (!act->m_sensing) {
		it = planner->m_commandNo.find(m_successors[0]);
		if (it == planner->m_commandNo.end()) {
			m_successors[0]->m_depth = m_depth + 1;
			m_successors[0]->solution_print(planner,level);			
		}
		else {
			if (m_successors[0]->m_depth <= m_depth) {
				m_successors[0]->m_depth = m_depth + 1;
				m_successors[0]->depth_propagate(planner);
			}

			for (i=0; i < level; i++)	cout << "  ";
			cout << "GOTO " << it->second << endl;
		}
	}
	else {
		
		if (m_successors.size() < 2) {
			cout <<"WRONG TRANSITION STRUCTURE!";
			return;
		}

		cout << "  " << "IF: " << ((*m_states.begin())->m_planner->convert(act->lit())) << endl;
		it = planner->m_commandNo.find(m_successors[0]);
		if (it == planner->m_commandNo.end()) {
			m_successors[0]->m_depth = m_depth + 1;
			m_successors[0]->solution_print(planner,level+1);			
		}
		else {
			if (m_successors[0]->m_depth <= m_depth) {
				m_successors[0]->m_depth = m_depth + 1;
				m_successors[0]->depth_propagate(planner);
			}

			for (i=0; i <= level; i++)	cout << "  ";
			cout << "GOTO " << it->second << endl;
		}		
		
		for (i=0; i < level; i++)	cout << "  ";
		cout << "IF: NOT " << ((*m_states.begin())->m_planner->convert(act->lit())) << endl;
		it = planner->m_commandNo.find(m_successors[1]);
		if (it == planner->m_commandNo.end()) {
			m_successors[1]->m_depth = m_depth + 1;
			m_successors[1]->solution_print(planner,level+1);			
		}
		else {			
			if (m_successors[1]->m_depth <= m_depth) {
				m_successors[1]->m_depth = m_depth + 1;
				m_successors[1]->depth_propagate(planner);
			}

			for (i=0; i <= level; i++)	cout << "  ";
			cout << "GOTO " << it->second << endl;
		}
	}
	return;
}

void CState::solution_not_print(Planner* planner, const int level)
{  	
	int i;	
	map<CState*,int>::iterator it;	
	const Action* act;	
	
	//for (i=0; i<level; i++)	cout << "  ";

	if (this->goal_satisfied()) {		
		if (planner->m_depth < this->m_depth)
			planner->m_depth = this->m_depth;
		return;
	}
	
	if (!m_successors.size()) {
		cout <<"DEAD-END, WRONG PLAN!";
		return;
	}

	act = m_successors[0]->get_action(this);
	//cout << planner->m_commandNo.size() <<": " << act->get_name()<<endl;
	planner->m_commandNo.insert(pair<CState*,int>(this,planner->m_commandNo.size()));	
	
	if (!act->m_sensing) {
		it = planner->m_commandNo.find(m_successors[0]);
		if (it == planner->m_commandNo.end()) {
			m_successors[0]->m_depth = m_depth + 1;
			m_successors[0]->solution_not_print(planner,level);			
		}
		else {
			if (m_successors[0]->m_depth <= m_depth) {
				m_successors[0]->m_depth = m_depth + 1;
				m_successors[0]->depth_propagate(planner);
			}
			//for (i=0; i < level; i++)	cout << "  ";
			//cout << "GOTO " << it->second << endl;
		}
	}
	else {
		
		if (m_successors.size() < 2) {
			cout <<"WRONG TRANSITION STRUCTURE!";
			return;
		}

	//	cout << "  " << "IF: " << ((*m_states.begin())->m_planner->convert(act->lit())) << endl;
		it = planner->m_commandNo.find(m_successors[0]);
		if (it == planner->m_commandNo.end()) {
			m_successors[0]->m_depth = m_depth + 1;
			m_successors[0]->solution_not_print(planner,level+1);			
		}
		else {
			if (m_successors[0]->m_depth <= m_depth) {
				m_successors[0]->m_depth = m_depth + 1;
				m_successors[0]->depth_propagate(planner);
			}
	//		for (i=0; i <= level; i++)	cout << "  ";
	//		cout << "GOTO " << it->second << endl;
		}		
		
	//	for (i=0; i <= level; i++)	cout << "  ";
	//	cout << "IF: NOT " << ((*m_states.begin())->m_planner->convert(act->lit())) << endl;
		it = planner->m_commandNo.find(m_successors[1]);
		if (it == planner->m_commandNo.end()) {
			m_successors[1]->m_depth = m_depth + 1;
			m_successors[1]->solution_not_print(planner,level+1);			
		}
		else {
			if (m_successors[1]->m_depth <= m_depth) {
				m_successors[1]->m_depth = m_depth + 1;
				m_successors[1]->depth_propagate(planner);
			}
	//		for (i=0; i <= level; i++)	cout << "  ";
	//		cout << "GOTO " << it->second << endl;
		}
	}
	return;
}

void CState::depth_propagate(Planner* planner)
{
	int i;
	for (i=0; i<m_successors.size(); i++) {
		if (m_successors[i]->m_depth <= m_depth) {
			m_successors[i]->m_depth = m_depth + 1;
			m_successors[i]->depth_propagate(planner);
		}
	}	
	if (!m_successors.size() && planner->m_depth < m_depth)
			planner->m_depth = m_depth;
}

void print_set(const Literals& S) 
{
	Literals::const_iterator itl;
	bool first=true;
	cout << "{";
	for (itl = S.begin(); itl != S.end(); itl++) {
		if (first)
			first = false;
		else
			cout <<", ";		
		print_literal(*itl);		
	}
	cout << "}";
	fflush(stdout);
}

void print_set(const boost::dynamic_bitset<>& L)
{
	int i;
	bool first=true;
	cout << "{";
	for (i = 0; i < L.size(); i++) {
		if (L[i]) {
			if (first)
				first = false;
			else
				cout <<", ";
			print_literal(i);
		}
	}
	cout << "}";
	fflush(stdout);
}

void print_literal(const Literal l)
{
	if (l % 2 == 0) 
		cout << (l / 2);
	else
		cout <<"-" <<(l / 2);
	fflush(stdout);
}
