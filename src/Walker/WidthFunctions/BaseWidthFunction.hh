#ifndef BaseWidthFunction_HH
#define BaseWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseWidthFunction {
public:
    BaseWidthFunction(PDDLInstance instance, double modifier = 1) : instance(instance), Modifier(modifier) {
    }
    double Modifier;
    virtual int GetWidth() = 0;
protected:
    PDDLInstance instance;
};

#endif