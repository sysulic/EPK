// planner.cpp: implementation of the planner class.
//////////////////////////////////////////////////////////////////////
#include "planner.h"
clock_t t_start, t_now;
bool giveup;
double timeLimit;

/*************************************************************************
 * Planner Implementation
 *************************************************************************/
// Constructor & destructor 
Planner::Planner(const Reader* reader, Timer* timer)
{
  m_timer = timer;
  m_reader = reader;

  m_semantics = PC;
  m_task = SEARCH;
  m_algorithm = GREEDY;
  m_detect_essential = true;
  m_output_decisive = false;  
}

Planner::~Planner()
{
 
}

bool Planner::main()
{

#ifdef PRINT_DOMAIN
  m_reader->print();
  exit(0);
#endif

  // build the domain
  cout << "Building domain..." <<endl; fflush(stdout);
  m_timer->start(BUILD_TIMER);
  m_states.resize(HASH_SIZE);
  m_cstates.resize(HASH_SIZE);
  build_domain();  
  build_goal();  
  build_init();
  m_timer->end(BUILD_TIMER);

  cout << "done." << endl << endl; fflush(stdout);

  // print domain
#ifdef PRINT_INTERNAL_DOMAIN
  print_interal_domain();
  cout << endl;
#endif

#ifdef PRINT_SUMMARY
  cout << endl;
  print_summary();
#endif
  // search for a plan or execute a sequence of actions
  switch (m_task) {
  case SEARCH:
    m_timer->start(SEARCH_TIMER);
    search();
    m_timer->end(SEARCH_TIMER);
    break;
  case DOPLAN:
    execute();
    break;
  default:
    return false;
  }

  cout << endl;
  print_statistics(); 

  return true;
};

/*

  StringList x;
  unsigned int i;
  string f; // fluent
  StringList::const_iterator itf;
  typedef map<string,Literal>::value_type value_type;
*/

bool Planner::build_domain()
{
  int i;
  StringList::const_iterator itf;
  typedef map<string,Literal>::value_type value_type;
  PropositionList::const_iterator it_prop;
  Action* p_act;
  StaticLaw stat;
  Literals hd, bd;
  Literals::iterator itl;
  ActionList::const_iterator ita, ito;
  EffectList::const_iterator ite;


  // build fluent literals;
  i = 0;
  for (itf = m_reader->m_fluents.begin(); 
       itf != m_reader->m_fluents.end(); itf++) { 
    m_map.insert(value_type(*itf,i));
    m_literals.insert(i++);
    m_map.insert(value_type(NEGATION_SYMBOL+*itf,i));
    m_literals.insert(i++);    
  }

  // build action list
  for (it_prop = m_reader->m_propositions.begin(); 
       it_prop != m_reader->m_propositions.end(); it_prop++) {    
    // The head of a sensing action contains only one single literal 
    hd = ground((*it_prop).get_effect());
    bd = ground((*it_prop).get_precondition());

	//m_L.resize(m_literals.size());
	//for (itl = bd.begin(); itl != bd.end(); itl++)
	//	m_L[*itl] = 1;

    switch ((*it_prop).n_type) {
    case STATIC:
      stat.set_head(hd);
      stat.set_body(bd);
      m_statics.push_back(stat);
      break;
    case DYNAMIC:
      p_act = add_action((*it_prop).act_name);
      p_act->add_effect(hd,bd);
      break;
    case EXECUTABILITY:
      p_act = add_action((*it_prop).act_name);
      p_act->add_exec(bd);
      break;
    case IMPOSSIBILITY:
      p_act = add_action((*it_prop).act_name);
      p_act->add_imposs(bd);
      break;
    default:
      break;
    }
  }

  /*
  //Compute independent pair (action,sensing) 
  for (ito = m_sensings.begin(); ito != m_sensings.end(); ito++) {
	  l = ito->lit();
	  NEGATE(l, l1);
	  for (ita = m_actions.begin(); ita != m_actions.end(); ita++) {
		  for (ite = (*ita)->get_effects()->begin(); ite != (*ita)->get_effects()->end(); ++ite)
			  if (ite->get_head()->count(l) || ite->get_head()->count(l1))
				  break;
		  
		  if (ite == (*ita)->get_effects()->end()) {
			  ito->add_independent(*ita);
			  ita->add_independent(*ito);
		  }
		
	  }
  }
  */

  return true;
}

bool Planner::build_goal()
{
  StringList2::const_iterator it;
  Literals st;

  // build the goal
  m_goal.resize(m_literals.size());
  for (it = (m_reader->m_gd).begin(); it != (m_reader->m_gd).end(); it++) {
    st = ground(&(*it));   
    insert(m_goal, st);
    m_gd.push_back(st);
  }
  
  //goal_analyze();

  /*
  cout << "Goal:" <<endl;
  set<Literals>::iterator itg;
  for (itg = m_gd.begin(); itg != m_gd.end(); itg++) {
	print(*itg);
	cout << endl;
  }
  */

  return true;
}

bool Planner::intersect(const boost::dynamic_bitset<>& S, const Literals& x) {
	Literals::const_iterator it;
	for (it = x.begin(); it != x.end(); it++) {
		if (S[*it] == 1)
			return true;
	}
	return false;
}

bool Planner::insert(boost::dynamic_bitset<>& S, const Literals& x) {
	Literals::const_iterator it;
	bool flip = false;

	for (it = x.begin(); it != x.end(); it++) {
		if (!S[*it]) {
			S[*it] = 1;
			if (!flip) flip =true;
		}
	}
	return flip;
}

