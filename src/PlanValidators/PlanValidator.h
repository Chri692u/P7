#ifndef PlanValidator_H
#define PlanValidator_H

#include <string>
#include <fstream>
#include <iostream>

#include "../Config/config.h"
#include "../Helpers/FileHelper.h"

class PlanValidator {
public:
	enum ValidatorResult { None, PlanMatch, PlanNotMatch, MissingVAL, MissingDomainFile, MissingProblemFile, MissingPlanFile};
	static enum ValidatorResult ValidatePlan(Config config, std::string domainFile, std::string problemFile, std::string planFile);
	
private:
};

#endif