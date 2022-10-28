#ifndef ConstantWidthFunction_HH
#define ConstantWidthFunction_HH

#include "BaseWidthFunction.hh"

class ConstantWidthFunction : public BaseWidthFunction {
public:
    ConstantWidthFunction(unsigned int maxWidth, unsigned int startWidth = 0, unsigned int increment = 1) : currentWidth(startWidth), maxWidth(maxWidth), increment(increment), BaseWidthFunction(maxWidth) {};
    bool Iterate(unsigned int *current) override {
        currentWidth += increment;
        (*current) = currentWidth;
        return currentWidth <= maxWidth;
    }
private:
    unsigned int currentWidth;
    const unsigned int maxWidth;
    const unsigned int increment;
};

#endif
