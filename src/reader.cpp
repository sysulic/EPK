#include "reader.h"

int yyparse();

int counter = 0;

void Reader::exec(const char* dFile, const char* pFile) {

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
	cout << "\n-----begin parsing" << endl;
	extern FILE* yyin;  // yyin和yyout都是FILE*类型
	yyin = fp_d;  // yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的
	yyparse();
	yyin = fp_p;
	yyparse();
	cout << "\n-----end parsing" << endl;
	fclose(fp_d);
	fclose(fp_p);
/*
	// print what Reader reads (before conversion)
	string begin_file = "../output/";
	begin_file += domainName + "+" + problemName; begin_file += "_begin";
	ofstream begin_out(begin_file);  // 打开要写入的文本文件
	if(!begin_out.is_open()) {
		cout << "cannot open " << begin_file << endl;
		return;
	}
	printInit(begin_out);
	printGoal(begin_out);
	printSenseActions(begin_out);
	printOnticActions(begin_out);
	begin_out.close();
*/
	// conversion
	convertToDNFTree(&this->init);
	for (size_t i = 0; i < 30; i++)
		convertToDNFTree2(&this->init);
	convertToCNFTree(&this->goal);

	for (PreSenseActionList::iterator it_action = senseActions.begin();
  		it_action != senseActions.end(); ++it_action) {
		convertToCNFTree(&(*it_action).preCondition);
		convertToCNFTree(&(*it_action).observe);
  	}

	for (PreOnticActionList::iterator it_action = onticActions.begin();
  		it_action != onticActions.end(); ++it_action) {
		convertToCNFTree(&(*it_action).preCondition);
  	}
///*
	// print what Reader reads
	string out_file = "../output/";
	out_file += domainName + "+" + problemName; out_file += "_reader";
	ofstream out(out_file);  // 打开要写入的文本文件
	if(!out.is_open()) {
		cout << "cannot open " << out_file << endl;
		return;
	}
	printInit(out);
	printGoal(out);
	printSenseActions(out);
	printOnticActions(out);
	out.close();
//	*/
}

void Reader::printInit(ofstream & out_file) {
	// print init
	out_file << "----------------init Tree-------------------" << endl;
	printTree(out_file, &this->init, 0);
	out_file << "----------------  done  -------------------\n" << endl;
}

void Reader::printGoal(ofstream & out_file) {
	// print goal
	out_file << "----------------goal Tree-------------------" << endl;
	printTree(out_file, &this->goal, 0);
	out_file << "----------------  done  -------------------\n" << endl;
}

void Reader::printSenseActions(ofstream & out_file) {

	out_file << "-------------- sense actions ----------------" << endl;
  	for(PreSenseActionList::iterator it_action = senseActions.begin();
  		it_action != senseActions.end(); ++it_action) {

		if (it_action != senseActions.begin())
			out_file << "******************************************" << endl;
		out_file << ":action " << (*it_action).name << " --------------" << endl;

		out_file << "\n:parameters ----------------" << endl;
		for (MultiTypeList::iterator it_para = (*it_action).paras.begin();
			it_para != (*it_action).paras.end(); ++it_para) {
			out_file << (*it_para).first << ":";
			for (StringList::const_iterator it_vrb = (*it_para).second.begin();
				it_vrb != (*it_para).second.end(); ++it_vrb) {
				out_file << " " << *it_vrb;
			}
			out_file << endl;
		}

		out_file << "\n:precondition --------------" << endl;
		printTree(out_file, &(*it_action).preCondition, 0);

		out_file << "\n:observe -------------------" << endl;
		printTree(out_file, &(*it_action).observe, 0);

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
		for (MultiTypeList::iterator it_para = (*it_action).paras.begin();
			it_para != (*it_action).paras.end(); ++it_para) {
			out_file << (*it_para).first << ":";
			for (StringList::const_iterator it_vrb = (*it_para).second.begin();
				it_vrb != (*it_para).second.end(); ++it_vrb) {
				out_file << " " << *it_vrb;
			}
			out_file << endl;
		}

		out_file << "\n:precondition --------------" << endl;
		printTree(out_file, &(*it_action).preCondition, 0);

		out_file << "\n:effect --------------------" << endl;
		size_t counter = 0;
		for (EffectList::iterator it_ef = (*it_action).effects.begin();
			it_ef != (*it_action).effects.end(); ++it_ef, ++counter) {
			out_file << "--- effect --- No." << counter << " :" << endl;
			for (StringList::iterator str = (*it_ef).condition.begin();
				str != (*it_ef).condition.end(); ++str) {
				out_file << *str << ", ";
			}
			out_file << "\n-----" << endl;
			for (StringList::iterator str = (*it_ef).lits.begin();
				str != (*it_ef).lits.end(); ++str) {
				out_file << *str << ", ";
			}
			out_file << "" << endl;
		}

  	}
	out_file << "----------------  done  -------------------\n" << endl;

}

