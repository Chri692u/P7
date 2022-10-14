#ifndef PDDLContext_HH
#define PDDLContext_HH

#include "BaseContext.hh"
#include "../../../IntermediatePDDL/PDDLInstance.hh"

class PDDLContext : public BaseContext {
public:
	PDDLDomain* DomainContext;
	PDDLProblem* ProblemContext;
	PDDLContext(PDDLDomain* domain, PDDLProblem* problem) : DomainContext(domain), ProblemContext(problem) {};
};

#endif