bool Planner::build_init()
{  
  list<boost::dynamic_bitset<> > init;  
  list<boost::dynamic_bitset<> >::reverse_iterator it;
  State *s;    
  
  //print(&m_reader->m_init);
  unsigned long cnf_cost = CNF_cost(&m_reader->m_init);
  unsigned long dnf_cost = DNF_cost(&m_reader->m_init);  
  cout<<"CNF Cost: "<<(long) cnf_cost<<", DNF Cost: "<<(long) dnf_cost<<endl;

  timeLimit = 10000;
  clock_t t_start0;
  t_start0 = clock();
  
  do {
    init.clear();
	giveup = false;
	t_start = clock();	
	if (!DNF(&m_reader->m_init, init)) {
		cout<<endl<<"Initial information is inconsistent!"<<endl;
		exit(1);
	}		
	if (timeLimit < 5.0)
		timeLimit *= 5.0;
	else
		timeLimit *= 2.0;
  } while(giveup);



  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(3);	
  cout<<"Initial Computation Time: "<< (clock() - t_start0)/(double)CLOCKS_PER_SEC; fflush(stdout);
  if (init.size())
	cout<<" Init size="<<init.size()<<" x "<< m_literals.size()<<" x " <<init.begin()->count()<<endl; 
  else
	cout<<" Init size="<<init.size()<<" x "<< m_literals.size()<<endl; fflush(stdout);
  		
  if (!init.size()) {		  
		  boost::dynamic_bitset<> st;
		  st.resize(m_literals.size());
		  st[0] = 1;
		  //init.push_back(st);
		  init.push_back(st);
		  st[0] = 0;
		  st[1] = 1;		  
		  //init.push_back(st);
		  init.push_back(st);
  }
  
  for (it = init.rbegin(); it != init.rend(); it++) {
    s = new State(this);	
    s->m_L = *it;
	s = add_state(s);
    m_init_cstate.m_states.insert(s);
  }
  
  cout <<"Initial CState Size = "<< m_init_cstate.m_states.size() << endl; fflush(stdout);
  //m_init_cstate.print();

  return true;
}

void Planner::print(const Node* node) {	
	vector<Literals> f, lf, rf;	
	vector<Literals>::iterator itl, itr;
	
	Literals st;
	
	if (!node) {
		cout <<"NULL, ";
		return;
	}
	//cout << node->label <<", ";

	if (node->label == "|" || node->label == "&") {			
		if (node->label == "|")
			cout<<"v ";
			//cout<<"(v "<<CNF_cost(node)<<" "<<DNF_cost(node)<<")";
		else
			cout<<"^ ";
			//cout<<"(^ "<<CNF_cost(node)<<" "<<DNF_cost(node)<<")";
		print(node->left);
		print(node->right);		
	}
	else
		cout <<node->label<<" ";
}

unsigned long Planner::DNF_cost(const Node* node) {
	if (node->label == "|") {
		return DNF_cost(node->left) + DNF_cost(node->right);
	}
	if (node->label == "&") {
		return DNF_cost(node->left) * DNF_cost(node->right);
	}	
	return 1;
}

unsigned long Planner::CNF_cost(const Node* node) {
	if (node->label == "|") {
		return CNF_cost(node->left) * CNF_cost(node->right);
	}
	if (node->label == "&") {
		return CNF_cost(node->left) + CNF_cost(node->right);
	}
	if (node->label == "$&|TRUE$")
		return 0;
	return 1;
}	


bool Planner::timeout() {
	if (giveup)
		return true;
	if ( (clock() - t_start)/(double)CLOCKS_PER_SEC > timeLimit) {
		giveup = true;
		return true;
	}
	return false;
}


bool Planner::DNF(const Node* node, list<boost::dynamic_bitset<> >& f) {	
	bool leftOK, rightOK;
	list<boost::dynamic_bitset<> > lf, rf;
	list<boost::dynamic_bitset<> >::iterator itl, itr;	
	boost::dynamic_bitset<> st;
		
	if (timeout()) return false;

	if (node->label == "|") {		
		leftOK = DNF(node->left, f);
		if (timeout()) return false;

		if (!leftOK) {			
			if (!(rightOK = DNF(node->right, f)))
				return false;
			return true;
		}
		
		rightOK = DNF(node->right, rf);
		if (timeout()) return false;

		if (!rightOK) {			
			return true;
		}
		
		if (annul(f, rf)) {
			f.clear();
			return true;
		}

		//f.splice(f.end(), rf);
		f.merge(rf);
		f.unique();

		return true;
	}	

	if (node->label == "&") {		

		leftOK = DNF(node->left, lf);
		if (timeout()) return false;
		if (!leftOK) return false;	

		rightOK = DNF(node->right, rf);
		if (timeout()) return false;		
		if (!rightOK) return false;
		
		if (!lf.size()) {
			f = rf;
			return true;
		}
		else if (!rf.size()) {
			f = lf;
			return true;
		}
		else {			
			merge(lf, rf, f);			
		}				
		if (!f.size())
			return false;

		return true;
	}
	
	st.resize(m_literals.size());
	st[ground(node->label)] = 1;	
	f.push_back(st);
	return true;
}

bool Planner::inconsistent(const boost::dynamic_bitset<>& s) {
	int i;

	for (i = 0; i < s.size()-1; i += 2) {
		if (s[i] && s[i+1]) return true;
	}
	return false;
}


