#include "action.h"
#include "planner.h"

/*********************************************************************
 Conditional effect implementation
**********************************************************************/
Effect::Effect()
{

}
Effect::~Effect()
{

}

void Effect::set_body(Literals bd) 
{  
  m_body = bd;  
}

void Effect::set_head(Literals hd) 
{
	Literals::iterator it;
	Literal l;
	if (hd.size() == 2) {
		it = hd.begin();
		NEGATE(*it, l);
		it++;
		if (*it == l) {
			m_head.insert(*hd.begin());
			m_nondet = true;
			return;
		}
	}
	m_head = hd;    
	m_nondet = false;
}

bool Effect::nondet() const
{
	return m_nondet;
}

const Literals* Effect::get_body() const 
{
  return &m_body;
}

const Literals* Effect::get_head() const 
{
  return &m_head;
}

/*********************************************************************
 Action implementation
**********************************************************************/
/* constructor and destructor */
Action::Action(const Planner* planner, const string& name) 
{
  m_planner = planner;
  m_name = name;  
}

Action::~Action()
{
  
}

/* get & set functions */
void Action::set_name(const string& name) {
  m_name = name;
}

string Action::get_name() const
{
  return m_name;
}

void Action::add_independent(Action* a)
{
	m_independents.insert(a);
}

bool Action::is_independent(Action* a) const
{
	return m_independents.count(a);
}



/* main functions */
void Action::add_exec(const Literals ex)
{
  m_execs.push_back(ex);
}

void Action::add_imposs(const Literals imp)
{
  m_imposs.push_back(imp);
}

void Action::add_effect(const Literals hd, const Literals bd)
{
  Effect ef;

  ef.set_head(hd); 
  ef.set_body(bd);

  m_effects.push_back(ef);
  m_EF.insert(hd.begin(),hd.end());
}

const EffectList* Action::get_effects() const
{
  return &m_effects;
}

//For sensing actions
const Literal Action::lit() const
{
  return *m_effects.begin()->get_head()->begin();
}


const ExecList* Action::get_execs() const
{
  return &m_execs;
}

const ExecList* Action::get_imposs() const
{
  return &m_imposs;
}

bool Action::is_executable(const State* s) const
{
  list<Literals>::const_iterator it;
  Literals x;

  // check impossibility conditions
  for (it = get_imposs()->begin(); 
       it != get_imposs()->end(); ++it) {
    // if the body of an impossiblity is empty
    // then the action is non-executable
    if (it->empty()) {
      return false;
    }

    x = m_planner->negate(*it);
    if (!s->intersect(&x)) {
      return false;
    }
  }

  // default is executable
  if (get_execs()->empty()) {
    return true;
  }

  for (it = get_execs()->begin(); 
       it != get_execs()->end(); ++it) {
    if (s->includes(&(*it))) {
      return true;
    }
  }
  return false;
}

bool Action::is_executable(const Literals* s) const
{
  list<Literals>::const_iterator it;
  Literals x;

  // default is executable
  if (get_execs()->empty())
    return true;
  
  for (it = get_execs()->begin(); it != get_execs()->end(); ++it) {
    if (includes(s->begin(),s->end(), it->begin(),it->end()))  
      return true; 
  }
  return false;
}

bool Action::noEffectIn(const boost::dynamic_bitset<>& L) const
{
	Literals::const_iterator itl;

	for (itl = m_EF.begin(); itl != m_EF.end(); itl++) {
		if (!L[*itl])
			return false;
	}
	
	return true;
}

bool Action::is_executable(const boost::dynamic_bitset<>& L) const
{	
	list<Literals>::const_iterator it;
	Literals::const_iterator it_l;
	
	// default is executable
	if (get_execs()->empty())
		return true;
	
	for (it = get_execs()->begin(); it != get_execs()->end(); ++it) {
		for (it_l = it->begin(); it_l != it->end(); it_l++) {
			if (!L[*it_l])
				break;
		}

		if (it_l == it->end())
			return true;
	}	
	
	return false;
}

bool Action::pre(const boost::dynamic_bitset<>& L, Literals* st) const
{	
	list<Literals>::const_iterator it;
	Literals::const_iterator it_l;	
	
	// default is executable
	if (get_execs()->empty())
		return false;
	
	for (it = get_execs()->begin(); it != get_execs()->end(); ++it) {
		for (it_l = it->begin(); it_l != it->end(); it_l++) {
			if (!L[*it_l])
				break;
		}

		if (it_l == it->end()) {
			*st = *it;
			return true;
		}
	}	
	
	return false;
}


bool Action::is_executable(const CState* cs) const
{
  set<State*>::const_iterator it;

  for (it = cs->m_states.begin(); it != cs->m_states.end(); it++) {
	if (!is_executable(*it))
	  return false;
  }

  return true;
}

bool Action::is_executable(const set<State*>* cs) const
{
  set<State*>::const_iterator it;

  for (it = cs->begin(); it != cs->end(); it++) {
	if (!is_executable(*it))
	  return false;
  }

  return true;
}


void Action::print() const
{
  list<Literals>::const_iterator it1;	
  EffectList::const_iterator it2;

  cout << get_name() << endl;
  // print executability condition
  cout << "    Executability:\n";
  for (it1 = get_execs()->begin(); it1 != get_execs()->end(); ++it1) {
    cout << "\t";
    m_planner->print(*it1);
    cout << endl;
  }	

  cout << "    Imposibility:\n";
  for (it1 = get_imposs()->begin(); 
       it1 != get_imposs()->end(); ++it1) {
    cout << "\t";
    m_planner->print(*it1);
    cout << endl;
  }

  // print conditional effects
  cout << "    Conditional Effects\n";	
  for (it2 = get_effects()->begin(); 
       it2 != get_effects()->end(); ++it2) {
    cout << "\t";
    m_planner->print(*it2->get_head());
    cout << " <- ";
    m_planner->print(*it2->get_body());
    cout << endl;	  
  }
}
