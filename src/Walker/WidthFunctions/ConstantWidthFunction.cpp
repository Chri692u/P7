#include "ConstantWidthFunction.hh"

using namespace std;

int ConstantWidthFunction::GetWidth() {
	return ConstantWidth * Modifier;
}