bool Planner::annul(const list<boost::dynamic_bitset<> >& lf, const list<boost::dynamic_bitset<> >& rf) {
	
	Literals f;
	Literal l;
	list<boost::dynamic_bitset<> >::const_iterator it;	
	
	for (it = rf.begin(); it != rf.end(); it++) {
		if (it->count() == 1)
			f.insert(it->find_first());
	}
	
	if (!f.size())
		return false;

	for (it = lf.begin(); it != lf.end(); it++) {
		if (it->count() == 1) {
			NEGATE(it->find_first(), l);
			if (f.count(l))
				return true;
		}
	}
	
	return false;
}

void Planner::add_clause(list<boost::dynamic_bitset<> >& cs, const boost::dynamic_bitset<>& st) {	
	set<int> si;
	set<int>::iterator it;
	list<boost::dynamic_bitset<> >::iterator its;

	if (inconsistent(st))	return;
	
	for (its = cs.begin(); its != cs.end(); its++) {
		if (its->is_subset_of(st))	return;
	}
	
	for (its = cs.begin(); its != cs.end(); ) {		
		if (st.is_proper_subset_of(*its))
			cs.erase(its);
		else
			its++;
	}
		
	cs.push_back(st);
}

void Planner::merge(list<boost::dynamic_bitset<> >& lf, list<boost::dynamic_bitset<> >& rf, list<boost::dynamic_bitset<> >& f) {
	list<boost::dynamic_bitset<> >::iterator its, its1, itsn;
	boost::dynamic_bitset<> st;
	bool include;	
	
	for (its = lf.begin(); its != lf.end(); ) {		
		itsn= its;
		itsn++;
		include = false;
		for (its1 = rf.begin(); its1 != rf.end() && !include; its1++) {			
			if (its1->is_subset_of(*its)) {				
				f.push_back(*its);
				if (its1->count() == its->count()) rf.erase(its1);				
				lf.erase(its);				
				include = true;				
				break;
			}
			if (include) break;			
		}				
		its = itsn;		
	}		
	

	for (its = rf.begin(); its != rf.end(); ) {
		itsn= its;
		itsn++;
		include = false;
		for (its1 = lf.begin(); its1 != lf.end() && !include; its1++) {
			if (its1->is_proper_subset_of(*its)) {
				f.push_back(*its);				
				rf.erase(its);
				include = true;
				break;
			}
			if (include) break;
		}						
		its = itsn;
	}
	
	for (its = rf.begin(); its != rf.end(); its++) {
		for (its1 = lf.begin(); its1 != lf.end(); its1++) {			
			st = *its | *its1;			
			if (!inconsistent(st)) f.push_back(st);
			//add_clause(f, st);				
		}
	}	
	f.sort();
	f.unique();	
}


// grounding functions
Literals Planner::ground(const StringList* x) const
{
  StringList::iterator it;
  Literals y;

  for (it = x->begin(); it != x->end(); it++) {
    y.insert(ground(*it));
  }

  return y;
}

Literal Planner::ground(const string& x) const
{
  map<string,Literal>::const_iterator p = m_map.find(x);

  if (p != m_map.end()) {
    return (p->second);
  }

  cout << "ERROR: Literal " << x << " is undeclared." << endl;
  cout << "Check the fluent declaration." << endl << endl;
  
  exit(1);
}

StringList Planner::convert(const Literals& x) const
{
  StringList y;
  Literals::iterator it;

  for (it = x.begin(); it != x.end(); it++) {
    y.insert(convert(*it));
  }

  return y;
}

string Planner::convert(const Literal& x) const
{
  unsigned short int i = x / 2;
  StringList::iterator it;

  if (i >= m_reader->m_fluents.size())
    return NULL;

  it = m_reader->m_fluents.begin();

  for (i = 0; i < x/2; i++) {
    it++;
  }

  if (x % 2 == 0)
    return *it;
  
  return (NEGATION_SYMBOL + (*it));
}


/* printing functions */
void Planner::print(const Literal& l) const
{
  cout << convert(l);
  //l % 2 == 0 ? (cout<<l/2) : cout<<"-"<<(l/2);
}

void Planner::print(const Literals& x) const
{
  Literals::iterator it;
  bool comma = false;
  for (it = x.begin(); it != x.end(); it++) {
    if (comma) 
      cout << ",";
    print(*it);
    comma = true;
  }
}

void Planner::print(const boost::dynamic_bitset<>& S) const
{
  Literals::iterator it;
  bool comma = false;

  for (boost::dynamic_bitset<>::size_type i = 0; i < S.size(); ++i) {
	  if (S[i]) {  
		if (comma) 
		  cout << ",";
		print(i);
		comma = true;
	  }
  }
}


