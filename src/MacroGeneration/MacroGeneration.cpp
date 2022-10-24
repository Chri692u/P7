#include "MacroGeneration.h"
#include <algorithm>
#include <unordered_set>
#include <set>

using namespace std;

PDDLActionInstance MacroGenerator::GenerateMacro(vector<PDDLActionInstance> actions) {
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
    //PDDLAction* macro = new PDDLAction(GenerateName(actionTypes), GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
    //return *macro;
}

string MacroGenerator::GenerateName(vector<PDDLAction> actions){
    string name= "";
    for(PDDLAction i : actions){
        name = name + i.name + "-";
    }
    macro_counter++;
    return name + to_string(macro_counter);
}

vector<string> GenerateParams(vector<PDDLActionInstance> actions){
    set<unsigned int> unique_parameters = GetUniqueParams(actions);
    vector<string> params;
    for (unsigned int obj : unique_parameters) {
        params.push_back("var" + to_string(obj));
    }
    return params;
}

set<unsigned int> GetUniqueParams(vector<PDDLActionInstance> actions) {
    // vector<string> params;

    // for(string param : action1.action->parameters){
    //     params.push_back(param + to_string(index));
    // }
    // for (string param : action2.action->parameters){
        
    // }
    set<unsigned int> unique_parameters;
    for (PDDLActionInstance inst : actions) {
        for (unsigned int obj : inst.objects) {
            unique_parameters.insert(obj);
        }
    }
    return unique_parameters;
}

vector<PDDLLiteral> GeneratePrecons(vector<PDDLActionInstance> actions) {
    vector<PDDLLiteral> precons;
    for (int i = 0; i < actions.size(); ++i) {
        if (i != 0) {
            vector<PDDLLiteral> previous_adds = actions[i-1].action->GetAdds();
            
        } else {

        }
    }
    return precons;
    // vector<PDDLLiteral> precons;
    // int size = actions.size();
    // int n = 0;
    // for(int i = 0; i < size; i++){
    //     int size2 = actions[i].preconditions.size();
    //     for(int j = 0; j < size2; j++){
    //         PDDLLiteral lit = PDDLLiteral(actions[i].preconditions[j].predicateIndex, 
    //         GenerateLitParams(n, actions[i].preconditions[j].args.size()), actions[i].preconditions[j].value);
    //         precons.push_back(lit);
    //         n += actions[i].preconditions[j].args.size();
    //     }
    // }
}

vector<PDDLLiteral> GenerateEffs(vector<PDDLActionInstance> actions){
    // vector<PDDLLiteral> effects;
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

// PDDLActionInstance MacroGenerator::GenerateGroundedMacro(vector<PDDLActionInstance> actions){
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