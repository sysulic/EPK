#include "plan.h"

Plan::Plan(const char *domain, const char *p, int type){
    printf("================================================================\n");
    printf("domain_file(%s)\np_file(%s)\n", domain, p);
    if(type == 0)
        cout << "search_type(Heur first)\n" << endl;
    if(type == 1)
        cout << "search_type(Deap first)\n" << endl;
    if(type == 2)
        cout << "search_type(Bread first)\n" << endl;
    all_nodes.clear();
    all_edges.clear();
    explored_num = -1;
    searchtype = type == 0 ? kHeuristic : (type == 1 ? kDepthFirst : kWidthFirst);
    plan_tree_depth = 0;
    plan_tree_node_num = 0;
    clock_t t_start = clock();
    printf("Preprocessing...\n");
    in.exec(domain, p);

    /*
    //print actions
    int i = 0;
    cout << "======= epis actions : ============" << endl;
    for (std::vector<EpisAction>::const_iterator v = epis_actions.begin();
        v != epis_actions.end(); ++v) {
        cout << i++ << ": " << (*v).name << endl;
    }
    cout << "======= ontic actions : ===========" << endl;
    i = 0;
    for (std::vector<OnticAction>::const_iterator v = ontic_actions.begin();
        v != ontic_actions.end(); ++v) {
        cout << i++ << ": " << (*v).name << endl;
    }
    cout << "===================================" << endl;
    */

    clock_t t_end = clock();
    preprocess_time = difftime(t_end, t_start) / 1000000.0;
}

// Algorithm 6
void Plan::exec_plan() {
    printf("Planning...\n");
    if(in.init.entails(in.goal)) {
        printf("init entails goal!\n");
        return;
    }

    clock_t t_start = clock();
    Node init_node;
    init_node.flag = TOBEEXPLORED;
    init_node.isolated = false;
    init_node.kb = in.init;
    add_node(init_node);
    hert_nodes = 0; //for deep search
    while(true) {
        int node_pos = get_tobeexplored_node();//heuristic
        if(node_pos == -1)
            return ;
         
        explore(node_pos); 
        if(all_nodes[0].flag == FINAL_GOAL) {
            clock_t t_end = clock();
            search_time = difftime(t_end, t_start) / 1000000.0;
            BuildPlan();//之后再调用BuildPlan，原算法中的Tree
            return ;
        }
        if(all_nodes[0].flag == DEAD)
            return ;
    }
}

