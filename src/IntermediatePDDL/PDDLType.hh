#ifndef PDDL_TYPE_HH
#define PDDL_TYPE_HH

#include <string>

struct PDDLType {
    std::string name;
    PDDLType(std::string name) : name(name) {};
};

#endif
