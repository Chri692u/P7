#include "BasePDDLCodeGenerator.hh"

using namespace std;

string BasePDDLCodeGenerator::GetPredicate(PDDLPredicate predicate) {
	return " (" + predicate.name + GetPDDLArgs(predicate.args) + ")";
}

string BasePDDLCodeGenerator::GetPDDLArgs(vector<PDDLArg> args) {
	string retStr = "";
	for (auto i : args)
		retStr += " " + GetPDDLArg(i);
	return retStr;
}

string BasePDDLCodeGenerator::GetPDDLArg(PDDLArg arg) {
	return arg.name;
}

string BasePDDLCodeGenerator::GetStringList(vector<string> list) {
	string retStr = "";
	for (auto i : list) {
		retStr += " " + i;
	}
	return retStr;
}

string BasePDDLCodeGenerator::GetLiteral(PDDLLiteral predicate) {
	if (!predicate.state) {
		return "(not" + GetPredicate(predicate.predicate) + ")";
	}
	else
	{
		return GetPredicate(predicate.predicate);
	}
}

string BasePDDLCodeGenerator::GetTabs(int count) {
	string retStr = "";
	for (int i = 0; i < count; i++) {
		retStr += "\t";
	}
	return retStr;
}