// Algorithm 7
void Plan::explore(int node_pos){

    /*
    // print edges
    cout << "======== edges ================" << endl;
    for (size_t i = 0; i < all_edges.size(); ++i) {
        cout << "edge " << i << ": " << all_edges[i].front_state
            << " -- " << (all_edges[i].is_observe_action ? "epis " : "ontic ") << all_edges[i].action_number
            << " --> " << all_edges[i].next_state << endl;
    }


    int i = 0;
    for (std::vector<OnticAction>::const_iterator v = ontic_actions.begin();
        v != ontic_actions.end(); ++v) {


        if (all_nodes.size() > 138 && i == 41) {
            if (all_nodes[138].kb.entails(v->pre_con)) {
                cout << "--------hahaha----------" << endl;
                
    ofstream out("abc", ios::app);
    all_nodes[138].kb.show(out);
    out.close();

                cout << "--------hahaha----------" << endl;
            }
        }
        i++;;
    }

    if (all_nodes.size() > 1000) {
        cout << "frank: " << all_nodes[138].flag << " " << all_nodes[138].isolated << endl;
    }


    cout << "===============================" << endl;
    */
    
    //cout << "explore..." << endl;
    bool execed = false;//deep search find new node
    // 进行感知演进
    for(size_t i = 0; i < epis_actions.size(); i++){        
        if(all_nodes[node_pos].kb.entails(epis_actions[i].pre_con)){

            vector<EpisDNF> res = all_nodes[node_pos].kb.epistemic_prog(epis_actions[i]);

            if(check_zero_dead(res[0]) || check_zero_dead(res[1]))
                continue;
            int res_pos = checknode(res[0]);// find if old node; if it is old node, then return node number            
            if(res_pos == node_pos) continue;
            if(res_pos == -1){
                Node newNode(TOBEEXPLORED,false,res[0],all_nodes.size());
                add_node(newNode);
                res_pos = all_nodes.size()-1;
            }
            else{
                if(all_nodes[res_pos].flag == DEAD)
                    continue;
                if(all_nodes[res_pos].flag == EXPLORED && all_nodes[res_pos].isolated){
                    reconnection_propagation(res_pos);
                }
            }
            Transition tbs;
            tbs.front_state = node_pos;
            tbs.next_state = res_pos;
            tbs.is_observe_action = true;
            tbs.action_number = i;
            tbs.is_true = true;
            expand(tbs);
           
            int res_pos1 = checknode(res[1]);
            if(res_pos1 == node_pos) continue;
            if(res_pos1 == -1){
                Node newNode(TOBEEXPLORED,false,res[1],all_nodes.size());
                add_node(newNode);
                res_pos1 = all_nodes.size()-1;
            }
            else{
                if(all_nodes[res_pos1].flag == DEAD)
                    continue;
                if(all_nodes[res_pos1].flag == EXPLORED && all_nodes[res_pos1].isolated){
                    reconnection_propagation(res_pos);
                }
            }
            Transition tbs1;
            tbs1.front_state = node_pos;
            tbs1.next_state = res_pos1;
            tbs1.is_observe_action = true;
            tbs1.action_number = i;
            tbs1.is_true = false;
            expand(tbs1);
            
            if(all_nodes[res_pos1].flag == FINAL_GOAL && all_nodes[res_pos].flag == FINAL_GOAL){
                PropagateGoalNode(node_pos, true, i);
                return;
            }
            if(searchtype == 1 && !execed){
                hert_nodes = res_pos;
                execed = true;
            }
        }
    }
    // 进行物理演进
    for(size_t i = 0; i < ontic_actions.size(); i++){
        if(all_nodes[node_pos].kb.entails(ontic_actions[i].pre_con)){

            EpisDNF res = all_nodes[node_pos].kb.ontic_prog(ontic_actions[i]);

            if(check_zero_dead(res)) continue;
            int res_pos = checknode(res);
            if(res_pos == node_pos) continue;
            if(res_pos == -1){
                Node newNode(TOBEEXPLORED,false,res,all_nodes.size());
                add_node(newNode);
                res_pos = all_nodes.size()-1;
            }
            else{
                if(all_nodes[res_pos].flag == DEAD)
                    continue;
                if(all_nodes[res_pos].flag == EXPLORED && all_nodes[res_pos].isolated)
                    reconnection_propagation(res_pos);
            }
            Transition tbs;
            tbs.front_state = node_pos;
            tbs.next_state = res_pos;
            tbs.is_observe_action = false;
            tbs.action_number = i;
            expand(tbs);
            
            if(all_nodes[res_pos].flag == FINAL_GOAL){
                PropagateGoalNode(node_pos, false, i);
                return;
            }
            
            if(searchtype == 1 && !execed){
                hert_nodes = res_pos;
                execed = true;
            }    
        }
    }

    if(is_exist_edge_from_node(node_pos)){
        all_nodes[node_pos].flag = EXPLORED;
    }
    else{
        all_nodes[node_pos].flag = DEAD;
        PropagateDeadNode(node_pos);
    }
}

// Algorithm 8
void Plan::expand(Transition ts){
    //cout << "expand..." << endl;
    if(all_nodes[ts.next_state].flag != EXPLORED){
        if(all_nodes[ts.next_state].kb.entails(in.goal))
            all_nodes[ts.next_state].flag = FINAL_GOAL;
        else
            all_nodes[ts.next_state].flag = TOBEEXPLORED;
    }
    all_edges.push_back(ts);
}

// Algorithm 12
void Plan::PropagateDeadNode(int node_num){
    //cout << "dead propagation..." << endl;
    for(size_t i = 0; i < all_edges.size(); ){
        if(all_edges[i].next_state == node_num){
            int front = all_edges[i].front_state;
            if(!all_edges[i].is_observe_action)
                all_edges.erase(all_edges.begin()+i);
            else{
                for(size_t j = 0; j < all_edges.size(); j++){
                    if((all_edges[i].front_state == all_edges[j].front_state) && (all_edges[i].action_number == all_edges[j].action_number)){
                        if(j!=i){
                            isolation_propagation(all_edges[j].next_state);
                            if(i > j){
                                all_edges.erase(all_edges.begin()+i);
                                all_edges.erase(all_edges.begin()+j);
                                i--;
                            }
                            else{
                                all_edges.erase(all_edges.begin()+j);
                                all_edges.erase(all_edges.begin()+i);
                                i--;
                            }
                        }
                    }
                }
            }
            bool is_front_dead = true;
            for(size_t k = 0; k < all_edges.size(); k++){
                if(front == all_edges[k].front_state)
                    is_front_dead = false;
            }
            //may change num of all_edges
            if(is_front_dead)
                PropagateDeadNode(front);
        }
        else
            i++;
    }
}

