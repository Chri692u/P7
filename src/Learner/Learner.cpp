#include "Learner.hh"
#include "unordered_set"
#include <map>
#include <ranges>

using namespace std;

enum EntangType {Init, Goal};

vector<vector<PDDLAction>> Learner::IteratePlans(vector<SASPlan> plans, PDDLInstance pddl){
    vector<vector<pair<SASAction, int>>> acts;
    vector<vector<PDDLAction>> macros;
    for (auto plan : plans){
        acts.push_back(AnalyzePlan(pddl, plan));
        //generate macros
    }
    return macros;
}

vector<pair<SASAction, int>> Learner::AnalyzePlan(PDDLInstance pddl, SASPlan plan){
    vector<pair<SASAction, int>> entanglements;
    map<string, int> os;
    map<string, int> goalViolations;
    map<string, int> initViolations;

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

    vector<string> ops;
    for(auto o : os){
        ops.push_back(o.first);
    }

    //træk actions ud af domain
    
    //compare alle strenge i domainet til alle vores keys ops
        //hvor hver action der findes:
            // Hvis flawRatio  > initViolations[action.name] / os[action.name]
                //entanglements.push_back( pair<string, int>{action.name, Init});

            // eller hvis flawRatio  > goalViolations[action.name] / os[action.name]
                //entanglements.push_back(pair<string, int>{action.name, Goal});

    return entanglements;

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

