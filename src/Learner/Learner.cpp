#include "Learner.hh"
#include "unordered_set"
#include <map>
#include <ranges>

using namespace std;

vector<vector<PDDLAction>> Learner::IteratePlans(vector<SASPlan> plans, PDDLInstance pddl){
    vector<vector<pair<PDDLAction, int>>> acts;
    vector<vector<PDDLAction>> macros;
    PDDLDomain domain = *(pddl.domain);
    vector<PDDLAction> pddlActs = domain.actions;
    vector<pair<PDDLAction, int>> entanglements;

    for(auto o : os){
        ops.push_back(o.first);
    }

    for (auto plan : plans){
        AnalyzePlan(pddl, plan);
    }

    for (string o: ops){
        for(auto act : pddlActs){
            if(act.name == o) {
                if (flawRatio > (float) initViolations[o] / (float) os[o]){
                    entanglements.push_back(pair<PDDLAction, int>{act, Init});
                }

                if (flawRatio > (float) goalViolations[o] / (float) os[o]){
                    entanglements.push_back(pair<PDDLAction, int>{act, Goal});
                }
            }
        }
    }

    return descendActions(entanglements, plans);
}

void Learner::AnalyzePlan(PDDLInstance pddl, SASPlan plan){
    vector<pair<PDDLAction, int>> entanglements;
    PDDLProblem problem = *(pddl.problem);    //from the initial state from pddl
    PDDLDomain domain = *(pddl.domain);       //predicates from domain
    vector<PDDLAction> pddlActs = domain.actions;

    double initTempRatio = 0;
    double goalTempRatio = 0;

    for (auto action : plan.actions) {
            os.emplace(action.name, 0);
            initViolations.emplace(action.name, 0);
            goalViolations.emplace(action.name, 0);
    }

    for (auto action : plan.actions) {
        ++os[action.name]; 
        bool notViolated = false;

        //check if goal state does not violate outer entanglements
        if (checkPredicates(problem, pddlActs, action, Goal)){
            notViolated = true;
            break;
        }

        if(!notViolated){
            ++goalViolations[action.name];
            notViolated = false;
        }

        //check if init state does not violate outer entanglements
        if (checkPredicates(problem, pddlActs, action, Init)){
            notViolated = true;
            break;
        }

        if(!notViolated){
            ++initViolations[action.name];
            notViolated = false;
        }
        
    }
}

vector<vector<PDDLAction>> Learner::descendActions(vector<pair<PDDLAction, int>> entanglements, vector<SASPlan> plans){
    vector<vector<PDDLAction>> oldCandidates;
    vector<vector<PDDLAction>> candidates;
    for(auto ent : entanglements){
        for (auto candidate : GetCandidates(vector<PDDLAction>{ent.first}, plans)){
            candidates.push_back(candidate);
        }
        while (oldCandidates.size() != candidates.size()){
            oldCandidates.clear();
            for(auto candidate : candidates){
                oldCandidates.push_back(candidate);
            }
            candidates.clear();
            for(auto candidate : oldCandidates){
                for (auto newCandidate : GetCandidates(candidate, plans)){
                    candidates.push_back(newCandidate);
                }
            }
        }
    }
    return candidates;
    /*
    for hver entanglement:
        går vi planer igennem indtil: Intermediate flawratio > macroFlaw (konstant)
            vi vil finde hvor i planen vores entanglements er
            så vil vi tage den næste action af de steder vores entanglements opstår
            Tæl hvor mange gange entanglement efterfulgt af en action kommer


    */
}

vector<vector<PDDLAction>> Learner::GetCandidates(PDDLInstance pddl, vector<PDDLAction> acts, vector<SASPlan> plans){
    /*
    let candidates = vector<vector<PDDLAction>>
    let realCandidates = vector<vector<PDDLAction>>
    let actSequence = "";

    for(auto plan in plans){
        find indices for act i planen
        find actions der kommer efter acts sekvensen (entanglement)
        hvis actions er dependent(i < j, (e+(ai) ∩ p(aj )) 6 = ∅ and (e+(ai) ∩ p(aj )) (not ⊆) ⋃j−1 t=i+1 e+(at).) så: 
            candidates.push_back(actions)
    }
    for(auto candidate : candidates){
        hvis den er over macroFlaw, så er det en candidate og vi tilføjer den til listen
        realCandidates.push_back(candidate);
    }
    candidate.size() == 0 ? return vector<vector<PDDLActions>>{acts} : return realCandidates
    */
    vector<vector<PDDLAction>> candidates;
    vector<vector<PDDLAction>> realCandidates;

    for (auto plan : plans) {
        map<string, vector<int>> actIndices;
        for (auto act : acts) {
            actIndices[act.name] = {};
            for (int i = 0; i < plan.actions.size(); ++i) {
                if (plan.actions[i].name == act.name) {
                    actIndices[act.name].push_back(i);
                }
            }
        }
        for (int i = acts.size(); i < plan.actions.size(); ++i) {
            int j = i-1; // final countdown :3
            int k = acts.size()-1; // what we lookin for
            vector<int> foundActIndices;
            for (auto _ : acts) {
                while (j >= 0) {
                    --j;
                    if (plan.actions[j].name == acts[k].name) {
                        --k;
                        foundActIndices.push_back(j);
                        break;
                    }
                }
            }
            if (k == 0) {
                PDDLAction macroTail = acts[foundActIndices[0]];

                // check if action is dependent on first one in foundActIndices
            }
        }
    }

    vector<vector<PDDLAction>> lol;
    return lol;
}

bool Learner::checkPredicates(PDDLProblem prob, vector<PDDLAction> acts, SASAction sAct, int flag){
    PDDLAction* actPtr;
    PDDLState state;

    if (flag == Init){
        state = prob.initState;
    } else {
        state = prob.goalState;
    }

    for (auto act : acts){
        if(act.name == sAct.name){
            actPtr = &act;
            break;
        }
    }
    PDDLAction pddlAction = *actPtr;
    vector<PDDLLiteral> literals;

    if (flag == Init){
        for (PDDLLiteral pre :  pddlAction.preconditions){
            literals.push_back(pre);
        }
    } else {
        for(PDDLLiteral eff : pddlAction.GetAdds()){
            literals.push_back(eff);
        }
    }
    
    for (auto lit : literals){
        if(lit.args.size() == 1){
            if(state.ContainsFact(lit.predicateIndex, prob.objectMap.at(sAct.parameters[0]))){
                return true;
            }
        } else if(lit.args.size() == 2){
            pair<unsigned int, unsigned int> binaryFact = make_pair(prob.objectMap.at(sAct.parameters[0]),
                                                                    prob.objectMap.at(sAct.parameters[1]));
            if (state.ContainsFact(lit.predicateIndex, binaryFact)){
                return true;
            }
        } else {
            vector<unsigned int> multiFact;
            for (string arg : sAct.parameters){
                multiFact.push_back(prob.objectMap.at(arg));
            }
            if(state.ContainsFact(lit.predicateIndex, new MultiFact(multiFact))){
                return true;
            }
        }
    }
    return false;
}

