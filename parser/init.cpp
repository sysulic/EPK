#include "reader.h"


Reader reader;

int yyparse();

void printTree(Formula & f, size_t deep) {
	for (int i = 0; i < deep; i++) cout << " ";
	cout << f.label << endl;
	if (f.left != NULL)
	{
		if (f.left->label == "same") f.left->label = f.label;
		// cout << "left\n";
		printTree(*f.left, deep+1);
	}
	if (f.right != NULL)
	{
		if (f.right->label == "same") f.right->label = f.label;
		// cout << "right\n";
		printTree(*f.right, deep+1);
	}
}

/*
 * The function is to replace all "->"s in
 * binary tree with "|" and "!".
 *
 * E.g:
 *             A -> B <=> ¬A V B
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | imply (A) |     imply     |       |      |
 * |       (B) |     /   \     |     /   \    |
 * |           |    A    B     |    !    B    |
 * |           |               |    A         |
 *  ------------------------------------------
 */
void removeImply(Formula & f) {
	Formula* leftF = new Formula("!", f.left, NULL);
	f.label = "|";
	f.left = leftF;
}

/*
 * The function is to replace all "oneof"s in binary tree
 * with "&", "|" and "!".
 *
 * E.g:
 *  oneof (A) (B) (C) <=> (¬A^B^C) V (A^¬B^C) V (A^B^¬C)
 *  ----------------------------------------------------
 * | epddl-doc | before b-tree |      after b-tree      |
 *  ----------------------------------------------------
 * | oneof (A) |     oneof     |               |        |
 * |       (B) |     /   \     |           /       \    |
 * |       (C) |  oneof  C     |          |         &   |
 * |           |   / \         |        /   \     /   \ |
 * |           |  A  B         |       &    &    &    ! |
 * |           |               |      /\   /\   /\   /  |
 * |           |               |     & C  & C  A B  C   |
 * |           |               |    / \  / \            |
 * |           |               |   !  B A  !            |
 * |           |               |  /       /             |
 * |           |               | A       B              |
 *  ----------------------------------------------------
 */
void removeOneof(Formula & f) {
	// cout << "In function removeOneof, root: " f.label << "\n";
	f.label = "|";
	vector<Formula*> clause_vec;  // points to each prop in the leaf
	vector<string> prop_vec;  // props in the leaf
	if (f.right == NULL) {
		cout << "Warning: at least two atomic propositions with oneof!\n";
		return;
	}
	clause_vec.push_back(f.right);
	prop_vec.push_back(f.right->label);
	Formula* pf = f.left;
	bool only_oneof = false;
	while (pf->label == "oneof") {
		pf->label = "|";
		clause_vec.push_back(pf->right);
		prop_vec.push_back(pf->right->label);
		pf = pf->left;
		only_oneof = true;
	}
	if (only_oneof) { 
		clause_vec.push_back(pf);  // leftest leaf of oneof
		prop_vec.push_back(pf->label);
	} else {
		clause_vec.push_back(pf);
		prop_vec.push_back(pf->label);	
	}

// cout << clause_vec.size() << endl;
// cout << prop_vec.size() << endl;

	const size_t prop_size = prop_vec.size();
	vector<Formula*>::iterator clause_it = clause_vec.begin();
	// neg_counter - a tag for locating which literal should be the negative
	for (int neg_counter = 0; clause_it != clause_vec.end(); clause_it++, neg_counter++)
	{
		// generate a CNF in place of the prop in every leaf
		size_t i;
		for (i = 0; i < prop_size-1; i++)
		{
			(*clause_it)->label = "&";
			(*clause_it)->left = new Formula();
			if (i == neg_counter) {
				(*clause_it)->right = new Formula("!");
				(*clause_it)->right->left = new Formula(prop_vec.at(i));
			} else {
				(*clause_it)->right = new Formula(prop_vec.at(i));
			}
			*clause_it = (*clause_it)->left;
		}
		if (i == neg_counter) {
			(*clause_it)->label = "!";
			(*clause_it)->left = new Formula(prop_vec.at(i));
		} else {
			(*clause_it)->label = prop_vec.at(i);
		}
	}
	// cout << "In function removeOneof, root: " f.label << " doen\n";
}