void Planner::print_interal_domain() const
{
  ActionList::const_iterator it;
  
  cout << "DOMAIN DESCRIPTION" << endl;
  cout << "----------------------------" << endl;
  for (it = m_actions.begin();it != m_actions.end(); it++) {
    it->print();
    cout << endl;    
  }

  StaticLaws::const_iterator its;
  
  cout << "Static Laws: " << endl;

  for (its = m_statics.begin(); its != m_statics.end(); ++its) {
    cout << "    ";
    print(*its->get_head());
    cout << " <- ";
    print(*its->get_body());
    cout << endl;	  
  }

  // print init cstate
  cout <<  "INIT" << endl;
  cout <<  "----------------------------" << endl;
  m_init_cstate.print();
  cout << endl;

  // print goal state
  cout <<  "GOAL " << endl;
  cout <<  "----------------------------" << endl;
  print(m_goal);
  cout << endl;  

  // print statistics
  StringList2::const_iterator itst;
  
  cout <<  "STATISTICS " << endl;
  cout <<  "----------------------------" << endl;
  cout << "Total actions: " << m_actions.size() << endl;
  cout << "Total fluents: " << m_literals.size() / 2 << endl;
  cout << "Unknown fluents: " << endl;
  /*
  for (itst = m_reader->m_init.begin(); 
       itst != m_reader->m_init.end(); itst++) {
    cout << "\tState " << i++ << ": ";
    cout << m_literals.size()/2 - (*itst).size();
    cout << endl;
  }
  */
  cout << endl;
}


void Planner::print_summary() const
{
  cout <<  "SUMMARY" << endl;
  cout <<  "---------------------" << endl;
  cout <<  "Number of fluents: " << m_literals.size()/2 << endl;
  cout <<  "Number of actions: " << m_actions.size() << endl;
  cout <<  "Number of static laws: " << m_statics.size() << endl;
}

void Planner::print_statistics() const
{
  double total = m_timer->time(READ_TIMER) + 
    m_timer->time(BUILD_TIMER) + m_timer->time(SEARCH_TIMER);

  cout << "STATISTICS" << endl;
  cout << "---------------------" << endl;
  printf("Total time: %.3f (sec) \n",total);
#ifdef PRINT_TIME_DETAILS
  printf("  Reading: %.3f (sec) [%.2f %%]\n", 
	 m_timer->time(READ_TIMER), 
	 100.0 * m_timer->time(READ_TIMER) / total);
  printf("  Preprocessing: %.3f (sec) [%.2f %%]\n", 
	 m_timer->time(BUILD_TIMER),
	 100.0 * m_timer->time(BUILD_TIMER)/total);
  printf("  Search: %.3f (sec) [%.2f %%]\n", 
	 m_timer->time(SEARCH_TIMER),
	 100.0 * m_timer->time(SEARCH_TIMER)/total);
#endif  
  int i, states = 0, cstates = 0;
  for (i=0; i<HASH_SIZE; i++) {
	  states += m_states[i].size();
	  cstates += m_cstates[i].size();
  }
  set<State*>::iterator its;
  int size = 0;

  for (its = m_init_cstate.m_states.begin(); its != m_init_cstate.m_states.end(); its++)
	  size += (*its)->m_L.count();

  cout <<"Initial CState Size: States = " << m_init_cstate.m_states.size() << ", size = " << size<<endl;
  printf("Total states allocated: %d\n", states);
  printf("Total cstate(s): %d\n", cstates);
  printf("Total cstate(s) expanded: %d", m_expanded);
  //printf("Total cstate(s) expanded: %d, states: %d\n", m_expanded, m_expanded_states);
  //printf("Avg # of states expanded %.2f\n", double (double (m_expanded_states)/ double(m_expanded)));  
  //printf("Avg size # of expanded states %.2f\n", double (double (m_expanded_sum_state_size)/ double(m_expanded_states)));
}

bool Planner::execute()
{
  RawPlan::const_iterator it;
  int n_count = 0;
  CState *cs;
  const Action *act;
  map<string,int>::iterator it1;

  cs = &m_init_cstate;

  cout << endl << "STEP " << n_count++ << endl;
  cout << "CState: " << endl;  
  cs->print();
  if (cs->goal_satisfied())
    cout << " (GOAL)";
  
  cout << endl;

  for (it = m_plan.begin(); it != m_plan.end(); ++it) {
    it1 = m_action_map.find(*it);
    if (it1 == m_action_map.end()) {
      cout << endl << "ERROR: Could not find action " << *it 
	   << " in the source file." << endl;
      return false;
    }

    // execute the action   
    cout << "-> Action: " << *it << endl;
    act = &m_actions[it1->second];
    
    if (!act->is_executable(cs)) {
      cout << endl << "STOP: Action " << *it 
	   << " cannot be executed." << endl;
      return false;
    }

    cs = next_cstate(cs,act);
    
    // print the next state
    cout << endl << "STEP " << n_count++ << endl;
    cout << "CState:" << endl;
    cs->print();
    if (cs->goal_satisfied())
      cout << " (GOAL)";
    cout << endl;
  }
  
  return true;
}

Action* Planner::add_action(const string str)
{ 
  map<string,int>::iterator it;
  Action a(this,str);
  
  if (str.compare(0,9,"cpa_sense") && str.compare(0,5,"sense")) {  
	  it = m_action_map.find(str);
	  if (it == m_action_map.end()) {
		  // create a new entry	
			a.m_sensing = false;
			m_actions.push_back(a);
			m_action_map.insert(map<string,int>::value_type(str,m_actions.size()-1));
			return &(m_actions[m_actions.size()-1]);
	  }
	  return &(m_actions[it->second]);
  }

  //For sensing actions
  it = m_sensing_map.find(str);
  if (it == m_sensing_map.end()) {
	  // create a new entry			
	    a.m_sensing = true;
		m_sensings.push_back(a);
		m_sensing_map.insert(map<string,int>::value_type(str,m_sensings.size()-1));
		return &(m_sensings[m_sensings.size()-1]);
  } 
  return &(m_sensings[it->second]);

}

