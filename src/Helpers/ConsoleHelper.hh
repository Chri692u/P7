#ifndef ConsoleHelper_HH
#define ConsoleHelper_HH

#include <string>
#include <iostream>

class ConsoleHelper {
public:
	static void PrintInfo(std::string text, int indent = 0, bool newLine = true);
	static void PrintWarning(std::string text, int indent = 0, bool newLine = true);
	static void PrintError(std::string text, int indent = 0, bool newLine = true);

	static void PrintDebugInfo(std::string text, int indent = 0, bool newLine = true);
	static void PrintDebugWarning(std::string text, int indent = 0, bool newLine = true);
	static void PrintDebugError(std::string text, int indent = 0, bool newLine = true);
private:
	static void IndentCout(int count);
};

#endif