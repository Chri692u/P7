#ifndef BaseHeuristics_HH
#define BaseHeuristics_HH

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>

#include "../../IntermediatePDDL/PDDLDomain.hh"
#include "../../IntermediatePDDL/PDDLProblem.hh"
#include "../../IntermediatePDDL/PDDLInstance.hh"

class BaseHeuristic {
public:
	const PDDLDomain *domain;
	const PDDLProblem *problem;
	BaseHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : domain(domain), problem(problem) {}

	virtual PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const = 0; 

	virtual int Eval(const PDDLState *state) const = 0;
};

#endif
