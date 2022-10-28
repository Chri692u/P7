#include "ConsoleHelper.hh"

using namespace std;

void ConsoleHelper::PrintInfo(string text, int indent, bool newLine) {
	cout << "        INFO:  ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::PrintWarning(string text, int indent, bool newLine) {
	cout << "        WARN:  ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::PrintError(string text, int indent, bool newLine) {
	cout << "        ERROR: ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::PrintDebugInfo(string text, int indent, bool newLine) {
	cout << "(DEBUG) INFO:  ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::PrintDebugWarning(string text, int indent, bool newLine) {
	cout << "(DEBUG) WARN:  ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::PrintDebugError(string text, int indent, bool newLine) {
	cout << "(DEBUG) ERROR: ";
	IndentCout(indent);
	cout << text;
	if (newLine)
		cout << endl;
	else
		cout.flush();
}

void ConsoleHelper::IndentCout(int count) {
	for (int i = 0; i < count; i++)
		cout << "\t";
}