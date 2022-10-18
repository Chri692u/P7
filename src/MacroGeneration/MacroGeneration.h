#ifndef _MACROGEN
#define _MACROGEN

#include "../IntermediatePDDL/PDDLdomain.hh"
#include "../IntermediatePDDL/PDDLActionInstance.hh"

class MacroGenerator {
public:
    PDDLAction GenerateMacro(std::vector<PDDLAction> actions);
    PDDLActionInstance GenerateGroundedMacro(std::vector<PDDLActionInstance> actions);
};

#endif