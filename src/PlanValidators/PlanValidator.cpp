#include "PlanValidator.hh"

using namespace std;

const string ValidatorLogName = "validatorLog";

enum PlanValidator::ValidatorResult PlanValidator::ValidatePlan(Config config, string domainFile, string problemFile, string planFile) {
	if (!FileHelper::DoesFileExist(filesystem::path(domainFile)))
		return PlanValidator::ValidatorResult::MissingDomainFile;
	if (!FileHelper::DoesFileExist(filesystem::path(problemFile)))
		return PlanValidator::ValidatorResult::MissingProblemFile;
	if (!FileHelper::DoesFileExist(filesystem::path(planFile)))
		return PlanValidator::ValidatorResult::MissingPlanFile;

	if (!FileHelper::DoesFileExist(filesystem::path(config.ValidatorPath.Content)))
		return PlanValidator::ValidatorResult::MissingVAL;
	string command = config.ValidatorPath.Content + " '" + domainFile + "' '" + problemFile + "' '" + planFile + "' > " + ValidatorLogName;
	system(command.c_str());

	ifstream stream(ValidatorLogName);
	string content((istreambuf_iterator<char>(stream)),
		(istreambuf_iterator<char>()));
	if (content.find("Plan valid") != string::npos)
		return PlanValidator::ValidatorResult::PlanMatch;
	if (content.find("Plan failed to execute") != string::npos)
		return PlanValidator::ValidatorResult::PlanNotMatch;
	return PlanValidator::ValidatorResult::None;
}