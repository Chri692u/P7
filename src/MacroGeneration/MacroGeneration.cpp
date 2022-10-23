#include "MacroGeneration.h"
#include <algorithm>
#include <unordered_set>

using namespace std;

PDDLActionInstance MacroGenerator::GenerateMacro(vector<PDDLActionInstance>* actions) {
   // vector<PDDLAction> actionTypes;
   // for (PDDLActionInstance actionInstance : actions) {
   //    actionTypes.push_back(*actionInstance.action);
   // }
   // PDDLAction* macro = new PDDLAction(GenerateName(actionTypes), GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
   // return *macro;
   int size = actions->size();
   int last = size - 1;
   PDDLActionInstance* macro;
   map<unsigned int, pair<int, int>> param_map;

   for(int i = 0; i < size; i++){
      param_map = GenerateParamMap((*actions)[i], (*actions)[last]);
      macro = new PDDLActionInstance(new PDDLAction(
      GenerateName((*actions)[i], (*actions)[last]), 
      GenerateParams((*actions)[i], (*actions)[last], param_map, i),
      GeneratePrecons((*actions)[i], (*actions)[last]),
      GenerateEffs((*actions)[i], (*actions)[last])
      ), GenerateObjects((*actions)[i], (*actions)[last]));
      (*actions).insert((*actions).end() - 1, (*macro));
   }
   return *macro;
}

map<unsigned int, pair<int, int>> GenerateParamMap(PDDLActionInstance action1, PDDLActionInstance action2){
   map<unsigned int, pair<int, int>> res;
   int size = action1.action->parameters.size();

   for(int i = 0; i < size; i++){
      res.insert(pair<unsigned int, pair<int, int>>(action1.objects[i], pair<int, int>(i, -1)));
   }

   size = action2.action->parameters.size();

   for(int i = 0; i < size; i++){
      if(res.find(action2.objects[i]) != res.end()){
         res[action2.objects[i]].second = i;
      }
      else {
         res.insert(pair<unsigned int, pair<int, int>>(action2.objects[i], pair<int, int>(-1, i)));
      }
   }
}

// need to make naming more unique
string GenerateName(PDDLActionInstance action1, PDDLActionInstance action2){
   string name= action1.action->name + "-" + action2.action->name + "-";
   return name;
}

vector<string> GenerateParams(PDDLActionInstance action1, PDDLActionInstance action2, map<unsigned int, pair<int, int>> param_map, int index){
   vector<string> params;

   for(string param : action1.action->parameters){
      params.push_back(param + to_string(index));
   }
   for (string param : action2.action->parameters){
      
   }
}

vector<unsigned int> GenerateObjects(PDDLActionInstance action1, PDDLActionInstance action2){

}

vector<PDDLLiteral> GeneratePrecons(PDDLActionInstance action1, PDDLActionInstance action2){
   // vector<PDDLLiteral> precons;
   // int size = actions.size();
   // int n = 0;
   // for(int i = 0; i < size; i++){
   //    int size2 = actions[i].preconditions.size();
   //    for(int j = 0; j < size2; j++){
   //       PDDLLiteral lit = PDDLLiteral(actions[i].preconditions[j].predicateIndex, 
   //       GenerateLitParams(n, actions[i].preconditions[j].args.size()), actions[i].preconditions[j].value);
   //       precons.push_back(lit);
   //       n += actions[i].preconditions[j].args.size();
   //    }
   // }
}

vector<PDDLLiteral> GenerateEffs(PDDLActionInstance action1, PDDLActionInstance action2){
   // vector<PDDLLiteral> effects;
   // int size = actions.size();
   // int n = 0;
   // for(int i = 0; i < size; i++){
   //    int size2 = actions[i].effects.size();
   //    for(int j = 0; j < size2; j++){
   //       PDDLLiteral lit = PDDLLiteral(actions[i].effects[j].predicateIndex, 
   //       GenerateLitParams(n, actions[i].effects[j].args.size()), actions[i].effects[j].value);
   //       effects.push_back(lit);
   //    }
   // }
}

// vector<unsigned int> GenerateLitParams(int offset, int size){
//    vector<unsigned int> res;
//    for(int i = 0; i < size; i++){
//       res.push_back(i + offset);
//    }
//    return res;
// }

// PDDLActionInstance MacroGenerator::GenerateGroundedMacro(vector<PDDLActionInstance> actions){
//    PDDLAction macro_action;
//    macro_action = PDDLAction(
//       GenerateGroundedName(actions),
//       GenerateGroundedParams(actions),
//       GenerateGroundedPreconditions(actions),
//       GenerateGroundedEffects(actions)
//    );

         // if (i != 0) {
         //    bool cont = false;
         //    // life could be a dream, check if an add of previous action is same as precondition
         //    vector<PDDLLiteral> adds = actions[i-1].GetAdds();
         //    for (PDDLLiteral lit : adds) {
         //       if (lit.predicateIndex == actions[i].preconditions[j].predicateIndex) {
         //          if (lit.value == actions[i].preconditions[j].value) {
         //             bool args_same = true;
         //             for (int k = 0; k < actions[i].preconditions[j].args.size() && args_same; ++k) {
         //                args_same = actions[i].preconditions[j].args[k] == lit.args[k];
         //             }
         //             cont = !args_same;
         //          }
         //       }
         //       if (cont)
         //          break;
         //    }
         //    if (cont)
         //       continue;            
         // }

//}