// Algorithm 11
void Plan::isolation_propagation(int node_num){
    //cout << "isolation_propagation..." << endl;
    if(!all_nodes[node_num].isolated){
        all_nodes[node_num].isolated = true;
        for(size_t i = 0; i < all_edges.size(); i++)
            if(all_edges[i].front_state == node_num)
                isolation_propagation(all_edges[i].next_state);
    }    
}

// Algorithm 9
void Plan::reconnection_propagation(int node_num){
    //cout << "reconnection_propagation..." << endl;
    if(all_nodes[node_num].isolated){
        all_nodes[node_num].isolated = false;
        for(size_t i = 0; i < all_edges.size(); i++)
            if(all_edges[i].front_state == node_num){
                reconnection_propagation(all_edges[i].next_state);
            }
    }    
}

int Plan::get_tobeexplored_node(){
    if (searchtype == kWidthFirst || searchtype == kDepthFirst) {
        if(searchtype == kDepthFirst) {
            if(all_nodes[hert_nodes].flag == TOBEEXPLORED && !all_nodes[hert_nodes].isolated)
                return hert_nodes;
            else {
                /*
                // find available father node
                int father_node = hert_nodes;
                for (size_t i = 0; i < all_edges.size() && father_node != 0; ++i) {
                    if (all_edges[i].next_state == father_node) {
                        for (size_t j = 0; j < all_edges.size(); ++j) {
                            if (all_edges[j].front_state == all_edges[i].front_state
                                && all_nodes[all_edges[j].next_state].flag == TOBEEXPLORED
                                && !all_nodes[all_edges[j].next_state].isolated) {
                                return all_edges[j].next_state;
                            }
                        }
                    }
                    father_node = all_edges[i].next_state;
                    i = 0;
                }
                //*/
            }
        }
        for(size_t i = explored_num + 1; i < all_nodes.size(); i++)
            if(all_nodes[i].flag == TOBEEXPLORED && !all_nodes[i].isolated)
                return i;
        return -1;    
    }
    else{
        if (heuristic_que_.empty())
            return -1;
        int ret = -1;
        vector<PlanHelper> phv;
        while (! heuristic_que_.empty()) {
            PlanHelper ph = heuristic_que_.top();
            heuristic_que_.pop();
            if (all_nodes[ph.node_id_].flag == TOBEEXPLORED && ! all_nodes[ph.node_id_].isolated) {
                ret = ph.node_id_;
                break;
            }
            else {
                phv.push_back(ph);
            }
        }
        for (size_t i = 0; i < phv.size(); ++ i) {
            heuristic_que_.push(phv[i]);
        }
        return ret;
    }
}
    

// Algorithm 10
void Plan::PropagateGoalNode(int start_node_num, bool is_observe_action, int act_num){
    //cout << "goal_propagation..." << endl;
    all_nodes[start_node_num].flag = FINAL_GOAL;
    for(size_t i = 0; i < all_edges.size();){
        if(all_edges[i].front_state == start_node_num){
            if(all_edges[i].action_number != act_num || is_observe_action != all_edges[i].is_observe_action){
                isolation_propagation(all_edges[i].next_state);
                all_edges.erase(all_edges.begin()+i);
            }
            else
                i++;
        }
        else
            i++;            
    }
    for(size_t i = 0; i < all_edges.size(); i++)
        if(all_edges[i].next_state == start_node_num){
            if(!all_edges[i].is_observe_action)
                PropagateGoalNode(all_edges[i].front_state, false, all_edges[i].action_number);
            else
                for(size_t j = 0; j < all_edges.size(); j++)
                if(j!=i){
                    if(all_edges[j].is_observe_action && all_edges[j].front_state == all_edges[i].front_state && all_edges[j].action_number == all_edges[i].action_number){
                        if(all_nodes[all_edges[j].next_state].flag == FINAL_GOAL)
                            PropagateGoalNode(all_edges[i].front_state, true, all_edges[i].action_number);
                        break;
                    }
                }
            
        } 
}

bool Plan::is_exist_edge_from_node(int n){
    for(size_t i = 0; i < all_edges.size(); i++){
        if(all_edges[i].front_state == n)
            return true;
    }
    return false;    
}

int Plan::checknode(EpisDNF ed){
    for(size_t i = 0; i < all_nodes.size(); i++)
        if( all_nodes[i].kb.equals(ed))
            return i;
    return -1;   
}

bool Plan::check_zero_dead(EpisDNF ed){
    return ed.epis_terms.size() == 0;
   
}

void Plan::BuildPlan(){
    if(all_nodes[0].flag != FINAL_GOAL){
        cout<<"no plan"<<endl;
        return;
    }
    vector<Transition> goal_edges;
    for(size_t i = 0; i < all_edges.size(); i++)
        if(all_nodes[all_edges[i].front_state].flag == FINAL_GOAL && all_nodes[all_edges[i].next_state].flag == FINAL_GOAL)
            goal_edges.push_back(all_edges[i]);
    set<int> nodes;//标记节点是否在树里面
    printf("\nPlan tree:\n");
    plan_tree_node_num = 0;
    plan_tree_depth = show_build_result(0, goal_edges, 0, nodes, -1);
}

