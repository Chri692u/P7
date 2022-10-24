#include "MacroGeneration.hh"
#include <algorithm>
#include <unordered_set>
#include <set>

using namespace std;

PDDLAction MacroGeneration::GenerateMacro(vector<PDDLActionInstance> actions) {
    // int size = actions->size();
    // int last = size - 1;
    // PDDLActionInstance* macro;
    // map<unsigned int, pair<int, int>> param_map;

    // for(int i = 0; i < size; i++){
    //     param_map = GenerateParamMap((*actions)[i], (*actions)[last]);
    //     macro = new PDDLActionInstance(new PDDLAction(
    //     GenerateName((*actions)[i], (*actions)[last]), 
    //     GenerateParams((*actions)[i], (*actions)[last], param_map, i),
    //     GeneratePrecons((*actions)[i], (*actions)[last]),
    //     GenerateEffs((*actions)[i], (*actions)[last])
    //     ), GenerateObjects((*actions)[i], (*actions)[last]));
    //     (*actions).insert((*actions).end() - 1, (*macro));
    // }
    // return *macro;

    vector<PDDLAction> actionTypes;
    for (PDDLActionInstance actionInstance : actions) {
        actionTypes.push_back(*actionInstance.action);
    }
    PDDLAction macro = PDDLAction(GenerateName(actionTypes), GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
    return macro;
}

string MacroGeneration::GenerateName(vector<PDDLAction> actions) {
    string name = "";
    for(PDDLAction i : actions) {
        name = name + i.name + "-";
    }
    macro_counter++;
    return name + to_string(macro_counter);
}

set<unsigned int> MacroGeneration::GetUniqueParams(vector<PDDLActionInstance> actions) {
    set<unsigned int> unique_parameters;
    for (PDDLActionInstance inst : actions) {
        for (unsigned int obj : inst.objects) {
            unique_parameters.insert(obj);
        }
    }
    return unique_parameters;
}

vector<string> MacroGeneration::GenerateParams(vector<PDDLActionInstance> actions) {
    set<unsigned int> unique_parameters = GetUniqueParams(actions);
    vector<string> params;
    for (unsigned int obj : unique_parameters) {
        params.push_back("x" + to_string(obj));
    }
    return params;
}

// cursed index of set element i
int MacroGeneration::GetIndex(set<unsigned int> p, unsigned int i) {
    set<unsigned int>::iterator it = p.find(i);
    int j = 0;
    for (set<unsigned int>::iterator it2 = p.begin(); it2 != p.end() && it2 != it; ++it2) {
        ++j;
    }
    return j;
}

// religiously convert literal to extremist macro literal
// converts arguments of literal to use arguments of macro
PDDLLiteral MacroGeneration::ConvertLiteral(PDDLLiteral lit, PDDLActionInstance action, set<unsigned int> params) {
    vector<unsigned int> newargs;
    for (unsigned int arg : lit.args) {
        // push the index of argument object to newargs
        newargs.push_back(GetIndex(params, action.objects[arg]));
    }
    return PDDLLiteral(lit.predicateIndex, newargs, lit.value);
}

vector<PDDLLiteral> MacroGeneration::GeneratePrecons(vector<PDDLActionInstance> actions) {
    set<unsigned int> unique_parameters = GetUniqueParams(actions);
    vector<PDDLLiteral> precons;
    // for each action, add its preconditions and remove effects of previous one
    for (int i = 0; i < actions.size(); ++i) {
        // because formula is pre(o1) U (pre(o2) \ eff+(o1)), a separate precons vector is needed
        vector<PDDLLiteral> additional_precons;
        for (PDDLLiteral precon : actions[i].action->preconditions) {
            precons.push_back(ConvertLiteral(precon, actions[i], unique_parameters));
        }
        // remove positive effects of previous action from precons
        if (i != 0) {
            vector<PDDLLiteral> previous_adds = actions[i-1].action->GetAdds();
            set<int> delete_list;
            // convert add literals to new ones
            // and add them to remove list if they exist in additional_precons
            for (PDDLLiteral add : previous_adds) {
                PDDLLiteral converted_add = ConvertLiteral(add, actions[i-1], unique_parameters);
                // check if add exists in additional_precons, add it to delete_list
                for (PDDLLiteral precon : additional_precons) {

                }
            }
            for (int i : delete_list) {
                //additional_precons.erase(additional_precons.begin()+i);
            }
        }
        // add additional precons literals to precons vector
        for (PDDLLiteral precon : additional_precons) {
            precons.push_back(precon);
        }
    }
    return precons;
}

vector<PDDLLiteral> MacroGeneration::GenerateEffs(vector<PDDLActionInstance> actions) {
    vector<PDDLLiteral> effects;
    // int size = actions.size();
    // int n = 0;
    // for(int i = 0; i < size; i++){
    //     int size2 = actions[i].effects.size();
    //     for(int j = 0; j < size2; j++){
    //         PDDLLiteral lit = PDDLLiteral(actions[i].effects[j].predicateIndex, 
    //         GenerateLitParams(n, actions[i].effects[j].args.size()), actions[i].effects[j].value);
    //         effects.push_back(lit);
    //     }
    // }
    return effects;
}

// map<unsigned int, pair<int, int>> GenerateParamMap(PDDLActionInstance action1, PDDLActionInstance action2){
//     map<unsigned int, pair<int, int>> res;
//     int size = action1.action->parameters.size();

//     for(int i = 0; i < size; i++){
//         res.insert(pair<unsigned int, pair<int, int>>(action1.objects[i], pair<int, int>(i, -1)));
//     }

//     size = action2.action->parameters.size();

//     for(int i = 0; i < size; i++){
//         if(res.find(action2.objects[i]) != res.end()){
//             res[action2.objects[i]].second = i;
//         }
//         else {
//             res.insert(pair<unsigned int, pair<int, int>>(action2.objects[i], pair<int, int>(-1, i)));
//         }
//     }
// }

// vector<unsigned int> GenerateLitParams(int offset, int size){
//     vector<unsigned int> res;
//     for(int i = 0; i < size; i++){
//         res.push_back(i + offset);
//     }
//     return res;
// }

// PDDLActionInstance MacroGeneration::GenerateGroundedMacro(vector<PDDLActionInstance> actions){
//     PDDLAction macro_action;
//     macro_action = PDDLAction(
//         GenerateGroundedName(actions),
//         GenerateGroundedParams(actions),
//         GenerateGroundedPreconditions(actions),
//         GenerateGroundedEffects(actions)
//     );

            // if (i != 0) {
            //     bool cont = false;
            //     // life could be a dream, check if an add of previous action is same as precondition
            //     vector<PDDLLiteral> adds = actions[i-1].GetAdds();
            //     for (PDDLLiteral lit : adds) {
            //         if (lit.predicateIndex == actions[i].preconditions[j].predicateIndex) {
            //             if (lit.value == actions[i].preconditions[j].value) {
            //                 bool args_same = true;
            //                 for (int k = 0; k < actions[i].preconditions[j].args.size() && args_same; ++k) {
            //                     args_same = actions[i].preconditions[j].args[k] == lit.args[k];
            //                 }
            //                 cont = !args_same;
            //             }
            //         }
            //         if (cont)
            //             break;
            //     }
            //     if (cont)
            //         continue;                
            // }

//}