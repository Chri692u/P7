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
    auto names = GenerateName(actionTypes);
    auto params = GenerateParams(actions);
    auto precons = GeneratePrecons(actions);
    auto effects = GenerateEffs(actions);
    PDDLAction macro = PDDLAction(names, params, precons, effects);
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
        params.push_back("?x" + to_string(obj));
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
        newargs.push_back(GetIndex(params, action.objects.at(arg)));
    }
    return PDDLLiteral(lit.predicateIndex, newargs, lit.value);
}
// good code
vector<PDDLLiteral> MacroGeneration::RemoveFromPDDLVector(vector<PDDLLiteral> literals, set<int> removes) {
    vector<PDDLLiteral> newLiterals;
    //newLiterals.reserve(literals.size()-removes.size());
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
        for (PDDLLiteral precon : actions.at(i).action->preconditions) {
            additional_precons.push_back(ConvertLiteral(precon, actions.at(i), unique_parameters));
        }
        // remove positive effects of previous action from precons
        if (i != 0) {
            vector<PDDLLiteral> previous_adds = actions.at(i-1).action->GetAdds();
            set<int> delete_list;
            // convert add literals to new ones
            // and add them to remove list if they exist in additional_precons
            for (PDDLLiteral add : previous_adds) {
                PDDLLiteral converted_add = ConvertLiteral(add, actions.at(i-1), unique_parameters);
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
    set<unsigned int> unique_parameters;
    int size = actions.size();
    vector<PDDLLiteral> new_adds;
    vector<PDDLLiteral> new_deletes;
    // size-1 because there is no point doing anything on the last one
    for (int i = 0; i < size-1; ++i) {
        vector<PDDLLiteral> preliminary_adds;
        vector<PDDLLiteral> preliminary_deletes;
        
        vector<PDDLLiteral> o1_adds;
        vector<PDDLLiteral> o1_deletes;

        if (i == 0) {
            o1_adds = actions.at(i).action->GetAdds();
            o1_deletes = actions.at(i).action->GetDeletes();
        } else {
            o1_adds = preliminary_adds;
            o1_deletes = preliminary_deletes;
        }

        vector<PDDLLiteral> o2_adds = actions.at(i+1).action->GetAdds();
        vector<PDDLLiteral> o2_deletes = actions.at(i+1).action->GetDeletes();

        // adds(o1, o2) is (adds(o1) \ deletes(o2)) U adds(o2)
        // this is adds(o1) \ deletes(o2) part allegedly
        for (int j = 0; j < o1_adds.size(); ++j) {
            bool is_in_deletes = false;
            PDDLLiteral converted_o1_add = (i == 0) ? ConvertLiteral(o1_adds.at(j), actions.at(i), unique_parameters) : o1_adds.at(j);
            for (PDDLLiteral o2_delete : o2_deletes) {
                PDDLLiteral converted_o2_delete = ConvertLiteral(o2_delete, actions.at(i+1), unique_parameters);
                if (converted_o1_add == converted_o2_delete) {
                    is_in_deletes = true;
                    break;
                }
            }
            if (!is_in_deletes) {
                preliminary_adds.push_back(converted_o1_add);
            }
        }
        // U adds(o2) part
        for (PDDLLiteral o2_add : o2_adds) {
            bool is_in_adds = false;
            PDDLLiteral converted_o2_add = ConvertLiteral(o2_add, actions.at(i+1), unique_parameters);
            // check if add already exists in preliminary_adds, add it if it doesnt
            for (PDDLLiteral o1_add : preliminary_adds) {
                if (converted_o2_add == o1_add) {
                    is_in_adds = true;
                    break;
                } 
            }
            if (!is_in_adds) {
                preliminary_adds.push_back(converted_o2_add);
            }
        }
        // deletes(o1, o2) (deletes(o1) \ adds(o2)) U deletes(o2)
        // deletes(o1) \ adds(o2)
        for (int j = 0; j < o1_deletes.size(); ++j) {
            bool is_in_adds = false;
            PDDLLiteral converted_o1_delete = (i == 0) ? ConvertLiteral(o1_deletes.at(j), actions.at(i), unique_parameters) : o1_deletes.at(j);
            for (PDDLLiteral o2_add : o2_adds) {
                PDDLLiteral converted_o2_add = ConvertLiteral(o2_add, actions.at(i+1), unique_parameters);
                if (converted_o1_delete == converted_o2_add) {
                    is_in_adds = true;
                    break;
                }
            }
            if (!is_in_adds) {
                preliminary_deletes.push_back(converted_o1_delete);
            }
        }
        // U deletes(o2) part
        for (PDDLLiteral o2_delete : o2_deletes) {
            bool is_in_deletes = false;
            PDDLLiteral converted_o2_delete = ConvertLiteral(o2_delete, actions.at(i+1), unique_parameters);
            // check if add already exists in preliminary_adds, add it if it doesnt
            for (PDDLLiteral o1_delete : preliminary_adds) {
                if (converted_o2_delete == o1_delete) {
                    is_in_deletes = true;
                    break;
                } 
            }
            if (!is_in_deletes) {
                preliminary_deletes.push_back(converted_o2_delete);
            }
        }
        new_adds = preliminary_adds;
        new_deletes = preliminary_deletes;
    }

    for (PDDLLiteral lit : new_adds) {
        effects.push_back(lit);
    }
    for (PDDLLiteral lit : new_deletes) {
        effects.push_back(lit);
    }

    return effects;
}