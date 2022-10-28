#include "CommonInterface.hh"

using namespace std;

enum CommonInterface::RunResult CommonInterface::Run(RunReport* report) {
	int64_t t;
	BaseReformulator* reformulator;

	// Find a suitable reformulator
	ConsoleHelper::PrintInfo("Finding reformulator algorithm...");
	report->Begin("Finding Reformulator");
	if (config.GetString("reformulator") == "sameoutput") {
		reformulator = new SameOutputReformulator(&config);
	} else 	if (config.GetString("reformulator") == "walker") {
		reformulator = new WalkerReformulator(&config);
	}
	else{
		ConsoleHelper::PrintError("Reformulator not found! Reformulator: " + config.GetString("reformulator"));
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	t = report->Stop();

	if (config.GetBool("debugmode")) {
		// Checking filepaths in the config file
		ConsoleHelper::PrintDebugInfo("Checking filepaths from the config...");
		report->Begin("Checking Filepaths");
		string notFoundPath = PathsChecker::IsPathsOk(&config);
		if (notFoundPath != "") {
			ConsoleHelper::PrintDebugError("Some file paths where not found! Not found path: " + notFoundPath);
			return CommonInterface::RunResult::ErrorsEncountered;
		}
		t = report->Stop();
	}

	// Parse original PDDL files
	ConsoleHelper::PrintInfo("Parsing PDDL files...");
	PDDLDriver originalDriver;
	if (originalDriver.parse(config.GetPath("domain"))) {
		ConsoleHelper::PrintError("Error parsing the domain file!");
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	if (originalDriver.parse(config.GetPath("problem"))) {
		ConsoleHelper::PrintError("Error parsing the problem file!");
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	t = report->Stop();

	// Convert PDDL format
	ConsoleHelper::PrintInfo("Converting PDDL format...");
	report->Begin("Converison of PDDL format");
	PDDLDomain domain = PDDLConverter::Convert(originalDriver.domain);
	PDDLProblem problem = PDDLConverter::Convert(&domain, originalDriver.problem);
	PDDLInstance instance = PDDLInstance(&domain, &problem);
	t = report->Stop();
	
	// Reformulate the PDDL file
	ConsoleHelper::PrintInfo("Reformulating PDDL...");
	report->Begin("Reformulation of PDDL");
	PDDLInstance reformulatedInstance = reformulator->ReformulatePDDL(&instance);
	t = report->Stop();
	
	// Generate new PDDL files
	ConsoleHelper::PrintInfo("Generating PDDL files...");
	report->Begin("Generating PDDL");
	PDDLCodeGenerator pddlGenerator = PDDLCodeGenerator(PDDLDomainCodeGenerator(&domain), PDDLProblemCodeGenerator(&domain, &problem));
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	t = report->Stop();

	// Throw the new pddl files into Fast Downward
	ConsoleHelper::PrintInfo("Run new PDDL files with Fast Downward...");
	report->Begin("Running FastDownward");
	DownwardRunner runner = DownwardRunner();
	runner.RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	auto runRes = runner.ParseDownwardLog();
	if (runRes != DownwardRunner::FoundPlan) {
		ConsoleHelper::PrintError("No solution could be found for the plan");
		t = report->Stop();
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	t = report->Stop();

	if (config.GetBool("debugmode")) {
		// Check to make sure the reformulated plan also matches the reformulated problem and domain
		ConsoleHelper::PrintDebugInfo("Validate reformulated SAS plan...");
		report->Begin("Validating reformulated SAS plan");
		auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName);
		if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
			ConsoleHelper::PrintDebugError("Output plan is not valid for reformulated domain and problem!");
			t = report->Stop();
			return CommonInterface::RunResult::ErrorsEncountered;
		}
		t = report->Stop();
	}

	// Parse the output SAS plan
	ConsoleHelper::PrintInfo("Parsing SAS Plan...");
	report->Begin("Parse SAS plan");
	SASParser sasParser;
	filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
	SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
	t = report->Stop();

	// Rebuild the SAS Plan
	ConsoleHelper::PrintInfo("Rebuilding the SAS plan...");
	report->Begin("Rebuild SAS plan");
	SASPlan outputPlan = reformulator->RebuildSASPlan(&reformulatedSASPlan);
	t = report->Stop();

	// Output the new SAS plan
	ConsoleHelper::PrintInfo("Output new SAS Plan...");
	report->Begin("Output SAS plan");
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
	t = report->Stop();

	if (config.GetBool("debugmode")) {
		// Validate reformulated plan works with original domain and problem
		ConsoleHelper::PrintDebugInfo("Validate new SAS plan...");
		report->Begin("Validate new SAS plan");
		auto newSASValidatorResult = PlanValidator::ValidatePlan(config, config.GetPath("domain"), config.GetPath("problem"), CommonInterface::OutputSASName);
		if (newSASValidatorResult != PlanValidator::PlanMatch) {
			ConsoleHelper::PrintDebugError("Output plan is not valid for original domain and problem!");
			t = report->Stop();
			return CommonInterface::RunResult::ErrorsEncountered;
		}
		t = report->Stop();
	}
	
	return CommonInterface::RunResult::RanWithoutErrors;
}