void Reader::printTree(ofstream & file, Formula * f, size_t deep) {
	for (int i = 0; i < deep; i++) file << " ";
	file << f->label << endl;
	if (f->left != NULL)
	{
		printTree(file, f->left, deep+1);
	}
	if (f->right != NULL)
	{
		printTree(file, f->right, deep+1);
	}
}

/*
 * The function is to replace all "=>"s in
 * binary tree with "|" and "~".
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
void Reader::removeImply(Formula * f) {
	Formula* leftF = new Formula("~", f->left, NULL);
	f->label = "|";
	f->left = leftF;
}

/*
 * The function is to replace all "oneof"s in binary tree
 * with "&", "|" and "~".
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
void Reader::removeOneof(Formula * f) {
	// cout << "In function removeOneof, root: " f->label << "" << endl;
	f->label = "|";
	vector<Formula*> clause_vec;  // points to each prop in the leaf
	vector<string> prop_vec;  // props in the leaf
	if (f->right == NULL) {
		cout << "Warning: at least two atomic propositions with oneof!" << endl;
		return;
	}
	clause_vec.push_back(f->right);
	prop_vec.push_back(f->right->label);
	Formula* pf = f->left;
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
				(*clause_it)->right = new Formula("~");
				(*clause_it)->right->left = new Formula(prop_vec.at(i));
			} else {
				(*clause_it)->right = new Formula(prop_vec.at(i));
			}
			*clause_it = (*clause_it)->left;
		}
		// process the leftest leaf
		if (i != neg_counter) {
			(*clause_it)->label = "~";
			(*clause_it)->left = new Formula(prop_vec.at(i));
		} else {
			(*clause_it)->label = prop_vec.at(i);
		}
	}
	// cout << "In function removeOneof, root: " f->label << " doen" << endl;
}

/*
 * The function is to move all "~"s to the
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
void Reader::inwardMoveNot(Formula * f) {
	// cout << "In function inwardMoveNot, root: " << f->label << "" << endl;
	Formula* r = new Formula("~", f->left->right, NULL);

	if (f->left->label == "&") f->label = "|";
	else f->label = "&";
	f->right = r;

	f->left->right = NULL;
	f->left->label = "~";
	// cout << "In function inwardMoveNot, root: " << f->label << " doen" << endl;
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
void Reader::mergeK(Formula * f) {
	// cout << "In function mergeK, root: " << f->label << "" << endl;
	f->left->right = f->right->left;
	delete f->right; f->right = NULL;
	f->label = "K";
	f->left->label = "&";
	// cout << "In function mergeK, root: " << f->label << " doen" << endl;
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
void Reader::mergeDK(Formula * f) {
	// cout << "In function mergeDK, root: " << f->label << "" << endl;
	f->left->right = f->right->left;
	delete f->right; f->right = NULL;
	f->label = "DK";
	f->left->label = "|";
	// cout << "In function mergeDK, root: " << f->label << " doen" << endl;
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
void Reader::inwardMoveAnd(Formula * f) {
	// cout << "In function inwardMoveAnd, root: " << f->label << "" << endl;
	if (f->left->label == "|") {
		Formula* rr = copyFormula(f->right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("&", f->left->right, rr);
		f->left->right = f->right;
		f->left->label = "&";
		f->right = r;
		f->label = "|";
	// cout << "left label is | : doen" << endl;
	} else {
		Formula* ll = copyFormula(f->left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("&", ll, f->right->left);
		f->right->left = f->left;
		f->right->label = "&";
		f->left = l;
		f->label = "|";
	// cout << "left label is & : doen" << endl;
	}
	// cout << "In function inwardMoveAnd, root: " << f->label << " doen" << endl;
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
void Reader::inwardMoveOr(Formula * f) {
	// cout << "In function inwardMoveAnd, root: " << f->label << "" << endl;
	if (f->left->label == "&") {
		Formula* rr = copyFormula(f->right);  // "rr" meas right subtree of right subtree of f
		Formula* r = new Formula("|", f->left->right, rr);
		f->left->right = f->right;
		f->left->label = "|";
		f->right = r;
		f->label = "&";
	// cout << "left label is | : doen" << endl;
	} else {
		Formula* ll = copyFormula(f->left);  // "ll" meas left subtree of left subtree of f
		Formula* l = new Formula("|", ll, f->right->left);
		f->right->left = f->left;
		f->right->label = "|";
		f->left = l;
		f->label = "&";
	// cout << "left label is & : doen" << endl;
	}
	// cout << "In function inwardMoveAnd, root: " << f->label << " doen" << endl;
	return;
}

/*
 * The function is to remove continuous "not" operator.
 *
 * E.g:
 *               ¬(¬A) <=> A
 *  ------------------------------------------
 * | epddl-doc | before b-tree | after b-tree |
 *  ------------------------------------------
 * | not(not   |       !       |       A      |
 * |       (A) |      /        |              |
 * |    )      |     !         |              |
 * |           |    /          |              |
 * |           |   A           |              |
 *  ------------------------------------------
 */
