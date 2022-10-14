#ifndef PDDL_ARG_HH
#define PDDL_ARG_HH

#include <string>

#include "PDDLType.hh"

struct PDDLArg {
    std::string name;
    PDDLType* typeRef;
    PDDLArg(std::string name, PDDLType* typeRef) : name(name), typeRef(typeRef) {};
};

#endif
