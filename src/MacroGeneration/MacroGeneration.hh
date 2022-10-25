#ifndef _MACROGEN
#define _MACROGEN

#include "../IntermediatePDDL/PDDLDomain.hh"
#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include <set>

class MacroGeneration {
private:
    int macro_counter = 0;

    std::string GenerateName(std::vector<PDDLAction> actions);
    std::vector<std::string> GenerateParams(std::vector<PDDLActionInstance> actions);
    std::vector<PDDLLiteral> GeneratePrecons(std::vector<PDDLActionInstance> actions);
    std::vector<PDDLLiteral> GenerateEffs(std::vector<PDDLActionInstance> actions);

    std::set<unsigned int> GetUniqueParams(std::vector<PDDLActionInstance> actions);
    int GetIndex(std::set<unsigned int> p, unsigned int i);
    PDDLLiteral ConvertLiteral(PDDLLiteral lit, PDDLActionInstance action, std::set<unsigned int> params);
    std::vector<PDDLLiteral> RemoveFromPDDLVector(std::vector<PDDLLiteral> literals, std::set<int> removes);
public:
    PDDLAction GenerateMacro(std::vector<PDDLActionInstance> actions);
};

#endif