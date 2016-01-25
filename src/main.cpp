#include "plan.h"

map<int, string> atomsByIndex;
map<string, int> atomsByName;
    
vector<EpisAction> epis_actions;
vector<OnticAction> ontic_actions;

int main(int argc, char **argv) {
    if (argc < 3) return 0;

    Plan p(argv[1], argv[2], 0);
	
    p.exec_plan();
    p.show_statistic();
    /*
    Initial in;
    in.exec(argv[1], argv[2]);
    if (in.init.entails(in.goal)) {
    	cout << "1" << endl;
    }
     */
   return 0;
}
