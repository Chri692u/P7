#ifndef PDDLCodeGenerator_HH
#define PDDLCodeGenerator_HH

#include <string>
#include <fstream>
#include <streambuf>

#include "../PDDLParser/pddldriver.hh"
#include "PDDLDomainCodeGenerator.hh"
#include "PDDLProblemCodeGenerator.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class PDDLCodeGenerator {
public:
	void GenerateCode(PDDLInstance document, std::string domainFile, std::string problemFile);

private:
	PDDLDomainCodeGenerator domainGenerator;
	PDDLProblemCodeGenerator problemGenerator;
};

#endif