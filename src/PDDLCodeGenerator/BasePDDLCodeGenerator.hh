#ifndef Base_PDDLCodeGenerator_HH
#define Base_PDDLCodeGenerator_HH

#include <fstream>
#include <string>

#include "../IntermediatePDDL/PDDLInstance.hh"

class BasePDDLCodeGenerator {
public:
	std::string GetPredicate(PDDLPredicate predicate);
	std::string GetStringList(std::vector<std::string> list);
	std::string GetTabs(int count);
	std::string GetPDDLArgs(std::vector<PDDLArg> args);
	std::string GetPDDLArg(PDDLArg arg);
	std::string GetLiteral(PDDLLiteral predicate);
};

#endif