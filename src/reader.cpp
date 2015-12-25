#include "reader.h"

int yyparse();

Reader::Reader() {

	const char* dFile = "../epddl-doc/demo/demo_domain.epddl";  // 打开要读取的文本文件
	const char* pFile = "../epddl-doc/demo/demo_p.epddl";
	FILE* fp_d=fopen(dFile, "r");
	FILE* fp_p=fopen(pFile, "r");
	if(fp_d==NULL) {
		printf("cannot open %s\n", dFile);
		return;
	}
	if(fp_p==NULL) {
		printf("cannot open %s\n", pFile);
		return;
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

	const char* beginFile = "output_begin";
	const char* endFile = "output_reader";
	ofstream out_begin(beginFile);  // 打开要写入的文本文件
	ofstream out_end(endFile);  // 打开要写入的文本文件
	if(!out_begin.is_open()) {
		printf("cannot open %s\n", beginFile);
		return;
	}
	if(!out_end.is_open()) {
		printf("cannot open %s\n", endFile);
		return;
	}

	printInit(out_begin, out_end);
	printGoal(out_begin, out_end);
	printSenseActions(out_begin);
	printSenseActions(out_end);
	printOnticActions(out_begin);
	printOnticActions(out_end);  // conversion after first printActions()

	out_begin.close();
	out_end.close();
}

void Reader::printInit(ofstream & out_begin, ofstream & out_end) {

	// print init
	out_begin << "----------------init Tree-------------------" << endl;
	printTree(out_begin, this->init, 0);
	out_begin << "----------------  done  -------------------\n" << endl;

	// print init DNFed
	out_end << "----------------init DNF Tree-------------------" << endl;
	convertToDNFTree(this->init);
	printTree(out_end, this->init, 0);
	out_end << "----------------  done  -------------------\n" << endl;

}

void Reader::printGoal(ofstream & out_begin, ofstream & out_end) {

	// print goal
	out_begin << "----------------goal Tree-------------------" << endl;
	printTree(out_begin, this->goal, 0);
	out_begin << "----------------  done  -------------------\n" << endl;
	
	// print goal DNFed
	out_end << "----------------goal CNF Tree-------------------" << endl;
	convertToCNFTree(this->goal);
	printTree(out_end, this->goal, 0);
	out_end << "----------------  done  -------------------\n" << endl;
}

void Reader::printSenseActions(ofstream & out_file) {

	out_file << "-------------- sense actions ----------------" << endl;
  	for(PreSenseActionList::iterator it_action = senseActions.begin();
  		it_action != senseActions.end(); ++it_action) {

		if (it_action != senseActions.begin())
			out_file << "******************************************" << endl;
		out_file << ":action " << (*it_action).name << " --------------" << endl;

		out_file << "\n:parameters ----------------" << endl;
		for (MultiTypeSet::iterator it_para = (*it_action).paras.begin();
			it_para != (*it_action).paras.end(); ++it_para) {
			out_file << (*it_para).first << ":";
			for (StringSet::const_iterator it_vrb = (*it_para).second.begin();
				it_vrb != (*it_para).second.end(); ++it_vrb) {
				out_file << " " << *it_vrb;
			}
			out_file << endl;
		}

		out_file << "\n:precondition --------------" << endl;
		printTree(out_file, (*it_action).preCondition, 0);
		convertToCNFTree((*it_action).preCondition);

		out_file << "\n:observe -------------------" << endl;
		printTree(out_file, (*it_action).observe, 0);
		convertToCNFTree((*it_action).observe);

  	}
	out_file << "----------------  done  -------------------\n" << endl;

}

void Reader::printOnticActions(ofstream & out_file) {

	out_file << "-------------- ontic actions ----------------" << endl;
  	for(PreOnticActionList::iterator it_action = onticActions.begin();
  		it_action != onticActions.end(); ++it_action) {

		if (it_action != onticActions.begin())
			out_file << "******************************************" << endl;
		out_file << ":action " << (*it_action).name << " --------------" << endl;

		out_file << "\n:parameters ----------------" << endl;
		for (MultiTypeSet::iterator it_para = (*it_action).paras.begin();
			it_para != (*it_action).paras.end(); ++it_para) {
			out_file << (*it_para).first << ":";
			for (StringSet::const_iterator it_vrb = (*it_para).second.begin();
				it_vrb != (*it_para).second.end(); ++it_vrb) {
				out_file << " " << *it_vrb;
			}
			out_file << endl;
		}

		out_file << "\n:precondition --------------" << endl;
		printTree(out_file, (*it_action).preCondition, 0);
		convertToCNFTree((*it_action).preCondition);

		out_file << "\n:effect --------------------" << endl;
		size_t counter = 0;
		for (EffectList::iterator it_ef = (*it_action).effects.begin();
			it_ef != (*it_action).effects.end(); ++it_ef, ++counter) {
			out_file << "--- effect --- No." << counter << " :" << endl;
			for (StringSet::iterator str = (*it_ef).condition.begin();
				str != (*it_ef).condition.end(); ++str) {
				out_file << *str << ", ";
			}
			out_file << "\n-----" << endl;
			for (StringSet::iterator str = (*it_ef).lits.begin();
				str != (*it_ef).lits.end(); ++str) {
				out_file << *str << ", ";
			}
			out_file << "" << endl;
		}

  	}
	out_file << "----------------  done  -------------------\n" << endl;

}

void Reader::printTree(ofstream & file, Formula & f, size_t deep) {
	for (int i = 0; i < deep; i++) file << " ";
	file << f.label << endl;
	if (f.left != NULL)
	{
		if (f.left->label == "same") f.left->label = f.label;
		// cout << "left" << endl;
		printTree(file, *f.left, deep+1);
	}
	if (f.right != NULL)
	{
		if (f.right->label == "same") f.right->label = f.label;
		// cout << "right" << endl;
		printTree(file, *f.right, deep+1);
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
void Reader::removeImply(Formula & f) {
	Formula* leftF = new Formula("!", f.left, NULL);
	f.label = "|";
	f.left = leftF;
}

/*
 * The function is to replace all "oneof"s in binary tree
 * with "&", "|" and "!".
 *
 * E.g:
 *  oneof (A) (B) (C) <=> (A^¬B^¬C) V (¬A^B^¬C) V (¬A^¬B^C)
 *  -----------------------------------------------------
 * | epddl-doc | before b-tree |       after b-tree      |
 *  -----------------------------------------------------
 * | oneof (A) |     oneof     |                |        |
 * |       (B) |     /   \     |           /          \  |
 * |       (C) |    /    C     |          |           &  |
 * |           |   / \         |       /     \      /  \ |
 * |           |  A  B         |      &      &     &   C |
 * |           |               |    /   \  /   \  / \    |
 * |           |               |   &    ! &    ! !  !    |
 * |           |               |  / \  / / \  / /  /     |
 * |           |               | A  ! C !  B ! A  B      |
 * |           |               |   /   /    /            |
 * |           |               |  B   A    C             |
 *  -----------------------------------------------------
 */
void Reader::removeOneof(Formula & f) {
	// cout << "In function removeOneof, root: " f.label << "" << endl;
	f.label = "|";
	vector<Formula*> clause_vec;  // points to each prop in the leaf
	vector<string> prop_vec;  // props in the leaf
	if (f.right == NULL) {
		cout << "Warning: at least two atomic propositions with oneof!" << endl;
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
			if (i != neg_counter) {
				(*clause_it)->right = new Formula("!");
				(*clause_it)->right->left = new Formula(prop_vec.at(i));
			} else {
				(*clause_it)->right = new Formula(prop_vec.at(i));
			}
			*clause_it = (*clause_it)->left;
		}
		// process the leftest leaf
		if (i != neg_counter) {
			(*clause_it)->label = "!";
			(*clause_it)->left = new Formula(prop_vec.at(i));
		} else {
			(*clause_it)->label = prop_vec.at(i);
		}
	}
	// cout << "In function removeOneof, root: " f.label << " doen" << endl;
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
void Reader::inwardMoveNot(Formula & f) {
	// cout << "In function inwardMoveNot, root: " << f.label << "" << endl;
	Formula* r = new Formula("!", f.left->right, NULL);

	if (f.left->label == "&") f.label = "|";
	else f.label = "&";
	f.right = r;

	f.left->right = NULL;
	f.left->label = "!";
	// cout << "In function inwardMoveNot, root: " << f.label << " doen" << endl;
	return;
}

/*
 * The function is to merge all "K"s to one "K".
 *
 * E.g:
 *           K(A) ^ K(B) <=> K(A^B)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | and(K(A)) |        &      |       K      |
 * |    (K(B)) |       / \     |      /       |
 * |           |      K  K     |     &        |
 * |           |     /  /      |    / \       |
 * |           |    A  B       |   A  B       |
 *  ------------------------------------------
 */
void Reader::mergeK(Formula & f) {
	// cout << "In function mergeK, root: " << f.label << "" << endl;
	f.left = f.right->left;
	delete f.right; f.right = NULL;
	f.label = "K";
	f.left->label = "&";
	// cout << "In function mergeK, root: " << f.label << " doen" << endl;
	return;
}

/*
 * The function is to merge all "DK"s to one "DK".
 *
 * E.g:
 *           DK(A) V DK(B) <=> DK(AVB)
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | or(DK(A)) |        |      |       DK     |
 * |   (DK(B)) |      /   \    |       /      |
 * |           |     DK   DK   |      |       |
 * |           |    /    /     |     / \      |
 * |           |   A    B      |    A  B      |
 *  ------------------------------------------
 */
void Reader::mergeDK(Formula & f) {
	// cout << "In function mergeDK, root: " << f.label << "" << endl;
	f.left = f.right->left;
	delete f.right; f.right = NULL;
	f.label = "DK";
	f.left->label = "|";
	// cout << "In function mergeDK, root: " << f.label << " doen" << endl;
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
void Reader::inwardMoveAnd(Formula & f) {
	// cout << "In function inwardMoveAnd, root: " << f.label << "" << endl;
	if (f.left->label == "|") {
		Formula* rr = new Formula(*f.right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("&", f.left->right, rr);
		f.left->right = f.right;
		f.left->label = "&";
		f.right = r;
		f.label = "|";
	// cout << "left label is | : doen" << endl;
	} else {
		Formula* ll = new Formula(*f.left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("&", ll, f.right->left);
		f.right->left = f.left;
		f.right->label = "&";
		f.left = l;
		f.label = "|";
	// cout << "left label is & : doen" << endl;
	}
	// cout << "In function inwardMoveAnd, root: " << f.label << " doen" << endl;
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
void Reader::inwardMoveOr(Formula & f) {
	// cout << "In function inwardMoveAnd, root: " << f.label << "" << endl;
	if (f.left->label == "&") {
		Formula* rr = new Formula(*f.right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("|", f.left->right, rr);
		f.left->right = f.right;
		f.left->label = "|";
		f.right = r;
		f.label = "&";
	// cout << "left label is | : doen" << endl;
	} else {
		Formula* ll = new Formula(*f.left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("|", ll, f.right->left);
		f.right->left = f.left;
		f.right->label = "|";
		f.left = l;
		f.label = "&";
	// cout << "left label is & : doen" << endl;
	}
	// cout << "In function inwardMoveAnd, root: " << f.label << " doen" << endl;
	return;
}

void Reader::convertToDNFTree(Formula & f) {
	if (f.label == "->")
		removeImply(f);
	if (f.label == "oneof")
		removeOneof(f);
	if (f.label == "!" &&
		(f.left->label == "&" || f.left->label == "|"))
			inwardMoveNot(f);
	if (f.label == "|" &&
		f.left->label == "DK" && f.right && f.right->label == "DK")
			mergeDK(f);
	if (f.label == "&") {
		/* several cases to make algorithm complete */
		if (f.left->label == "&")
			convertToDNFTree(*f.left);
		if (f.left->label == "K" &&
			f.right && f.right->label == "K")
			mergeK(f);
		if (f.left->label == "->")
			removeImply(*f.left);
		if (f.right->label == "->")
			removeImply(*f.right);
		if (f.left->label == "!" &&
			(f.left->left->label == "&" || f.left->left->label == "|"))
			inwardMoveNot(*f.left);
		if (f.right && f.right->label == "!" &&
			(f.right->left->label == "&" || f.right->left->label == "|"))
			inwardMoveNot(*f.right);
		if (f.left->label == "|" || (f.right && f.right->label == "|"))
			inwardMoveAnd(f);
	}
    /*** use the rule: not (not (a) ) <=> a ***/
    if (f.left && f.left->left &&
            f.left->label == "!" && f.left->left->label == "!") {
        Formula* tmp = f.left;
        f.left = f.left->left->left;
        delete tmp->left; tmp->left = NULL;
        delete tmp; tmp = NULL;
    }
    if (f.right && f.right->left &&
            f.right->label == "!" && f.right->left->label == "!") {
        Formula* tmp = f.right;
        f.right = f.right->left->left;
        delete tmp->left; tmp->left = NULL;
        delete tmp; tmp = NULL;
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

void Reader::convertToCNFTree(Formula & f) {
	if (f.label == "->")
		removeImply(f);
	if (f.label == "oneof")
		removeOneof(f);
	if (f.label == "!" &&
		(f.left->label == "&" || f.left->label == "|"))
			inwardMoveNot(f);
	if (f.label == "&" &&
		f.left->label == "K" && f.right && f.right->label == "K")
			mergeK(f);
	if (f.label == "|") {
		/* several cases to make algorithm complete */
		if (f.left->label == "|")
			convertToCNFTree(*f.left);
		if (f.left->label == "DK" &&
			f.right && f.right->label == "DK")
			mergeDK(f);
		if (f.left->label == "->")
			removeImply(*f.left);
		if (f.right->label == "->")
			removeImply(*f.right);
		if (f.left->label == "!" &&
			(f.left->left->label == "&" || f.left->left->label == "|"))
			inwardMoveNot(*f.left);
		if (f.right && f.right->label == "!" &&
			(f.right->left->label == "&" || f.right->left->label == "|"))
			inwardMoveNot(*f.right);
		if (f.left->label == "&" || (f.right && f.right->label == "&"))
			inwardMoveOr(f);
	}
    /*** use the rule: not (not (a) ) <=> a ***/
    if (f.left && f.left->left &&
            f.left->label == "!" && f.left->left->label == "!") {
        Formula* tmp = f.left;
        f.left = f.left->left->left;
        delete tmp->left; tmp->left = NULL;
        delete tmp; tmp = NULL;
    }
    if (f.right && f.right->left &&
            f.right->label == "!" && f.right->left->label == "!") {
        Formula* tmp = f.right;
        f.right = f.right->left->left;
        delete tmp->left; tmp->left = NULL;
        delete tmp; tmp = NULL;
    }

	if (f.left != NULL)
	{
		convertToCNFTree(*f.left);
	}
	if (f.right != NULL)
	{
		convertToCNFTree(*f.right);
	}
	return;
}
