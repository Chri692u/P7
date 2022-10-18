#ifndef _MACROGEN
#define _MACROGEN

#include "../IntermediatePDDL/PDDLdomain.hh"
#include "../IntermediatePDDL/PDDLActionInstance.hh"

class MacroGenerator {
public:
    PDDLAction GenerateMacro(std::vector<PDDLAction> actions);
    PDDLAction GenerateGroundedMacro(std::vector<PDDLActionInstance> actions);
};

#endif