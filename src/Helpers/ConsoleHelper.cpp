#include "ConsoleHelper.hh"

using namespace std;

void ConsoleHelper::PrintInfo(string text, int indent) {
	cout << "        INFO:  ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::PrintWarning(string text, int indent) {
	cout << "        WARN:  ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::PrintError(string text, int indent) {
	cout << "        ERROR: ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::PrintDebugInfo(string text, int indent) {
	cout << "(DEBUG) INFO:  ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::PrintDebugWarning(string text, int indent) {
	cout << "(DEBUG) WARN:  ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::PrintDebugError(string text, int indent) {
	cout << "(DEBUG) ERROR: ";
	IndentCout(indent);
	cout << text << endl;
}

void ConsoleHelper::IndentCout(int count) {
	for (int i = 0; i < count; i++)
		cout << "\t";
}