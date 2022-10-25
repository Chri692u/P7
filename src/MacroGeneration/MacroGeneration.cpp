#include "MacroGeneration.hh"
#include <algorithm>
#include <unordered_set>
#include <set>

using namespace std;

PDDLAction MacroGeneration::GenerateMacro(vector<PDDLActionInstance> actions) {
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
// good code
vector<PDDLLiteral> MacroGeneration::RemoveFromPDDLVector(vector<PDDLLiteral> literals, set<int> removes) {
    vector<PDDLLiteral> newLiterals;
    newLiterals.reserve(literals.size()-removes.size());
    for (int i = 0; i < literals.size(); i++)
        if (!removes.contains(i))
            newLiterals.push_back(PDDLLiteral(literals.at(i)));
    return newLiterals;
}

vector<PDDLLiteral> MacroGeneration::GeneratePrecons(vector<PDDLActionInstance> actions) {
    set<unsigned int> unique_parameters = GetUniqueParams(actions);
    vector<PDDLLiteral> precons;
    int size = actions.size();
    // for each action, add its preconditions and remove effects of previous one
    for (int i = 0; i < size; ++i) {
        // because formula is pre(o1) U (pre(o2) \ eff+(o1)), a separate precons vector is needed
        vector<PDDLLiteral> additional_precons;
        for (PDDLLiteral precon : actions[i].action->preconditions) {
            additional_precons.push_back(ConvertLiteral(precon, actions[i], unique_parameters));
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
                for (int j = 0; j < additional_precons.size(); ++j) {
                    PDDLLiteral* precon = &additional_precons.at(j);
                    // same stuff if same value and parameters and predicate
                    if (*precon == converted_add) {
                        delete_list.insert(j);
                    }
                }
            }
            additional_precons = RemoveFromPDDLVector(additional_precons, delete_list);
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
    
    return effects;
}