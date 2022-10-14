#include "MacroGeneration.h"
#include <algorithm>
#include <format>
#include <string>
#include <string_view>

using namespace std;

Action MacroGenerator::GenerateMacro(vector<Action> actions) {
   Action* macro = new Action("Macrohehexd", GenerateParams(actions), GeneratePrecons(actions), GenerateEffs(actions));
   return *macro;
}

ParameterList* GenerateParams(vector<Action> actions){
   ParameterList params;
   StringList params_first;
   TypeDict params_second;
   int size = actions.size();
   vector<string> found_params;

   for(int i = 0; i <= size; i++){
      for(int j = 0; j <= actions[i]._params->size(); j++){
         if(find(found_params.begin(), found_params.end(), (*actions[i]._params)[j]) == found_params.end()){
            found_params.push_back(((*actions[i]._params)[j]));
         }
      }
   }
   for(int i = 0; i <= size; i++){
      for(int j = 0; j <= actions[i]._params->size(); j++){
         params_first.push_back((*actions[i]._params)[j] + to_string(i));
          
      }
   }
}

PreconditionList* GeneratePrecons(vector<Action> actions){
   
}

EffectList* GenerateEffs(vector<Action> actions){

}

StringList MultiUnion(vector<Action> actions) {
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