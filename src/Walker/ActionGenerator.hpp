#ifndef ACTION_GENERATOR
#define ACTION_GENERATOR

#include <vector>
#include <string>
#include <map>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class ActionGenerator {
public:
    ActionGenerator(PDDLDomain* domain) : domain(domain) {};
    std::vector<PDDLActionInstance> GenerateActions(PDDLState *state);
private:
    PDDLDomain* domain;
    // Given some action generate all legal parameter variations
    std::vector<PDDLActionInstance> GenerateLegal(PDDLAction action, PDDLState *state);
    // Get relevant preconditions for given parameter
    //// Note: at some point make this static
    std::vector<PDDLLiteral> GetPreconditions(PDDLAction action, PDDLArg *param);
    // Find those objects that match the given unary preconditions
    std::vector<std::string> GetCandidateObjects(PDDLAction* action, PDDLState *state, std::vector<PDDLLiteral> preconditions);
    void RemoveInvalidObjects();

    void SplitLiterals(std::vector<PDDLLiteral> literals, std::vector<PDDLLiteral> *unaryLiterals, std::vector<PDDLLiteral> *multiLiterals);
    // returns false on no increment possible
    bool Increment(std::vector<int> *indexes, std::vector<std::string> objects[]);
};

#endif
