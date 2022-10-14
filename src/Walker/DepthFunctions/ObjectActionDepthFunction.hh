#ifndef ObjectActionDepthFunction_HH
#define ObjectActionDepthFunction_HH

#include "../../IntermediatePDDL/PDDLInstance.hh"
#include "BaseDepthFunction.hh"

class ObjectActionDepthFunction : public BaseDepthFunction {
public:
    ObjectActionDepthFunction(PDDLInstance instance, double modifier = 1) : BaseDepthFunction(instance, modifier) {}
    int GetDepth() override;
};

#endif
