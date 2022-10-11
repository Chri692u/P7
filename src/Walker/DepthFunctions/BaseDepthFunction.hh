#ifndef BaseDepthFunction_HH
#define BaseDepthFunction_HH

#include "../../PDDLTypes/PDDLInstance.hpp"

class BaseDepthFunction {
public:
    BaseDepthFunction(PDDLInstance instance, double modifier = 1) : instance(instance), Modifier(modifier) {
    }
    double Modifier;
    virtual int GetDepth() = 0;
protected:
    PDDLInstance instance;
};

#endif