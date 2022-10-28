#ifndef ProgressBarHelper_HH
#define ProgressBarHelper_HH

#include <iostream>
#include <string>

#include "ConsoleHelper.hh"

class ProgressBarHelper {
public:
	int DisplayWidth = 50;
	int To = 1;

	ProgressBarHelper(int to, std::string desc, int indent = 0) : To(to), Indent(indent) {
		StepValue = ((double)DisplayWidth / ((double)To - 1));
		ConsoleHelper::PrintDebugInfo(desc, indent);
		ConsoleHelper::PrintDebugInfo("|", indent, false);
		for (int i = 0; i < DisplayWidth; i++)
			std::cout << " ";
		std::cout << "|" << std::endl;
		ConsoleHelper::PrintDebugInfo(" ", indent, false);
	};

	void SetTo(int value);
	void Update(int by = 1);
	void End();

private:
	int Indent = 0;
	int Value = 0;

	double StepValue = 0;
	int CurrentDisplayIndex = 0;
};

#endif