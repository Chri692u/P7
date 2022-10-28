#include "PlanValidator.hh"

using namespace std;

const string ValidatorLogName = "validatorLog";

enum PlanValidator::ValidatorResult PlanValidator::ValidatePlan(Config config, std::filesystem::path domainFile, std::filesystem::path problemFile, std::filesystem::path planFile) {
	if (!FileHelper::DoesFileExist(domainFile))
		return PlanValidator::ValidatorResult::MissingDomainFile;
	if (!FileHelper::DoesFileExist(problemFile))
		return PlanValidator::ValidatorResult::MissingProblemFile;
	if (!FileHelper::DoesFileExist(planFile))
		return PlanValidator::ValidatorResult::MissingPlanFile;

	if (!FileHelper::DoesFileExist(config.GetPath("validatorpath")))
		return PlanValidator::ValidatorResult::MissingVAL;
	string path = config.GetPath("validatorpath").c_str();
	string command = path + " '" + string(domainFile) + "' '" + string(problemFile) + "' '" + string(planFile) + "' > " + ValidatorLogName;
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