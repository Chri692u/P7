#include <catch2/catch_test_macros.hpp>

#include "../../src/MacroGeneration/MacroGeneration.hh"

using namespace std;

const string TAG = "MacroGeneration "

PDDLActionInstance GenerateActionInstance(vector<unsigned int> objects, string name, vector<string> params, vector<PDDLLiteral> precons, vector<PDDLLiteral> effects){
   return PDDLActionInstance(PDDLAction(name, params, precons, effects), objects);
}

TEST_CASE(TAG + "GenerateMacroWith2Actions"){
   MacroGenerator generator = MacroGenerator();
   vector<PDDLActionInstance> actions;
   vector<unsigned int> obj_1 = {1, 2};
   vector<unsigned int> obj_2 = {3, 2, 7};
   vector<unsigned int> macro_obj = {1, 2, 3, 7};
   string name_1 = "move"
   string name_2 = "pick-up"
   string macro_name = "move-pick-up-1"
   vector<string> params_1 = {"?x", "?y"};
   vector<string> params_2 = {"?x", "?y", "?z"};
   vector<string> macro_params = {"x1", "x2", "x3", "x7"};
   vector<PDDLLiteral> precons_1 = {
      PDDLLiteral(1, vector<unsigned int> = {0}, true),
      PDDLLiteral(1, vector<unsigned int> = {1}, true),
      PDDLLiteral(0, vector<unsigned int> = {0, 1}, false),
      PDDLLiteral(4, vector<unsigned int> = {0}, true)
   };
   vector<PDDLLiteral> precons_2 = {
      PDDLLiteral(2, vector<unsigned int> = {0}, true),
      PDDLLiteral(1, vector<unsigned int> = {1}, true),
      PDDLLiteral(3, vector<unsigned int> = {2}, true),
      PDDLLiteral(5, vector<unsigned int> = {0, 1}, true),
      PDDLLiteral(4, vector<unsigned int> = {1}, true),
      PDDLLiteral(6, vector<unsigned int> = {2}, true)
   };
   vector<PDDLLiteral> macro_precons = {

   }
   vector<PDDLLiteral> effs_1 = {
      PDDLLiteral(4, vector<unsigned int> = {1}, true),
      PDDLLiteral(4, vector<unsigned int> = {0}, false)
   };
   vector<PDDLLiteral> effs_2 = {
      PDDLLiteral(7, vector<unsigned int> = {2, 0}, true),
      PDDLLiteral(5, vector<unsigned int> = {0, 1}, false),
      PDDLLiteral(6, vector<unsigned int> = {2}, false),
   };
   actions.push_back(GenerateActionInstance(obj_1, name_1, params_1, precons_1, effs_1));
   actions.push_back(GenerateActionInstance(obj_2, name_2, params_2, precons_2, effs_2));
   
}