State* Planner::add_state(State* s)
{
  if (s->m_allocated) return s;
  pair<StateTable::iterator,bool> result;  
  result = m_states[s->hash()].insert(s);  
  if (!result.second) {
    // state exists
    delete s;
    return *result.first;
  }
  
  s->m_allocated = true;
  return s;
}


CState* Planner::next_cstate(CState* csin, const Action* act)
{
  set<State*>::iterator its;
  CState *csout, *cs, *cs1;

  EffectList::const_iterator it; 
  //vector<State*> cs;  

  static int count = 0;
  int maxcount = 0;
  
  if (++count <= maxcount) { cout << "Exploring CState: "; csin->print(); cout <<endl << "Action: ";  act->print(); fflush(stdout);}
  
  cs = new CState;
  cs->m_states = csin->m_states;  

  csout = new CState;

  for (it = act->get_effects()->begin(); it != act->get_effects()->end(); ++it) {	  
	  split_effect(cs, *it, csout);	
	  cs1 = cs; cs = csout; csout = cs1; csout->m_states.clear();	 
  }
    
  execute_effect(csout, cs);

  delete cs;

  if (count <= maxcount) {cout << "Next CState: "; csout->print(); fflush(stdout);cout<<endl;}

  return csout;
}

bool Planner::add_state(CState* cs, CState* csout, set<State*>::iterator its, State* s)
{
	set<State*>::iterator its1;	
	for (its1 = csout->m_states.begin(); its1 != csout->m_states.end(); its1++) {
		if (s->includes(*its1)) {
			delete s;
			return false;
		}
	}

	for (its1 = its, its1++; its1!= cs->m_states.end(); its1++) {
		if (s->includes(*its1)) {
			delete s;
			return false;
		}
	}

	if (s != *its) {
		s->m_EF = (*its)->m_EF;
		s->m_nondet_EF = (*its)->m_nondet_EF;
	}
	
	csout->m_states.insert(s);			
	return true;
}

void Planner::split_effect(CState* cs, const Effect& ef, CState* csout) {
	
	const Literals *bd;
	const Literals *hd;	
	Literal l;	
	Literals::iterator itl;
	Literals st;
	set<State*>::iterator its;
	State* s;

	bd = ef.get_body();
    hd = ef.get_head();    
	for (its = cs->m_states.begin(); its != cs->m_states.end(); its++) {
		if (!sat_value(*its, ef, &st)) {			
			csout->m_states.insert(*its);			
		}
		else { 
			if (!st.size()) {													
				if (!(*its)->m_allocated) {		
					if (!ef.nondet())
						(*its)->m_EF.insert(hd->begin(), hd->end());
					else
						(*its)->m_nondet_EF.insert(hd->begin(), hd->end());

					csout->m_states.insert(*its);									
				}
				else {					
					s = new State(this);
					s->m_L = (*its)->m_L;					
					if (!ef.nondet())
						s->m_EF.insert(hd->begin(), hd->end());
					else
						s->m_nondet_EF.insert(hd->begin(), hd->end());

					csout->m_states.insert(s);					
				}
			}
			else {					
				for (itl = st.begin(); itl != st.end(); itl++) {					
					NEGATE(*itl, l);
					s = new State(this);
					s->m_L = (*its)->m_L;
					s->m_L[l] = 1;					
					add_state(cs, csout, its, s);					
				}				
				if (!(*its)->m_allocated) {								
					(*its)->insert(st);
					if (add_state(cs, csout, its, *its)) {
						if (!ef.nondet())
							(*its)->m_EF.insert(hd->begin(), hd->end());
						else
							(*its)->m_nondet_EF.insert(hd->begin(), hd->end());
					}
				}
				else {					
					s = new State(this);
					s->m_L = (*its)->m_L;
					s->insert(st);
					if (add_state(cs, csout, its, s)){
						if (!ef.nondet())
							s->m_EF.insert(hd->begin(), hd->end());
						else
							s->m_nondet_EF.insert(hd->begin(), hd->end());
					}
				}
			}
		}
	}	
}

