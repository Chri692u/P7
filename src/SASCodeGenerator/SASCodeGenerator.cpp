#include "SASCodeGenerator.hh"

using namespace std;

void SASCodeGenerator::GenerateCode(SASPlan plan, string targetFile) {
	ofstream file;
	file.open(targetFile);
	file << GenerateCodeString(plan, targetFile);
	file.close();
}


string SASCodeGenerator::GenerateCodeString(SASPlan plan, string targetFile) {
	string returnValue = "";
	for (auto const& action : plan.actions)
		returnValue += GetAction(action) + "\n";
	returnValue += "; cost = " + to_string(plan.cost) + " (general cost)\n";
	return returnValue;
}

string SASCodeGenerator::GetAction(SASAction action) {
	string retStr = "";
	retStr += "(" + action.name + GetParameters(action.parameters) + ")";
	return retStr;
}

string SASCodeGenerator::GetParameters(vector<string> parameters) {
	string retStr = "";
	for (string str : parameters)
		retStr += " " + str;
	return retStr;
}
