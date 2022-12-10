// go through paths, get smaller paths that match with our macros
// rank paths based on how many goal predicates are fulfilled with that macro
// take top 100
#include "MacroGrounder.hh"

using namespace std;

vector<EntanglementOccurance> MacroGrounder::WalkerWheelchair(vector<Path> &paths) {
    vector<EntanglementOccurance> groundedMacros;
    for (auto mac : macros) {
        for (auto path : paths) {
            int pathsize = path.steps.size();
            int macsize = mac.size();
            for (int i = 0; i < pathsize - macsize; ++i) {
                bool mike = true;
                // go through macro and subpath
                for (int j = 0; j < macsize && mike; ++j) {
                    if (path.steps.at(i + j).action->name != mac.at(j).name) {
                        mike = false;
                    }
                }
                if (mike) {
                    vector<PDDLActionInstance*> actionInsts;
                    for (int j = 0; j < macsize; ++j)
                        actionInsts.push_back(new PDDLActionInstance(path.steps.at(i + j).action, path.steps.at(i + j).objects));
                    groundedMacros.push_back(EntanglementOccurance(actionInsts, i));
                }
            }
        }
    }
    return groundedMacros;
}

