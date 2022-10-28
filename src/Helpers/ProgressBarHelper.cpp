#include "ProgressBarHelper.hh"

using namespace std;

void ProgressBarHelper::Update(int by) {
	if (Value > To)
		return;
	Value += by;
	int newIndex = Value * StepValue;
	for (int i = CurrentDisplayIndex; i < newIndex; i++) {
		cout << "X";
	}
	if (Value >= To)
		cout << endl;
	else
		cout.flush();
	CurrentDisplayIndex = newIndex;
}

void ProgressBarHelper::SetTo(int value) {
	if (value > Value)
		Update(value - Value);
}

void ProgressBarHelper::End() {
	Update(To - Value);
}