#ifndef _MACROGEN
#define _MACROGEN

#include "../IntermediatePDDL/PDDLdomain.hh"
#include "../IntermediatePDDL/PDDLActionInstance.hh"

class MacroGenerator {
private:
    int macro_counter = 0;
    std::string GenerateName(vector<PDDLAction> actions);
public:
    PDDLActionInstance GenerateMacro(std::vector<PDDLActionInstance> actions);
};

#endif