void Reader::removeDoubleNot(Formula * f) {
	if (f->left && f->left->label == "~" &&
		f->left->left && f->left->left->label == "~") {
		Formula * tmp = f->left;
		f->left = f->left->left->left;
		delete tmp->left; tmp->left = NULL;
		delete tmp; tmp = NULL;
	} else if (f->right && f->right->label == "~" &&
		f->right->left && f->right->left->label == "~") {
		Formula * tmp = f->right;
		f->right = f->right->left->left;
		delete tmp->left; tmp->left = NULL;
		delete tmp; tmp = NULL;
	}
	if (f->left != NULL)
	{
		removeDoubleNot(f->left);
	}
	if (f->right != NULL)
	{
		removeDoubleNot(f->right);
	}
}

void Reader::convertToDNFTree(Formula * f) {
	// cout << f->label << endl;
	if (f->left && f->left->label == "same")
		f->left->label = f->label;
	if (f->right && f->right->label == "same")
		f->right->label = f->label;
	
	removeDoubleNot(f);
	if (f->label == "~")
		if (f->left->label == "&" || f->left->label == "|")
			inwardMoveNot(f);
	if (f->label == "=>")
		removeImply(f);

	if (f->left && f->left->label == "oneof")
		removeOneof(f->left);
	if (f->right && f->right->label == "oneof")
		removeOneof(f->right);

	if (f->label == "|" &&
		f->left->label == "DK" && f->right && f->right->label == "DK")
			mergeDK(f);

	bool left_ok = false, right_ok = false;
	if (f->label == "&") {
		// several cases to make algorithm complete
		if (f->left->label == "&") {
			convertToDNFTree(f->left);
			left_ok = true;
		}
		if (f->right->label == "&") {
			convertToDNFTree(f->right);
			right_ok = true;
		}

		if (f->left->label == "K" &&
			f->right && f->right->label == "K") {
			mergeK(f);  // mergeK method convert label "&" to "K"!
			convertToDNFTree(f->left);
			left_ok = true;
		} else {
			if (f->left->label == "=>")
				removeImply(f->left);
			if (f->right && f->right->label == "=>")
				removeImply(f->right);
			if (f->left->label == "~" &&
				(f->left->left->label == "&" || f->left->left->label == "|"))
				inwardMoveNot(f->left);
			if (f->right && f->right->label == "~" &&
				(f->right->left->label == "&" || f->right->left->label == "|"))
				inwardMoveNot(f->right);
			if (f->left->label == "|" || (f->right && f->right->label == "|"))
				inwardMoveAnd(f);
		}
	}
    
	if (!left_ok && f->left != NULL)
	{
		convertToDNFTree(f->left);
	}
	if (!right_ok && f->right != NULL)
	{
		convertToDNFTree(f->right);
	}
	return;
}

void Reader::convertToDNFTree2(Formula * f) {
	if (f->left != NULL)
	{
		convertToDNFTree2(f->left);
	}
	if (f->right != NULL)
	{
		convertToDNFTree2(f->right);
	}

	if (f->label == "&") {
		if ((f->right && f->right->label == "|") || f->left->label == "|") {
			inwardMoveAnd(f);
		}
	}
	return;
}

void Reader::convertToCNFTree(Formula * f) {
	if (f->left && f->left->label == "same")
		f->left->label = f->label;
	if (f->right && f->right->label == "same")
		f->right->label = f->label;
	removeDoubleNot(f);
	if (f->label == "=>")
		removeImply(f);

	if (f->label == "oneof")
		removeOneof(f);
	
	if (f->label == "~" &&
		(f->left->label == "&" || f->left->label == "|"))
			inwardMoveNot(f);
	if (f->label == "&" &&
		f->left->label == "K" && f->right && f->right->label == "K")
			mergeK(f);

	bool left_ok = false;
	if (f->label == "|") {
		/* several cases to make algorithm complete */
		if (f->left->label == "|") {
			convertToCNFTree(f->left);
			left_ok = true;
		}
		if (f->left->label == "DK" &&
			f->right && f->right->label == "DK")
			mergeDK(f);  // mergeK method convert label "|" to "DK"!
		else {
			if (f->left->label == "=>")
				removeImply(f->left);
			if (f->right->label == "=>")
				removeImply(f->right);
			if (f->left->label == "~" &&
				(f->left->left->label == "&" || f->left->left->label == "|"))
				inwardMoveNot(f->left);
			if (f->right && f->right->label == "~" &&
				(f->right->left->label == "&" || f->right->left->label == "|"))
				inwardMoveNot(f->right);
			if (f->left->label == "&" || (f->right && f->right->label == "&"))
				inwardMoveOr(f);
		}
	}

	if (!left_ok && f->left != NULL)
	{
		convertToCNFTree(f->left);
	}
	if (f->right != NULL)
	{
		convertToCNFTree(f->right);
	}
	return;
}
