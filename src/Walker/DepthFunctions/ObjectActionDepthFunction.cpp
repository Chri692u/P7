#include "ObjectActionDepthFunction.hh"

using namespace std;

int ObjectActionDepthFunction::GetDepth() {
	int retValue = 0;
	retValue = instance.problem->objects.size() * instance.domain->actions.size();
	return retValue * Modifier;
}