//Return false if not affects, true else. Set st contains unknown truth-value literals
bool Planner::sat_value(State* s, const Effect& ef, Literals* st) {
	Literals::const_iterator it_l;
	Literal l;
	set<State*>::const_iterator its;

	//If the state already includes the head of the effect so we just ignore it.
	if (s->includes(ef.get_head()))
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

void Planner::execute_effect(CState* csout, CState* cs){	
	
	static int times=0, count=0;
	static bool check = true, checkcheck = false;
	Literals::iterator itl;
	Literal l;
	set<State*>::iterator its, its1;

	if (!check) {
		for (its = cs->m_states.begin(); its != cs->m_states.end(); its++) {
			//New block for nondeterministic effects
			for (itl = (*its)->m_nondet_EF.begin(); itl != (*its)->m_nondet_EF.end(); itl++) {
					NEGATE(*itl,l);
					(*its)->m_L[l] = 0;
					(*its)->m_L[*itl] = 0;				
			}		
			(*its)->m_nondet_EF.clear();		
			
			for (itl = (*its)->m_EF.begin(); itl != (*its)->m_EF.end(); itl++) {				
					NEGATE(*itl,l);
					(*its)->m_L[l] = 0;
					(*its)->m_L[*itl] = 1;				
			}		
			(*its)->m_EF.clear();		
			csout->m_states.insert(add_state(*its));
		}
		return;
	}

	for (its = cs->m_states.begin(); its != cs->m_states.end(); its++) {
		for (itl = (*its)->m_nondet_EF.begin(); itl != (*its)->m_nondet_EF.end(); itl++) {
				NEGATE(*itl,l);
				(*its)->m_L[l] = 0;
				(*its)->m_L[*itl] = 0;			
		}				
		for (itl = (*its)->m_EF.begin(); itl != (*its)->m_EF.end(); itl++) {			
				NEGATE(*itl,l);
				(*its)->m_L[l] = 0;
				(*its)->m_L[*itl] = 1;			
		}				
	}	

	for (its = cs->m_states.begin(); its != cs->m_states.end(); its++) {
		
		if (!checkcheck) {		
			if (times>500 && count<2) {
				cout << "No check, count(500) = " <<count << endl;
				check = false;
				checkcheck = true;
			}

			if (times>5000) {
				if (20*count<times) {
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
			for (its1=csout->m_states.begin(); its1 != csout->m_states.end(); its1++) {
				times++;
				if ((*its)->includes(*its1)) {
					count++;
					break;
				}
			}

			if (its1 != csout->m_states.end()) {
				if (!(*its)->m_allocated)
					delete *its;
				continue;
			}

			for (its1 = its, its1++ ; its1 != cs->m_states.end(); its1++) {
				times++;
				if ((*its)->includes(*its1)) {
					count++;
					break;
				}
				
				if (!checkcheck && times>2000 && count<5) {
					its1 = cs->m_states.end();
					break;
				}
			}
			if (its1 != cs->m_states.end()) {
				if (!(*its)->m_allocated)
					delete *its;
				continue;
			}
		}
		(*its)->m_nondet_EF.clear();
		(*its)->m_EF.clear();		
		csout->m_states.insert(add_state(*its));
	}	
}


Literals Planner::negate(const Literals& x) const
{
  Literals::const_iterator it;
  Literals y; // output literals
  Literal l;
  
  for (it = x.begin(); it != x.end(); ++it) {
    NEGATE(*it,l);
    y.insert(l);
  }
  return y;
}


CState* Planner::first_unexpanded()
{	
	CState* cs;	

	while (m_queue.size() && (m_queue.top()->m_status != UNEXPANDED)) {
		if (m_queue.top()->m_status == ISOLATED)
			m_queue.top()->m_status = OUT_ISOLATED;
		m_queue.pop();	
	}

	if (m_queue.size()) {
		cs = m_queue.top();
		m_queue.pop();
		return cs;
	}

	return NULL;
}


bool Planner::search()
{
  CState *cs;  
  set<State*>::iterator its;
	
  if (m_init_cstate.goal_satisfied()) {
    cout << "The initial state satisies the goal " << endl;
	return true;
  }
  
  m_init_cstate.m_status = UNEXPANDED;
  m_expanded = 0;
  //m_expanded_states =0;
  //m_expanded_sum_state_size =0;
  m_queue.push(&m_init_cstate);
  m_cstates[m_init_cstate.hash()].insert(&m_init_cstate);  

  while ((cs = first_unexpanded())) {	  
	  m_expanded++;
	  //m_expanded_states += cs->m_states.size();	  
	  //for (its = cs->m_states.begin(); its != cs->m_states.end(); its++) {
	 //	  m_expanded_sum_state_size += (*its)->m_L.count();
	 // }
	  if (expand(cs))
		  break;
  }    
  
  // m_status: 0-unexplored, 1-explored, 2-goal_reachable, -1-dead_end,	-2-isolated
  if (m_init_cstate.m_status != GOAL_REACHABLE) {
    cout << "No plan was found." << endl;
	return false;
  }
  
  cout << endl << "  Found a plan: " <<endl;
  m_depth = 0;
  //m_init_cstate.solution_not_print(this,0);
  m_init_cstate.solution_print(this,0);
  cout <<"Size of solution: " << m_commandNo.size() <<"\t Depth: " << m_depth << endl;

  return true;
}

//Return true if search is terminated
bool Planner::expand(CState *cs)
{
  CState *cs1, *cs2;
  const Action *act;
  ActionList::const_iterator it;    
  CStateTable::iterator it2;
  static int maxhvalue =-1;  

  if (maxhvalue < cs->hvalue()) {
	  maxhvalue = cs->hvalue();
	  cout <<"maxh = "<< maxhvalue << ", cs size = "<< cs->m_states.size()<<" "; fflush(stdout);
  }

  //Usual actions
  for (it = m_actions.begin(); it != m_actions.end(); it++) {
	  act = &(*it);    		
	  if (!act->is_executable(cs)) 
		  continue;	  	  	
	  //execs++;	
	  cs1 = next_cstate(cs,act);
	  
	  new_action_transition(cs, act, cs1);	  	  	  
		
	  //Terminate the search when the initial state reaches the goal or a dead-end	  
	  if (m_init_cstate.m_status == GOAL_REACHABLE)
		  return true;

	  if (cs->m_status == GOAL_REACHABLE)
		  return false;	  
  }  

  //Sensing actions
  for (it = m_sensings.begin(); it != m_sensings.end(); it++) {
	  act = &(*it); 
	  if (!act->is_executable(cs) || cs->decides(act->lit())) {		  
		  continue;	  
	  }
	  cs1 = new CState;
	  cs2 = new CState;
	  cs->split(cs1, cs2, act->lit());	  
	  new_sensing_transition(cs, act, cs1, cs2);

	  if (m_init_cstate.m_status == GOAL_REACHABLE)
		  return true;
	  
	  if (cs->m_status == GOAL_REACHABLE)
		  return false;
  }  

  if (!cs->m_successors.size()) {
	  cs->m_status = DEAD;
	  cout << "DEAD " << cs << endl;
	  dead_propagate(cs);
	  if (m_init_cstate.m_status == DEAD)
		  return true;
  }

  return false;
}

//act: cs -> cs1
bool Planner::new_action_transition(CState* cs, const Action *act, CState* cs1)
{	
	CStateTable::iterator it;	
	int hash;	

	hash = cs1->hash();	
	
	it = m_cstates[hash].find(cs1);	 
	  
	if (it == m_cstates[hash].end()) {			
		if (cs1->goal_satisfied()) {			
			cs1->m_status = GOAL_REACHABLE;			
			cs->m_status = GOAL_REACHABLE;
			goal_propagate(cs, cs1);	
		}	  
		else {			
			m_queue.push(cs1);
			//m_queue1.push(cs1);
		}
		m_cstates[hash].insert(cs1);		
	}
	else {		
		delete cs1;
		cs1 = *it;		
		//Dead-end
		if (cs1 == cs || cs1->m_status == DEAD)
			return false;		

		if (cs1->m_status == GOAL_REACHABLE) {			
			cs->m_status = GOAL_REACHABLE;
			goal_propagate(cs,cs1);
		}		
		else {// cs1 is EXPANDED
			reconnection_propagate(cs1);
		}
	}	
	cs->m_successors.push_back(cs1);
	cs1->m_in_transitions.insert(pair<CState*,const Action*>(cs,act));	

	return true;
}

bool Planner::new_sensing_transition(CState* cs, const Action *act, CState* cs1, CState* cs2)
{	
	CStateTable::iterator it1, it2;	
	int hash1, hash2;    
	hash1 = cs1->hash();
	it1 = m_cstates[hash1].find(cs1);
	
	hash2 = cs2->hash();
	it2 = m_cstates[hash2].find(cs2);
		
	if ((it1 != m_cstates[hash1].end() && (*it1)->m_status == DEAD) || 
		(it2 != m_cstates[hash2].end() && (*it2)->m_status == DEAD )) {
			delete cs1;
			delete cs2;
			return false;
	}


	if ((it1 != m_cstates[hash1].end() && ((*it1)->m_status == ISOLATED || (*it1)->m_status == OUT_ISOLATED)) &&
		(it2 != m_cstates[hash2].end() && ((*it2)->m_status == ISOLATED || (*it2)->m_status == OUT_ISOLATED))) {
			delete cs1;
			delete cs2;
			cout << "ISOLATION, IGNORE SENSING";
			return false;
	}

	//Treat cs1	  
	if (it1 == m_cstates[hash1].end()) {
		if (cs1->goal_satisfied())			
			cs1->m_status = GOAL_REACHABLE;										
		m_queue.push(cs1);		
		//m_queue1.push(cs1);
		m_cstates[hash1].insert(cs1);		  
	}
	else {
		delete cs1;
		cs1 = *it1;		
		cs1->m_active_in_transitions++;				
		if (cs1->m_status == ISOLATED) {
			cs1->m_status = UNEXPANDED;
		}
		else if (cs1->m_status == OUT_ISOLATED) {
			cs1->m_status = UNEXPANDED;
			m_queue.push(cs1);
			//m_queue1.push(cs1);
		}		
	}
	cs->m_successors.push_back(cs1);
	cs1->m_in_transitions.insert(pair<CState*,const Action*>(cs,act));	
	
	//Treat cs2
	if (it2 == m_cstates[hash2].end()) {		
		if (cs2->goal_satisfied()){			
			cs2->m_status = GOAL_REACHABLE;	
			if (cs1->m_status == GOAL_REACHABLE) {
				cs->m_status = GOAL_REACHABLE;
				goal_propagate(cs,cs1,cs2);
			}
		}		
		m_queue.push(cs2);
		//m_queue1.push(cs2);
		m_cstates[hash2].insert(cs2);
	}
	else {
		delete cs2;
		cs2 = *it2;		
		cs2->m_active_in_transitions++;
		if (cs2->m_status == GOAL_REACHABLE) {			
			if (cs1->m_status == GOAL_REACHABLE) {
				cs->m_status = GOAL_REACHABLE;
				goal_propagate(cs,cs1,cs2);
			}
		}
		else if (cs2->m_status == ISOLATED) {
			cs2->m_status = UNEXPANDED;
		}
		else if (cs2->m_status == OUT_ISOLATED) {
			cs2->m_status = UNEXPANDED;			
			m_queue.push(cs2);
			//m_queue1.push(cs2);
		}
		else {// cs2 is EXPANDED
			reconnection_propagate(cs2);
			if (cs1->m_status == EXPANDED) {
				reconnection_propagate(cs1);
			}
		}
	}
	cs->m_successors.push_back(cs2);
	cs2->m_in_transitions.insert(pair<CState*,const Action*>(cs,act));		
	return true;
}

void Planner::goal_propagate(CState* cs, CState* suc_goal)
{
	vector<CState*>::iterator itcs;	
	map<CState*,const Action*>::iterator it;
		
	for (itcs = cs->m_successors.begin(); itcs != cs->m_successors.end(); itcs++) {
		if (*itcs != suc_goal) {
			isolation_propagate(*itcs);					
			(*itcs)->m_in_transitions.erase(cs);
		}
	}

	//Only keep the outgoing transition(s) to the goal node(s)
	cs->m_successors.clear();
	cs->m_successors.push_back(suc_goal);		
	
	for (it = cs->m_in_transitions.begin(); it != cs->m_in_transitions.end(); it++) {
		if (it->second->m_sensing) {
			//Two complement successors should be next to one another
			for (itcs = it->first->m_successors.begin(); itcs != it->first->m_successors.end(); itcs++) {
				if ((*itcs)->is_successor(it->first, it->second))
					break;
			}
			//The complement of cs should be next to cs
					
			if (*itcs == cs) {
				itcs++;
				if ((*itcs)->m_status == GOAL_REACHABLE) {
					it->first->m_status = GOAL_REACHABLE;
					goal_propagate(it->first, cs, *itcs);
				}
			}
			else {								
				if ((*itcs)->m_status == GOAL_REACHABLE) {
					it->first->m_status = GOAL_REACHABLE;
					goal_propagate(it->first, *itcs, cs);
				}				
			}					
		}
		else {
			it->first->m_status = GOAL_REACHABLE;
			goal_propagate(it->first, cs);
		}
	}
}

void Planner::goal_propagate(CState* cs, CState* suc_goal1, CState* suc_goal2)
{
	vector<CState*>::iterator itcs;	
	map<CState*,const Action*>::iterator it;
		
	for (itcs = cs->m_successors.begin(); itcs != cs->m_successors.end(); itcs++) {
		if (*itcs != suc_goal1 && *itcs != suc_goal2) {
			isolation_propagate(*itcs);					
			(*itcs)->m_in_transitions.erase(cs);
		}
	}

	//Only keep the outgoing transition(s) to the goal node(s)
	cs->m_successors.clear();
	cs->m_successors.push_back(suc_goal1);
	cs->m_successors.push_back(suc_goal2);
	
	for (it = cs->m_in_transitions.begin(); it != cs->m_in_transitions.end(); it++) {
		if (it->second->m_sensing) {
			//Two complement successors should be next to one another
			for (itcs = it->first->m_successors.begin(); itcs != it->first->m_successors.end(); itcs++) {
				if ((*itcs)->is_successor(it->first, it->second))
					break;
			}
			//The complement of cs should be next to cs
					
			if (*itcs == cs) {
				itcs++;
				if ((*itcs)->m_status == GOAL_REACHABLE) {
					it->first->m_status = GOAL_REACHABLE;
					goal_propagate(it->first, cs, *itcs);
				}
			}
			else {								
				if ((*itcs)->m_status == GOAL_REACHABLE) {
					it->first->m_status = GOAL_REACHABLE;
					goal_propagate(it->first, *itcs, cs);
				}				
			}					
		}
		else {
			it->first->m_status = GOAL_REACHABLE;
			goal_propagate(it->first, cs);
		}
	}
}

void Planner::dead_propagate(CState* cs)
{	
	map<CState*,const Action*>::iterator it;
	vector<CState*>::iterator itcs;			
	while (cs->m_in_transitions.size()) {
		it = cs->m_in_transitions.begin();
		if (it->second->m_sensing) {			
			//Two complement successors should be next to one another
			for (itcs = it->first->m_successors.begin(); itcs != it->first->m_successors.end(); itcs++) {				
				if ((*itcs)->is_successor(it->first, it->second))
					break;
			}
			//The complement of cs should be next to cs
					
			if (*itcs == cs) {
				itcs++;
				isolation_propagate(*itcs);				
				(*itcs)->m_in_transitions.erase(it->first);								
				it->first->m_successors.erase(itcs-1, itcs+1);				
			}
			else {										
				isolation_propagate(*itcs);				
				(*itcs)->m_in_transitions.erase(it->first);
				it->first->m_successors.erase(itcs, itcs+2);				
			}			
			if (!it->first->m_successors.size()) {
				it->first->m_status = DEAD;
				dead_propagate(it->first);
			}
		}
		else {
			for (itcs = it->first->m_successors.begin(); itcs != it->first->m_successors.end(); itcs++) {
				if (*itcs == cs)
					break;
			}
			it->first->m_successors.erase(itcs);
			if (!it->first->m_successors.size()) {
				it->first->m_status = DEAD;
				dead_propagate(it->first);
			}
		}
		cs->m_in_transitions.erase(it);
	}	
}

void Planner::isolation_propagate(CState* cs)
{
	//return;
	vector<CState*>::iterator itcs;			
	cs->m_active_in_transitions--;
	if (cs->m_active_in_transitions || cs->m_status == GOAL_REACHABLE)
		return;	

	if (cs->m_status == UNEXPANDED) {
		cs->m_status = ISOLATED;
		return;
	}	

	for (itcs = cs->m_successors.begin(); itcs != cs->m_successors.end(); itcs++) {		
		isolation_propagate(*itcs);
	}
}

void Planner::reconnection_propagate(CState* cs)
{
	//return;
	vector<CState*>::iterator itcs;
	cs->m_active_in_transitions++;
	if (cs->m_active_in_transitions > 1 || cs->m_status == GOAL_REACHABLE)
		return;
	if (cs->m_status == ISOLATED) 
		cs->m_status = UNEXPANDED;
	else if (cs->m_status == OUT_ISOLATED) {
		cs->m_status = UNEXPANDED;		
		m_queue.push(cs);
		//m_queue1.push(cs);
	}
	else {// cs1 is EXPANDED
		for (itcs = cs->m_successors.begin(); itcs != cs->m_successors.end(); itcs++)		
			reconnection_propagate(*itcs);
	}
}