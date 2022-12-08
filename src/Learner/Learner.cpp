#include "Learner.hh"

using namespace std;

// MacroList Learner::IteratePlans(vector<pair<SASPlan, PDDLInstance> plans){
//     vector<vector<pair<PDDLAction, int>>> acts;
//     MacroList macros;
//     vector<SASPlan> sasPlans;
//     PDDLDomain* domain = plans.at(0).second->domain;
//     const Macro pddlActs = domain->actions;
//     vector<pair<PDDLAction, int>> entanglements;

//     for(auto o : os){
//         ops.push_back(o.first);
//     }

//     for (auto plan : plans){
//         AnalyzePlan(*(plan.second), plan.first);
//     }

//     for (string o: ops){
//         for(auto act : pddlActs){
//             if(act.name == o) {
//                 if (flawRatio > (float) initViolations.at(o) / (float) os.at(o)){
//                     entanglements.push_back(pair<PDDLAction, int>{act, Init});
//                 }

//                 if (flawRatio > (float) goalViolations.at(o) / (float) os.at(o)){
//                     entanglements.push_back(pair<PDDLAction, int>{act, Goal});
//                 }
//             }
//         }
//     }

//     for (auto plan : plans){
//         sasPlans.push_back(plan.first);
//     }
    
//     return descendActions(*(plans.at(0).second, entanglements, sasPlans);
// }

MacroList Learner::IteratePlans(PlanGenerator generator){
    vector<vector<pair<PDDLAction, int>>> acts;
    MacroList macros;
    vector<SASPlan> sasPlans;
    PDDLDomain domain = generator.domains.at(0);
    const Macro pddlActs = domain.actions;
    vector<pair<PDDLAction, int>> entanglements;

    for (auto act : pddlActs) {
        os.emplace(act.name, 0);
        initViolations.emplace(act.name, 0);
        goalViolations.emplace(act.name, 0);
    }

    for(auto o : os){
        ops.push_back(o.first);
    }

    for (int i = 0; i < generator.sasplans.size(); ++i){
        PDDLInstance haha = PDDLInstance(&(generator.domains.at(i)), &(generator.problems.at(i)));
        AnalyzePlan(haha, generator.sasplans.at(i));
    }

    for (string o: ops){
        for(auto act : pddlActs){
            if(act.name == o) {
                if (flawRatio <= (float) initViolations.at(o) / (float) os.at(o)){
                    entanglements.push_back(pair<PDDLAction, int>{act, Init});
                }

                if (flawRatio <= (float) goalViolations.at(o) / (float) os.at(o)){
                    entanglements.push_back(pair<PDDLAction, int>{act, Goal});
                }
            }
        }
    }
    
    for (auto plan : generator.sasplans){
        sasPlans.push_back(plan);
    }
    PDDLInstance haha = PDDLInstance(&(generator.domains.at(0)), &(generator.problems.at(0)));
    return descendActions(haha, entanglements, sasPlans);
}

void Learner::AnalyzePlan(PDDLInstance &pddl, SASPlan plan){
    vector<pair<PDDLAction, int>> entanglements;
    PDDLProblem* problem = pddl.problem;    //from the initial state from pddl
    PDDLDomain* domain = pddl.domain;       //predicates from domain
    const Macro pddlActs = domain->actions;

    double initTempRatio = 0;
    double goalTempRatio = 0;

    for (auto action : plan.actions) {
        ++os[action.name]; 
        bool notViolated = false;

        //check if goal state does not violate outer entanglements
        // BIG EXPLOSION ALLAH PROBLEM IS WRONG XD
        if (checkPredicates(pddl, pddlActs, action, Goal)){
            notViolated = true;
        }

        if(!notViolated){
            ++goalViolations[action.name];
        }

        //check if init state does not violate outer entanglements
        notViolated = false;
        if (checkPredicates(pddl, pddlActs, action, Init)){
            notViolated = true;
        }

        if(!notViolated){
            ++initViolations[action.name];
        }
        
    }
}

