#include "ConstantDepthFunction.hh"

using namespace std;

int ConstantDepthFunction::GetDepth() {
	return ConstantDepth * Modifier;
}
