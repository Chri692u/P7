#include "MacroGeneration.h"
#include <algorithm>
#include <unordered_set>

using namespace std;

PDDLActionInstance MacroGenerator::GenerateMacro(vector<PDDLActionInstance> actions) {
   vector<PDDLAction> actionTypes;
   for (PDDLActionInstance actionInstance : actions) {
      actionTypes.push_back(*actionInstance.action);
   }
   PDDLAction* macro = new PDDLAction(GenerateName(actionTypes), GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
   return *macro;
}

// need to make naming more unique
string GenerateName(vector<PDDLAction> actions){
   string name= "";
   for(PDDLAction i : actions){
      name = name + i.name + "-";
   }
}

vector<string> GenerateParams(vector<PDDLActionInstance> actions){
   // vector<string> params;
   // int size = actions.size();

   // for(int i = 0; i < size; i++){
   //    for(string j : actions[i].parameters){
   //       params.push_back(j + to_string(i));
   //    }
   // }

   // return params;
}

vector<PDDLLiteral> GeneratePrecons(vector<PDDLActionInstance> actions){
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

vector<PDDLLiteral> GenerateEffs(vector<PDDLActionInstance> actions){
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