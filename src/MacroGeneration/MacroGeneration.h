#ifndef _MACROGEN
#define _MACROGEN

#include "../PDDLParser/domain.hh"

class MacroGenerator {
public:
    Action GenerateMacro(std::vector<Action> actions);
};

#endif