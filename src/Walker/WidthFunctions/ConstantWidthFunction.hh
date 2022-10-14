#ifndef ConstantWidthFunction_HH
#define ConstantWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseWidthFunction.hh"

class ConstantWidthFunction : public BaseWidthFunction {
public:
    ConstantWidthFunction(int width, PDDLInstance instance, double modifier = 1) : ConstantWidth(width), BaseWidthFunction(instance, modifier) {}
    int GetWidth() override;
private:
    int ConstantWidth = 0;
};

#endif
