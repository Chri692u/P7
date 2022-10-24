#include "TimeWidthFunction.hh"

using namespace std;

int TimeWidthFunction::GetWidth() {
	if (!IsStarted) {
		StartTime = chrono::steady_clock::now();
		IsStarted = true;
	}
	auto ellapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - StartTime).count();
	if (ellapsed >= Limitms)
		return 0;
	return INT32_MAX;
}
