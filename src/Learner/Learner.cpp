#include "Learner.hh"
#include "unordered_set"
#include <map>
#include <ranges>

using namespace std;

enum EntangType {Init, Goal};

vector<vector<PDDLAction>> IteratePlans(vector<SASPlan> plans){
    vector<vector<PDDLAction>> acts;
    for (auto plan : plans)
        vector<vector<PDDLAction>> act = AnalyzePlan(plan);
        acts.push_back(act);
        //generate macros
    return acts
}

vector<pair<SASAction, int>> AnalyzePlan(PDDLInstance pddl, SASPlan plan){
    vector<pair<string, int>> entanglements;
    map<string, int> os;
    map<string, int> goalViolations;
    map<string, int> initViolations;

    PDDLState problem = pddl->problem// from the initial state from pddl
    PDDLDomain pddlActs = pddl->domain.actions; //predicates from domain

    double initTempRatio = 0;
    double goalTempRatio = 0;

    for (auto action : plan) {
            os.emplace(action.name, 0);
            initViolations.emplace(action.name, 0);
            goalViolations.emplace(action.name, 0);
    }

    for (auto action : plan) {
        ++os[action.name]; 
        bool notViolated = false;

        //check if goal state does not violate outer entanglements
        if (checkPredicates(goal, pddlActs, action)){
            notViolated = true;
            break;
        }

        if(!notViolated){
            ++goalViolations[action.name];
            notViolated = false;
        }

        //check if init state does not violate outer entanglements
        if (checkPredicates(init, pddlActs, action)){ //fix
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
                entanglements.push_back( pair<string, int>{action.name, Init});

            // eller hvis flawRatio  > goalViolations[action.name] / os[action.name]
                entanglements.push_back(pair<string, int>{action.name, Goal});

    return entanglements;

}

bool checkPredicatesInit(PDDLProblem, vector<PDDLAction> acts, SASAction sAct){
    PDDLAction pddlAction;
    for (auto act : acts){
        if(act.name == sAct.name){
            pddlAction = act;
            break;
        }
    }
    //check unary facts
    vector<PDDLLiteral> pre = pddlAction.preconditions;
    //check binary facts
    //mutlifacts
}