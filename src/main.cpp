#include "plan.h"

map<int, string> atomsByIndex;
map<string, int> atomsByName;
    
vector<EpisAction> epis_actions;
vector<OnticAction> ontic_actions;

int main(int argc, char **argv) {
    //*
    if (argc < 3) return 0;

    if (argc != 3 && argc != 4) {
        printf("Usage:\n%s domain_file p_file (search_type)\n", argv[0]);
        return 0;
    }
    int search_type = 0;
    if (argc == 4) {
        search_type = atoi(argv[3]);
    }
    Plan p(argv[1], argv[2], search_type);
	
    p.exec_plan();
    p.show_statistic();
    /*/
    
    //*
    Initial in;
    in.exec(argv[1], argv[2]);
    if (in.init.entails(in.goal)) {
    	cout << "1" << endl;
    }
    for (std::vector<EpisAction>::const_iterator v = epis_actions.begin();
        v != epis_actions.end(); ++v) {
        if (in.init.entails((*v).pre_con)) {
            cout << (*v).name << endl;
        }
    }
    for (std::vector<OnticAction>::const_iterator v = ontic_actions.begin();
        v != ontic_actions.end(); ++v) {
        if (in.init.entails((*v).pre_con)) {
            cout << (*v).name << endl;
        }
    }
    */
    return 0;
}
