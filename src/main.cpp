#include "initial.h"

map<int, string> atomsByIndex;
map<string, int> atomsByName;
    
vector<EpisAction> epis_actions;
vector<OnticAction> ontic_actions;

int main(int argc, char **argv) {
	if (argc < 3) return 0;
	Initial i(argv[1], argv[2]);
	return 0;
}
