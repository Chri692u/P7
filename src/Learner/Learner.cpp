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

    return descendActions(pddl, entanglements, plans);
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

vector<vector<PDDLAction>> Learner::descendActions(PDDLInstance pddl, vector<pair<PDDLAction, int>> entanglements, vector<SASPlan> plans){
    vector<vector<PDDLAction>> oldCandidates;
    vector<vector<PDDLAction>> candidates;
    for(auto ent : entanglements){
        for (auto candidate : GetCandidates(pddl, vector<PDDLAction>{ent.first}, plans)){
            candidates.push_back(candidate);
        }
        while (oldCandidates.size() != candidates.size()){
            oldCandidates.clear();
            for(auto candidate : candidates){
                oldCandidates.push_back(candidate);
            }
            candidates.clear();
            for(auto candidate : oldCandidates){
                for (auto newCandidate : GetCandidates(pddl, candidate, plans)){
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
    
    unordered_map<string, int> candidateCount;
    unordered_map<string, int> totalCandidateCount;

    for (auto plan : plans) {
        unordered_map<string, vector<int>> actIndices;
        for (auto act : acts) {
            actIndices[act.name] = {};
            for (int i = 0; i < plan.actions.size(); ++i) {
                if (plan.actions[i].name == act.name) {
                    actIndices[act.name].push_back(i);
                }
            }
        }
        for (int j = acts.size(); j < plan.actions.size(); ++j) {
            for (int i = j-1; i >= 0; --i) {
                if (!actIndices.contains(plan.actions[i].name)) continue;
                // get intersection of positive effects between i and preconditions of j
                vector<pair<int, vector<string>>> larry = predIntersect(
                        pddl, 
                        pddl.domain->getAction(plan.actions[i].name), plan.actions[i],
                        pddl.domain->getAction(plan.actions[j].name), plan.actions[j]);
                // no need to continue if larry is empty
                if (larry.size() == 0) continue;
                // check if actions between i and j have effects which are in intersection
                vector<pair<int, vector<string>>> olivia;
                for (int t = i + 1; t < j; ++t) {
                    PDDLAction actT = pddl.domain->getAction(plan.actions[t].name);
                    for (auto addT : actT.GetAdds()) {
                        vector<string> predparams;
                        for (auto p : addT.args) {
                            predparams.push_back(actT.parameters[p]);
                        }
                        olivia.push_back(make_pair(addT.predicateIndex, predparams));
                    }
                }
                // check if intersection larry isnt a subset of olivia
                bool isSubSet = false;
                 for (auto iPair : larry) {
                    for (auto tPair : olivia) {
                        if (iPair.first != tPair.first) continue;
                        if (iPair.second != tPair.second) continue;
                        isSubSet = true;
                    }
                }
                
                if (!isSubSet) {
                    if (candidateCount.contains(plan.actions[j].name))
                        ++candidateCount[plan.actions[j].name];
                    else
                        candidateCount[plan.actions[j].name] = 1;
                }
            }
            if (totalCandidateCount.contains(plan.actions[j].name))
                ++totalCandidateCount[plan.actions[j].name];
            else
                totalCandidateCount[plan.actions[j].name] = 1;
        }
        // iteratively find dependent actions which are in current macro (acts) -> [acts]
        // for each action j check if j is dependent on actions in any of [acts]
        // if true add chain candidates
    }
    for (auto c : candidateCount) {
        if ((float)c.second / (float)totalCandidateCount[c.first] < macroFlawRatio) {
            vector<PDDLAction> mark;
            for (auto emilia : acts) {
                mark.push_back(emilia);
            }
            mark.push_back(pddl.domain->getAction(c.first));
            candidates.push_back(mark);
        }
    }
    return candidates;
}

vector<pair<int, vector<string>>> Learner::predIntersect(PDDLInstance pddl, PDDLAction iAct, SASAction iSASAct, PDDLAction jAct, SASAction jSASAct) {
    vector<pair<int, vector<string>>> preds;
    for (auto ip : iAct.GetAdds()) {
        for (auto jp : jAct.preconditions) {
            if (jp.predicateIndex != ip.predicateIndex) continue;
            bool paramsEqual = true;
            for (int i = 0; i < jp.args.size(); ++i) {
                if (iSASAct.parameters[i] != jSASAct.parameters[i]) paramsEqual = false;
            }
            vector<string> predparams;
            for (auto p : jp.args) {
                predparams.push_back(jSASAct.parameters[p]);
            }
            if (paramsEqual) preds.push_back(make_pair(jp.predicateIndex, predparams));
        }
    }
    return preds;
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