/*
 * The function is to move all "!"s to the
 * front of atomic propositions
 *
 * E.g:
 *           ¬(A ^ B) <=> ¬A V ¬B
 *           ¬(A V B) <=> ¬A ^ ¬B
 *  ------------------------------------------
 * | epddl-doc | before b-tree | After b-tree |
 *  ------------------------------------------
 * | not(and   |        !      |        |     |
 * |       (A) |       /       |      /   \   |
 * |       (B) |      &        |     !    !   |
 * |    )      |     / \       |    /    /    |
 * |           |    A  B       |   A    B     |
 *  ------------------------------------------
 * | not(or    |        !      |        &     |
 * |       (A) |       /       |      /   \   |
 * |       (B) |      |        |     !    !   |
 * |    )      |     / \       |    /    /    |
 * |           |    A  B       |   A    B     |
 *  ------------------------------------------
 */
void inwardMoveNot(Formula & f) {
	// cout << "In function inwardMoveNot, root: " << f.label << "\n";
	Formula* r = new Formula("!", f.left->right, NULL);

	if (f.left->label == "&") f.label = "|";
	else f.label = "&";
	f.right = r;

	f.left->right = NULL;
	f.left->label = "!";
	// cout << "In function inwardMoveNot, root: " << f.label << " doen\n";
	return;
}

/*
 * The function is to move all "&"s to the
 * underneath of all "|"s by distributive law.
 *
 * E.g:
 *        (AVB) ^ C <=> A^C V B^C
 *        A ^ (BVC) <=> A^B V A^C
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | and(or    |       &       |       |      |
 * |       (A) |      / \      |     /   \    |
 * |       (B) |     |  C      |    &    &    |
 * |    )      |    / \        |   / \  / \   |
 * |    (C)    |   A  B        |  A  C B  C   |
 *  ------------------------------------------
 * | and(A)    |       &       |       |      |
 * |    (or    |      / \      |     /   \    |
 * |       (B) |     A  |      |    &    &    |
 * |       (C) |       / \     |   / \  / \   |
 * |    )      |      B  C     |  A  B A  C   |
 *  ------------------------------------------
 */
