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

MacroList Learner::IteratePlans(PlanGenerator generator, Config &config){
    vector<vector<pair<PDDLAction, int>>> acts;
    MacroList macros;
    vector<SASPlan> sasPlans;
    PDDLDomain domain = generator.domains.at(0);
    const MacroT pddlActs = domain.actions;
    vector<pair<PDDLAction, int>> entanglements;
    flawRatio = config.GetItem<double>("flawRatio");
    macroFlawRatio = config.GetItem<double>("macroFlawRatio");

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
                double initFlaw = ((double) initViolations.at(o)) / ((double) os.at(o));
                double goalFlaw = ((double) goalViolations.at(o)) / ((double) os.at(o));
                if (flawRatio <= initFlaw){
                    entanglements.push_back(pair<PDDLAction, int>{act, Init});
                }

                if (flawRatio <= goalFlaw){
                    entanglements.push_back(pair<PDDLAction, int>{act, Goal});
                }
                break;
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
    const MacroT pddlActs = domain->actions;

    double initTempRatio = 0;
    double goalTempRatio = 0;

    for (auto action : plan.actions) {
        ++os[action.name]; 
        bool notViolated = false;

        //check if goal state does not violate outer entanglements
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
        for (auto candidate : GetCandidates(*pddl.domain, MacroT{ent.first}, plans)){
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
    // remove 1 size candidates
    MacroList realCandidates;
    for (auto cand : candidates) {
        if (cand.size() > 1)
            realCandidates.push_back(cand);
    }
    return realCandidates;
    /*
    for hver entanglement:
        går vi planer igennem indtil: Intermediate flawratio > macroFlaw (konstant)
            vi vil finde hvor i planen vores entanglements er
            så vil vi tage den næste action af de steder vores entanglements opstår
            Tæl hvor mange gange entanglement efterfulgt af en action kommer


    */
}

MacroList Learner::GetCandidates(PDDLDomain &domain, MacroT acts, vector<SASPlan> plans){
    MacroList candidates;
    
    unordered_map<string, int> candidateCount;
    unordered_map<string, int> totalCandidateCount;

    for (auto plan : plans) {
        for (int j = acts.size(); j < plan.actions.size(); ++j) {
            unordered_map<string, int> macroIndices;
            unordered_map<string, int> mateo;

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
        double r = 1 - ((double) candidateCount[c.first]) / ((double) totalCandidateCount[c.first]);
        if (r <= macroFlawRatio) {
            MacroT mark;
            for (auto emilia : acts) {
                mark.push_back(emilia);
            }
            mark.push_back(domain.getAction(c.first));
            candidates.push_back(mark);
        }
    }
    return candidates.size() == 0 ? MacroList{acts} : candidates;
}

bool Learner::checkDependent(PDDLDomain &domain, SASPlan &plan, int j, MacroT mac) {
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
        // count down k
        --k;
        // set j to i, this makes it so all actions in macro are checked
        j = i;    
    }

    return k == -1;
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

MacroT Learner::lookupRanges(int start, int end, MacroT candidate){
    MacroT macroRange;
    for (int i = start; i < end; ++i){
        macroRange.push_back(candidate.at(i));
    }
    return macroRange;
}

bool Learner::checkPredicates(PDDLInstance &pddl, MacroT acts, SASAction sAct, int flag){
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
                    if(state.ContainsFact(lit.predicateIndex, pddl.problem->objectMap.at(sAct.parameters.at(lit.args[0])))){
                        return true;
                    }
                } else if(lit.args.size() == 2){
                    pair<unsigned int, unsigned int> binaryFact = make_pair(pddl.problem->objectMap.at(sAct.parameters.at(lit.args.at(0))),
                                                                            pddl.problem->objectMap.at(sAct.parameters.at(lit.args.at(1))));
                    if (state.ContainsFact(lit.predicateIndex, binaryFact)){
                        return true;
                    }
                } else {
                    vector<unsigned int> multiFact;
                    for (int i = 0; i < sAct.parameters.size(); ++i){
                        multiFact.push_back(pddl.problem->objectMap.at(sAct.parameters.at(lit.args.at(i))));
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

