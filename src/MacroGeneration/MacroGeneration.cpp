#include "MacroGeneration.h"
#include <algorithm>
#include <unordered_set>

using namespace std;

PDDLAction MacroGenerator::GenerateMacro(vector<PDDLAction> actions) {
   PDDLAction* macro = new PDDLAction(GenerateName(actions), GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
   return *macro;
}

string GenerateName(vector<PDDLAction> actions){
   string name= "";
   int size = actions.size();
   for(int i = 0; i <= size; i++){
      name = name + actions[i].name + "-";
   }
}

vector<string> GenerateParams(vector<PDDLAction> actions){
   vector<string> params;
   int size = actions.size();

   for(int i = 0; i < size; i++){
      for(int j = 0; j < actions[i].parameters.size(); j++){
         params.push_back((actions[i].parameters)[j] + to_string(i));
      }
   }

   return params;
}

vector<PDDLLiteral> GeneratePrecons(vector<PDDLAction> actions){
   vector<PDDLLiteral> precons;
   int size = actions.size();
   int n = 0;
   for(int i = 0; i < size; i++){
      int size2 = actions[i].preconditions.size();
      for(int j = 0; j < size2; j++){
         PDDLLiteral lit = PDDLLiteral(actions[i].preconditions[j].predicateIndex, 
         GenerateLitParams(n, actions[i].preconditions[j].args.size()), actions[i].preconditions[j].value);
         precons.push_back(lit);
         n += actions[i].preconditions[j].args.size();
      }
   }
}

vector<PDDLLiteral> GenerateEffs(vector<PDDLAction> actions){
   vector<PDDLLiteral> effects;
   int size = actions.size();
   int n = 0;
   for(int i = 0; i < size; i++){
      int size2 = actions[i].effects.size();
      for(int j = 0; j < size2; j++){
         PDDLLiteral lit = PDDLLiteral(actions[i].effects[j].predicateIndex, 
         GenerateLitParams(n, actions[i].effects[j].args.size()), actions[i].effects[j].value);
         effects.push_back(lit);
      }
   }
}

vector<unsigned int> GenerateLitParams(int offset, int size){
   vector<unsigned int> res;
   for(int i = 0; i < size; i++){
      res.push_back(i + offset);
   }
   return res;
}

PDDLActionInstance MacroGenerator::GenerateGroundedMacro(vector<PDDLActionInstance> actions){
   PDDLAction* macro_action;
   int size = actions.size();
   vector<PDDLAction> input_actions;
   unordered_set<unsigned int> objects;

   for(int i = 0; i < size; i++){
      input_actions.push_back(*actions[i].action);
   }
   macro_action = &GenerateMacro(input_actions);


}