void inwardMoveAnd(Formula & f) {
	// cout << "In function inwardMoveAnd, root: " << f.label << "\n";
	if (f.left->label == "|") {
		Formula* rr = new Formula(*f.right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("&", f.left->right, rr);
		f.left->right = f.right;
		f.left->label = "&";
		f.right = r;
		f.label = "|";
	// cout << "left label is | : doen\n";
	} else {
		Formula* ll = new Formula(*f.left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("&", ll, f.right->left);
		f.right->left = f.left;
		f.right->label = "&";
		f.left = l;
		f.label = "|";
	// cout << "left label is & : doen\n";
	}
	// cout << "In function inwardMoveAnd, root: " << f.label << " doen\n";
	return;
}

/*
 * The function is to move all "|"s to the
 * underneath of all "&"s by distributive law.
 *
 * E.g:
 *        A^B V C <=> (AVC) ^ (BVC)
 *        A V B^C <=> (AVB) ^ (AVC)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | or(and    |       |       |       &      |
 * |       (A) |      / \      |     /   \    |
 * |       (B) |     &  C      |    |    |    |
 * |   )       |    / \        |   / \  / \   |
 * |   (C)     |   A  B        |  A  C B  C   |
 *  ------------------------------------------
 * | or (A)    |       |       |       &      |
 * |    (and   |      / \      |     /   \    |
 * |       (B) |     A  &      |    |    |    |
 * |       (C) |       / \     |   / \  / \   |
 * |    )      |      B  C     |  A  B A  C   |
 *  ------------------------------------------
 */
void inwardMoveOr(Formula & f) {
	// cout << "In function inwardMoveAnd, root: " << f.label << "\n";
	if (f.left->label == "&") {
		Formula* rr = new Formula(*f.right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("|", f.left->right, rr);
		f.left->right = f.right;
		f.left->label = "|";
		f.right = r;
		f.label = "&";
	// cout << "left label is | : doen\n";
	} else {
		Formula* ll = new Formula(*f.left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("|", ll, f.right->left);
		f.right->left = f.left;
		f.right->label = "|";
		f.left = l;
		f.label = "&";
	// cout << "left label is & : doen\n";
	}
	// cout << "In function inwardMoveAnd, root: " << f.label << " doen\n";
	return;
}

void convertToDNFTree(Formula & f) {
	if (f.label == "->")
		removeImply(f);
	if (f.label == "oneof")
		removeOneof(f);
	if (f.label == "!" &&
		(f.left->label == "&" || f.left->label == "|"))
			inwardMoveNot(f);
	if (f.label == "&") {
		/* several cases to make algorithm complete */
		if (f.left->label == "->")
			removeImply(*f.left);
		if (f.right->label == "->")
			removeImply(*f.right);
		if (f.left && f.left->label == "!" &&
			(f.left->left->label == "&" || f.left->left->label == "|"))
			inwardMoveNot(*f.left);
		if (f.right && f.right->label == "!" &&
			(f.right->left->label == "&" || f.right->left->label == "|"))
			inwardMoveNot(*f.right);
		if (f.left && (f.left->label == "|" || (f.right && f.right->label == "|")))
			inwardMoveAnd(f);
	}

	if (f.left != NULL)
	{
		convertToDNFTree(*f.left);
	}
	if (f.right != NULL)
	{
		convertToDNFTree(*f.right);
	}
	return;
}

void convertToCNFTree(Formula & f) {
	if (f.label == "->")
		removeImply(f);
	if (f.label == "oneof")
		removeOneof(f);
	if (f.label == "!" &&
		(f.left->label == "&" || f.left->label == "|"))
			inwardMoveNot(f);
	if (f.label == "|") {
		/* several cases to make algorithm complete */
		if (f.left->label == "->")
			removeImply(*f.left);
		if (f.right->label == "->")
			removeImply(*f.right);
		if (f.left && f.left->label == "!" &&
			(f.left->left->label == "&" || f.left->left->label == "|"))
			inwardMoveNot(*f.left);
		if (f.right && f.right->label == "!" &&
			(f.right->left->label == "&" || f.right->left->label == "|"))
			inwardMoveNot(*f.right);
		if (f.left && (f.left->label == "&" || (f.right && f.right->label == "&"))) {
			inwardMoveOr(f);}
	}

	if (f.left != NULL)
	{
		convertToDNFTree(*f.left);
	}
	if (f.right != NULL)
	{
		convertToDNFTree(*f.right);
	}
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
	//yyparse();
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
		// cout << *it << endl;
		atomicByName.insert( pair<string, int>(*it, atomicCounter++) );
		atomicByIndex.insert( pair<int, string>((atomicCounter), *it) );
	}
	atomicCounter--;

	// print init
	cout << "------Begin-----init Tree-------------------\n";
	printTree(reader.init, 0);
	cout << "-------End------init Tree-------------------\n\n";
	
	// print init DNFed
	cout << "------Begin-----init DNF Tree-------------------\n";
	convertToCNFTree(reader.init);
	printTree(reader.init, 0);
	cout << "-------End------init DNF Tree-------------------\n\n";
/*
	// print goal
	cout << "------Begin-----goal Tree-------------------\n";
	printTree(reader.goal, 0);
	cout << "-------End------goal Tree-------------------\n\n";
	
	// print goal DNFed
	cout << "------Begin-----goal CNF Tree-------------------\n";
	convertToCNFTree(reader.goal);
	printTree(reader.goal, 0);
	cout << "-------End------goal CNF Tree-------------------\n\n";
*/

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
