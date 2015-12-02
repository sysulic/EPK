#include "reader.h"

Reader reader;

int yyparse();

void printTree(Formula & f, size_t deep) {
	for (int i = 0; i < deep; i++) cout << " ";
	cout << f.label << endl;
	if (f.left != NULL)
	{
		if (f.left->label == "same") f.left->label = f.label;
		printTree(*(f.left), deep+1);
	}
	if (f.right != NULL)
	{
		if (f.right->label == "same") f.right->label = f.label;
		printTree(*(f.right), deep+1);
	}
}

void removeImply(Formula & f) {
	if(f.label == "->")
	{
		Formula* leftF = new Formula();
		leftF->label = "!";
		leftF->left = f.left;

		f.label = "|";
		f.left = leftF;
	}
	if (f.left != NULL)
	{
		removeImply(*(f.left));
	}
	if (f.right != NULL)
	{
		removeImply(*(f.right));
	}
	return;
}

void removeOneof(Formula & f) {
	if(f.label == "oneof")
	{
		vector<Formula*> oneof_vector, prop_vector;
		// process oneof
		prop_vector.push_back(f.right);
		Formula* pf = f.left;
		bool temp = false;
		while (pf->label == "oneof") {
			oneof_vector.push_back(pf);
			prop_vector.push_back(pf->right);
			pf = pf->left;
			temp = true;
		}
		if (temp) prop_vector.push_back(pf);  // leftest leaf of oneof
		else prop_vector.push_back(pf->left);

		// print for debug
		vector<Formula*>::iterator it = prop_vector.begin();
		for ( ; it != prop_vector.end(); it++)
		{
			cout << (*it)->label << endl;
		}

/*
		// construct left
		Formula* f11 = new Formula(*f.left);  // "1" means "left", "2" means "right"
		Formula* f121 = new Formula(*f.right);  // sequence means deepth
		Formula* f12 = new Formula(*f.right); f12->label = "!"; f12->left = f121; f12->right = NULL;
		Formula* f1 = new Formula; f1->label = "&"; f1->left = f11; f1->right = f12;
		// construct right
		Formula* f21 = new Formula; f21->label = "!"; f21->left = f.left; f21->right = NULL;
		Formula* f2 = new Formula; f2->label = "&"; f2->left = f21; f2->right = f.right;

		f.label = "|";
		f.left = f1;
		f.right = f2;
		*/

	return;
	}
	if (f.left != NULL)
	{
		removeOneof(*(f.left));
	}
	if (f.right != NULL)
	{
		removeOneof(*(f.right));
	}
	return;
}

void toDNF(Formula & f) {
	return;
}

void convertToDNFTree(Formula & f) {
	removeImply(f);
	removeOneof(f);
	toDNF(f);
	return;
}

int main() {

	const char* dFile="../epddl-doc/demo/demo_domain.epddl";  // 打开要读取的文本文件
	const char* pFile="../epddl-doc/demo/demo_p.epddl";  // 打开要读取的文本文件
	FILE* fp_d=fopen(dFile, "r");
	FILE* fp_p=fopen(pFile, "r");
	if(fp_d==NULL)
	{
		printf("cannot open %s\n", dFile);
		return -1;
	}
	if(fp_p==NULL)
	{
		printf("cannot open %s\n", pFile);
		return -1;
	}
	puts("-----begin parsing");
	extern FILE* yyin;  // yyin和yyout都是FILE*类型
	yyin = fp_d;  // yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的
	yyparse();
	yyin = fp_p;
	yyparse();
	puts("-----end parsing");
	fclose(fp_d);
	fclose(fp_p);
	cout << endl;
	
	// final structure
	map<string, int> atomicByName;
	map<int, string> atomicByIndex;

	// prop table ****
	size_t atomicCounter = 0;
	for (set<string>::iterator it = reader.atomicPropSet.begin();
			it != reader.atomicPropSet.end(); ++it) {
		cout << *it << endl;
		atomicByName.insert( pair<string, int>(*it, atomicCounter++) );
		atomicByIndex.insert( pair<int, string>((atomicCounter), *it) );
	}
	atomicCounter--;

	// print init
	cout << "------Begin-----init Tree-------------------" << endl;
	printTree(reader.init, 0);
	cout << "-------End------init Tree-------------------" << endl;
	
	convertToDNFTree(reader.init);
	printTree(reader.init, 0);

	// print goal
	//cout << "------Begin-----goal Tree-------------------" << endl;
	//searchTree(reader.goal);
	//cout << "-------End------goal Tree-------------------" << endl;


/*
	// prop grounding **
	for (PredicateSet::iterator predi = reader.predicates.begin();
			predi != reader.predicates.end(); ++predi) {
		for (MultiTypeSet::iterator type = (*predi).second.begin();
				type != (*predi).second.end(); ++type) {
			// find objects to the specific type
			for (MultiTypeSet::iterator obj = reader.objects.begin();
					obj != reader.objects.end(); ++obj) {
				if((*type).first == (*obj).first) {
					for (StringSet::iterator ob = (*obj).second.begin();
						ob != (*obj).second.end(); ++ob)
					{
						cout << *ob << endl;
						atomicByName.insert( pair<string, int>(*ob, atomicCounter++) );
						atomicByIndex.insert( pair<int, string>((atomicCounter), *ob) );
					}
				}
			}
		}
	}
*/
	// node to DNF and CNF



	return 0;
}

//bool Planner::DNF(const Node* node, list<boost::dynamic_bitset<> >& f) {
	
//}

/*
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
*/
