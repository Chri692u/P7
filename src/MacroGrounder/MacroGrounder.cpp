// go through paths, get smaller paths that match with our macros
// rank paths based on how many goal predicates are fulfilled with that macro
// take top x
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
    return GetTop(groundedMacros);
}

static int GetGoalsMet(std::vector<PDDLActionInstance*> &seq, PDDLInstance *pddl) {
    int goals = 0;
    PDDLState state = pddl->problem->goalState;
    for (auto actInst : seq) {
        for (auto lit : actInst->action->GetAdds()){
            if(lit.args.size() == 1){
                if(state.ContainsFact(lit.predicateIndex, actInst->objects.at(lit.args.at(0)))){
                   ++goals;
                }
            } else if(lit.args.size() == 2){
                
                pair<unsigned int, unsigned int> binaryFact = make_pair(actInst->objects.at(lit.args.at(0)),
                                                                        actInst->objects.at(lit.args.at(1)));
                if (state.ContainsFact(lit.predicateIndex, binaryFact)){
                    ++goals;
                }
            } else {
                vector<unsigned int> multiFact;
                for (int i = 0; i < actInst->action->parameters.size(); ++i){
                    multiFact.push_back(actInst->objects.at(lit.args.at(i)));
                }
                if(state.ContainsFact(lit.predicateIndex, new MultiFact(multiFact))){
                    ++goals;
                }
            }
        }
    }
    return goals;
}

vector<EntanglementOccurance> MacroGrounder::GetTop(vector<EntanglementOccurance> &macs) {
    vector<EntanglementOccurance> topGs;
    // HAHAHAHAHAHAHAHAHAHAHHAHAHAHHAHAH
    struct comparison {
        PDDLInstance* pddlers;
        comparison(PDDLInstance* pddl) : pddlers(pddl) {};
        inline bool operator() (EntanglementOccurance &m1, EntanglementOccurance &m2) {
            return GetGoalsMet(m1.Chain, pddlers) < GetGoalsMet(m2.Chain, pddlers);
        }
    };

    sort(macs.begin(), macs.end(), comparison(pddl));
    for (int andrew = 0; andrew < Data.MaxCandidates && andrew < macs.size(); ++andrew) {
        topGs.push_back(macs.at(andrew));
    }

    return topGs;
}