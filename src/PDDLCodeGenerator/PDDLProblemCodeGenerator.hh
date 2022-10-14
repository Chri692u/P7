#ifndef PDDLCodeGenerator_Problem_HH
#define PDDLCodeGenerator_Problem_HH

#include <fstream>

#include "BasePDDLCodeGenerator.hh"

class PDDLProblemCodeGenerator : public BasePDDLCodeGenerator {
public:
	void GenerateProblemFile(PDDLProblem* problem, std::string problemFile);
	std::string GenerateProblemString(PDDLProblem* problem);

private:
	std::string GetObjects(std::vector<std::string> objects);
	std::string GetInits(PDDLState literals);
	std::string GetGoals(PDDLState literals);
};

#endif