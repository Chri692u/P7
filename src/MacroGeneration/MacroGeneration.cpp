#include "MacroGeneration.h"
#include <algorithm>

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

   for(int i = 0; i <= size; i++){
      for(int j = 0; j <= actions[i].parameters.size(); j++){
         params.push_back((actions[i].parameters)[j] + to_string(i));
      }
   }

   return params;
}

vector<PDDLLiteral> GeneratePrecons(vector<PDDLAction> actions){
   vector<PDDLLiteral> precons;
   int size = actions.size();

   for(int i = 0; i <= size; i++){
      int size2 = actions[i].preconditions.size();
      for(int j = 0; j <= size2; j++){
         precons.push_back(actions[i].preconditions[j]);
      }
   }
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