MacroList Learner::descendActions(PDDLInstance &pddl, vector<pair<PDDLAction, int>> entanglements, vector<SASPlan> plans){
    MacroList oldCandidates;
    MacroList candidates;
    for(auto ent : entanglements){
        for (auto candidate : GetCandidates(*pddl.domain, Macro{ent.first}, plans)){
            candidates.push_back(candidate);
        }
        while (oldCandidates.size() != candidates.size()){
            oldCandidates.clear();
            for(auto candidate : candidates){
                oldCandidates.push_back(candidate);
            }
            candidates.clear();
            for(auto candidate : oldCandidates){
                for (auto newCandidate : GetCandidates(*pddl.domain, candidate, plans)){
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

// fix this 🥺
MacroList Learner::GetCandidates(PDDLDomain &domain, Macro acts, vector<SASPlan> plans){
    MacroList candidates;
    
    unordered_map<string, int> candidateCount;
    unordered_map<string, int> totalCandidateCount;

    for (auto plan : plans) {
        unordered_map<string, vector<int>> actIndices;
        for (auto act : acts) {
            actIndices[act.name] = {};
            for (int i = 0; i < plan.actions.size(); ++i) {
                if (plan.actions.at(i).name == act.name) {
                    actIndices[act.name].push_back(i);
                }
            }
        }
        for (int j = acts.size(); j < plan.actions.size(); ++j) {
            unordered_map<string, int> macroIndices;
            unordered_map<string, int> mateo;
            for (auto act : actIndices){
                macroIndices[act.first] = 0;
                mateo[act.first] = 0;
                for (int k = 0; j > k; ++k){
                    if (plan.actions.at(k).name == act.first && act.second.size() > macroIndices[act.first]){
                        ++macroIndices[act.first];
                    }
                }
                for(auto _act : acts){
                    if(_act.name == act.first){
                        ++mateo[_act.name];
                    }
                }
            }

            bool skip = false;
            for (auto act : macroIndices) {
                if (mateo[act.first] < act.second)
                    skip = true;
            }

            if(skip) 
                continue;

            // add candidate to totalcandidatecounts
            if (totalCandidateCount.contains(plan.actions.at(j).name))
                ++totalCandidateCount[plan.actions.at(j).name];
            else
                totalCandidateCount[plan.actions.at(j).name] = 1;

            if (checkDependent(domain, plan, j, acts)) {
                if (candidateCount.contains(plan.actions.at(j).name))
                    ++candidateCount[plan.actions.at(j).name];
                else
                    candidateCount[plan.actions.at(j).name] = 1;
            }
        }
        // iteratively find dependent actions which are in current macro (acts) -> [acts]
        // for each action j check if j is dependent on actions in any of [acts]
        // if true add chain candidates
    }
    for (auto c : candidateCount) {
        float r = 1 - ((float) candidateCount[c.first]) / ((float) totalCandidateCount[c.first]);
        if (r <= macroFlawRatio) {
            Macro mark;
            for (auto emilia : acts) {
                mark.push_back(emilia);
            }
            mark.push_back(domain.getAction(c.first));
            candidates.push_back(mark);
        }
    }
    return candidates.size() == 0 ? vector<Macro>{acts} : candidates;
}

bool Learner::checkDependent(PDDLDomain &domain, SASPlan &plan, int j, Macro mac) {
    int k = mac.size()-1;
    for (int i = j-1; i >= 0 && k >= 0; --i) {
        //if (!actIndices.contains(plan.actions.at(i).name)) continue;
        bool joel = false; // if i action is in macro
        for (auto cheese : mac) { // cheese is an action in mac
            if (plan.actions.at(i).name == cheese.name && mac.at(k).name == cheese.name) {
                joel = true;
            }
        }
        if (!joel) break;
        // get intersection of positive effects between macro and preconditions of j
        bool charles = false;
        for (int m = 1; m <= k+1; ++m) {
            vector<pair<int, vector<string>>> larry = predIntersect(
                domain.getAction(plan.actions.at(j-m).name), plan.actions.at(j-m),
                domain.getAction(plan.actions.at(j).name), plan.actions.at(j));
            if (larry.size() != 0) {
                charles = true;
                break;
            }
        }
        // no need to continue if none of the macro actions share predicates
        if (!charles) break;
        // check if actions between i and j have effects which are in intersection
        // vector<pair<int, vector<string>>> olivia;
        // for (int t = i + 1; t < j; ++t) {
        //     PDDLAction actT = domain.getAction(plan.actions.at(t).name);
        //     for (auto addT : actT.GetAdds()) {
        //         vector<string> predparams;
        //         for (auto p : addT.args) {
        //             predparams.push_back(actT.parameters.at(p));
        //         }
        //         olivia.push_back(make_pair(addT.predicateIndex, predparams));
        //     }
        // }
        // // check if intersection larry isnt a subset of olivia
        // bool isSubSet = false;
        //     for (auto iPair : larry) {
        //     for (auto tPair : olivia) {
        //         if (iPair.first != tPair.first) continue;
        //         if (iPair.second != tPair.second) continue;
        //         isSubSet = true;
        //     }
        // }
        // count down k
        --k;
        // set j to i, this makes it so all actions in macro are checked
        j = i;    
    }

    return k == EXIT_SUCCESS-1;
}

// this never called
MacroList Learner::FilterCandidates(MacroList candidates){
    MacroList returnList;
    for(Macro candidate : candidates){
        returnList.push_back(RepetitiveFilter(candidate));
    }
    /*Check uninformative*/
    return returnList;
}

// this dont work
Macro Learner::RepetitiveFilter(Macro candidate){
    if (candidate.size() % 2 != 0) return candidate;
    for(int sweep = 1; sweep < candidate.size() / 2; ++sweep){
        Macro range = lookupRanges(0, sweep, candidate);
        for(int i = sweep-1; candidate.size() > i; i+=sweep){
            Macro cmpr = lookupRanges(i, i+sweep-1, candidate);
            if(range != cmpr){
                break;
            }
            if (i == candidate.size()+1){
                return range;
            }
        }
    }
    return candidate;
}

vector<pair<int, vector<string>>> Learner::predIntersect(PDDLAction iAct, SASAction iSASAct, PDDLAction jAct, SASAction jSASAct) {
    vector<pair<int, vector<string>>> preds;
    for (auto ip : iAct.GetAdds()) {
        for (auto jp : jAct.preconditions) {
            if (jp.predicateIndex != ip.predicateIndex) continue;
            bool paramsEqual = true;
            for (int i = 0; i < jp.args.size(); ++i) {
                if (iSASAct.parameters.at(ip.args.at(i)) != jSASAct.parameters.at(jp.args.at(i))) paramsEqual = false;
            }
            vector<string> predparams;
            for (auto p : jp.args) {
                predparams.push_back(jSASAct.parameters.at(p));
            }
            if (paramsEqual) preds.push_back(make_pair(jp.predicateIndex, predparams));
        }
    }
    return preds;
}

Macro Learner::lookupRanges(int start, int end, Macro candidate){
    Macro macroRange;
    for (int i = start; i < end; ++i){
        macroRange.push_back(candidate.at(i));
    }
    return macroRange;
}

bool Learner::checkPredicates(PDDLInstance &pddl, Macro acts, SASAction sAct, int flag){
    PDDLState state;

    if (flag == Init){
        state = pddl.problem->initState;
    } else {
        state = pddl.problem->goalState;
    }

    for (auto act : acts){
        if(act.name == sAct.name){
            vector<PDDLLiteral> literals;

            if (flag == Init){
                for (PDDLLiteral pre :  act.preconditions){
                    literals.push_back(pre);
                }
            } else {
                for(PDDLLiteral eff : act.GetAdds()){
                    literals.push_back(eff);
                }
            }
            
            for (auto lit : literals){
                if(lit.args.size() == 1){
                    if(state.ContainsFact(lit.predicateIndex, pddl.problem->objectMap.at(sAct.parameters.at(0)))){
                        return true;
                    }
                } else if(lit.args.size() == 2){
                    pair<unsigned int, unsigned int> binaryFact = make_pair(pddl.problem->objectMap.at(sAct.parameters.at(0)),
                                                                            pddl.problem->objectMap.at(sAct.parameters.at(1)));
                    if (state.ContainsFact(lit.predicateIndex, binaryFact)){
                        return true;
                    }
                } else {
                    vector<unsigned int> multiFact;
                    for (string arg : sAct.parameters){
                        multiFact.push_back(pddl.problem->objectMap.at(arg));
                    }
                    if(state.ContainsFact(lit.predicateIndex, new MultiFact(multiFact))){
                        return true;
                    }
                }
            }
            // break for loop because sAct is checked
            break;
        }
    }
    
    return false;
}

