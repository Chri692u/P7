#ifndef ConsoleHelper_HH
#define ConsoleHelper_HH

#include <string>
#include <iostream>

class ConsoleHelper {
public:
	static void PrintInfo(std::string text, int indent = 0);
	static void PrintWarning(std::string text, int indent = 0);
	static void PrintError(std::string text, int indent = 0);

	static void PrintDebugInfo(std::string text, int indent = 0);
	static void PrintDebugWarning(std::string text, int indent = 0);
	static void PrintDebugError(std::string text, int indent = 0);
private:
	static void IndentCout(int count);
};

#endif