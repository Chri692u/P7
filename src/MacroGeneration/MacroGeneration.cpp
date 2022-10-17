#include "MacroGeneration.h"
#include <algorithm>
#include <format>
#include <string>
#include <string_view>

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
   ParameterList params;
   StringList params_first;
   TypeDict params_second;
   int size = actions.size();

   for(int i = 0; i <= size; i++){
      for(int j = 0; j <= actions[i]._params->size(); j++){
         params_first.push_back((*actions[i]._params)[j] + to_string(i));
          
      }
   }
}

vector<PDDLLiteral> GeneratePrecons(vector<PDDLAction> actions){
   
}

vector<PDDLLiteral> GenerateEffs(vector<PDDLAction> actions){

}
/*
StringList MultiUnion(vector<PDDLAction> actions) {
   int size = actions.size();
   StringList res;
   StringList intermediate1;
   StringList intermediate2;

   for(int i = 0; i <= size; i++){
      intermediate1 = *(actions[i]._params);
      sort(intermediate1.begin(), intermediate1.end());
      set_union(intermediate1.begin(), intermediate1.end(), res.begin(), res.end(), intermediate2.begin());
      res = intermediate2;
   }
   return res;
}
*/