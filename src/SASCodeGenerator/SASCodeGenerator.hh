#ifndef SASCodeGenerator_HH
#define SASCodeGenerator_HH

#include <string>
#include <fstream>
#include <streambuf>

#include "../SASParser/SASParser.hh"

class SASCodeGenerator {
public:
	void GenerateCode(SASPlan plan, std::string targetFile);
	std::string GenerateCodeString(SASPlan plan, std::string targetFile);

private:
	std::string GetAction(SASAction action);
	std::string GetParameters(std::vector<std::string> parameters);
};

#endif