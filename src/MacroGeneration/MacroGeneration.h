#ifndef _MACROGEN
#define _MACROGEN

#include "../IntermediatePDDL/PDDLdomain.hh"
#include "../IntermediatePDDL/PDDLActionInstance.hh"

class MacroGenerator {
public:
    PDDLActionInstance GenerateMacro(std::vector<PDDLAction> actions);
};

#endif