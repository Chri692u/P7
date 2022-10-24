#ifndef ConstantWidthFunction_HH
#define ConstantWidthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseWidthFunction.hh"

class ConstantWidthFunction : public BaseWidthFunction {
public:
    ConstantWidthFunction(int width, double modifier = 1) : ConstantWidth(width), BaseWidthFunction(modifier) {}
    int GetWidth() override;
private:
    int ConstantWidth = 0;
};

#endif
