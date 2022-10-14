#include "PDDLProblemCodeGenerator.hh"

using namespace std;

void PDDLProblemCodeGenerator::GenerateProblemFile(PDDLProblem* problem, string problemFile) {
	ofstream file;
	file.open(problemFile);
	file << GenerateProblemString(problem);
	file.close();
}

string PDDLProblemCodeGenerator::GenerateProblemString(PDDLProblem* problem) {
	string out = "(define (problem " + problem->name + ")\n";
	out += GetTabs(1) + "(:domain " + problem->domain->name + ")\n";
	out += "\n";
	out += GetObjects(problem->objects) + "\n";
	out += "\n";
	out += GetInits(problem->initState) + "\n";
	out += "\n";
	out += GetGoals(problem->goalState) + "\n";
	out += "\n";
	out += ")\n";
	return out;
}

string PDDLProblemCodeGenerator::GetObjects(vector<string> objects) {
	string retStr = GetTabs(1) + "(:objects\n";
	retStr += GetTabs(2) + GetStringList(objects);
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetInits(PDDLState literals) {
	string retStr = GetTabs(1) + "(:init\n";
	retStr += GetTabs(2);
	for (auto i : literals.state) {
		retStr += GetPredicate(i);
	}
	retStr += "\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}

string PDDLProblemCodeGenerator::GetGoals(PDDLState literals) {
	string retStr = GetTabs(1) + "(:goal\n";
	retStr += GetTabs(2) + "(and \n";
	retStr += GetTabs(3);
	for (auto i : literals.state) {
		retStr += GetPredicate(i);
	}
	retStr += "\n";
	retStr += GetTabs(2) + ")\n";
	retStr += GetTabs(1) + ")";
	return retStr;
}