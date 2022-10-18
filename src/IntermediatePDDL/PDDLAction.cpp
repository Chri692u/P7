#include "PDDLAction.hh"

std::vector<PDDLLiteral> PDDLAction::GetAdds() {
    std::vector<PDDLLiteral> return_vec;
    for (PDDLLiteral lit : (*this).effects) {
        if (lit.value) 
            return_vec.push_back(lit);
    }
    return return_vec;
}

std::vector<PDDLLiteral> PDDLAction::GetDeletes() {
    std::vector<PDDLLiteral> return_vec;
    for (PDDLLiteral lit : (*this).effects) {
        if (!lit.value) 
            return_vec.push_back(lit);
    }
    return return_vec;
}