void Plan::show_statistic() const {
    printf("\nStatistic:\n");
    printf(" preprocess time: %.4fs\n", preprocess_time);
    printf(" search time: %.4fs\n", search_time);
    printf(" solution size: %d\n", plan_tree_node_num);
    printf(" solution depth: %d\n", plan_tree_depth);
    printf(" search size: %lu\n", all_nodes.size());
}
    

int Plan::show_build_result(int node_num, const vector<Transition> &goal_edges, int tab_num, set<int> nodes, int oldnode){
    int depth = 0;
    ++ plan_tree_node_num;
    tab_num++;
    vector<Transition> next_trans;
    if(oldnode != -1)
        nodes.insert(oldnode);
    int num = goal_edges.size();
    for(int i = 0; i < num; i++)
        if(goal_edges[i].front_state == node_num)
            next_trans.push_back(goal_edges[i]);
    for(size_t i = 0; i < next_trans.size(); i++)
        if(nodes.find(next_trans[i].next_state) == nodes.end()){
            for (int k = 0; k < tab_num; k++) 
                cout << " ";
            if (next_trans[i].is_observe_action) {
                if (next_trans[i].is_true){                   
                    cout << epis_actions[next_trans[i].action_number].name;
                    cout<<" +:";
                    /*
                    if(epis_actions[next_trans[i].action_number].para_match.size()!=0){
                        cout<<" (";
                        for(size_t j = 0; j < epis_actions[next_trans[i].action_number].para_match.size()-1; j++)
                            cout<<epis_actions[next_trans[i].action_number].para_match[j]<<",";
                        if(epis_actions[next_trans[i].action_number].para_match.size() > 0)
                            cout<<epis_actions[next_trans[i].action_number].para_match[epis_actions[next_trans[i].action_number].para_match.size()-1];
                        cout<<")";
                    }
                    */
                    cout << endl;
                    depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
                }
                else{
                    cout << epis_actions[next_trans[i].action_number].name;
                    cout << " -:";
                    /*
                    if(epis_actions[next_trans[i].action_number].para_match.size()!=0){
                        cout<<" (";
                        for(size_t j = 0; j < epis_actions[next_trans[i].action_number].para_match.size()-1; j++)
                            cout<<epis_actions[next_trans[i].action_number].para_match[j]<<",";
                        if(epis_actions[next_trans[i].action_number].para_match.size() > 0)
                            cout<<epis_actions[next_trans[i].action_number].para_match[epis_actions[next_trans[i].action_number].para_match.size()-1];                        
                        cout<<")";
                    }
                    */
                    cout << endl;
                    depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
                    
                }
            }
            else{
                cout << ontic_actions[next_trans[i].action_number].name;
                /*
                if(ontic_actions[next_trans[i].action_number].para_match.size() != 0){
                    cout<<" (";
                    for(size_t j = 0; j < ontic_actions[next_trans[i].action_number].para_match.size()-1; j++)
                        cout<<ontic_actions[next_trans[i].action_number].para_match[j]<<",";
                    if(ontic_actions[next_trans[i].action_number].para_match.size() > 0)
                        cout<<ontic_actions[next_trans[i].action_number].para_match[ontic_actions[next_trans[i].action_number].para_match.size()-1];
                    cout<<")";  
                }
                */
                cout << endl;
                depth = max(depth, show_build_result(next_trans[i].next_state, goal_edges, tab_num, nodes, node_num) + 1);
            }   
        }
    return depth;
}


void Plan::add_node(const Node& node) {
    all_nodes.push_back(node);
    int node_id = all_nodes.size() - 1;
    int heuristic_value = calculate_node_heuristic_value(all_nodes.back());
    heuristic_que_.push(PlanHelper(node_id, heuristic_value));
}

int Plan::calculate_node_heuristic_value(const Node& node) const {
    assert(! in.goal.epis_clauses.empty());
    int count = 0;
    for (list<EpisClause>::const_iterator it_goal = in.goal.epis_clauses.begin();
            it_goal != in.goal.epis_clauses.end(); ++ it_goal) {
        for (list<EpisTerm>::const_iterator it_node = node.kb.epis_terms.begin();
                it_node != node.kb.epis_terms.end(); ++ it_node) {
            if (it_node->entails(*it_goal))
                ++ count;
        }
    }
    return count / in.goal.epis_clauses.size();
}
