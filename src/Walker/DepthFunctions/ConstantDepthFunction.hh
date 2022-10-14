#ifndef ConstantDepthFunction_HH
#define ConstantDepthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseDepthFunction.hh"

class ConstantDepthFunction : public BaseDepthFunction {
public:
    ConstantDepthFunction(int depth, PDDLInstance instance, double modifier = 1) : ConstantDepth(depth), BaseDepthFunction(instance, modifier) {}
    int GetDepth() override;
private:
    int ConstantDepth = 0;
};

#endif
