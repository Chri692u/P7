#include "CommonInterface.hh"

using namespace std;

enum CommonInterface::RunResult CommonInterface::Run(RunReport* report) {
	int64_t t;
	BaseReformulator* reformulator;

	cout << "Finding reformulator algorithm...";
	report->Begin("Finding Reformulator");
	if (config.Reformulator.Content == "SameOutput") {
		reformulator = new SameOutputReformulator();
	} else 	if (config.Reformulator.Content == "RandomWalker") {
		reformulator = new RandomWalkerReformulator();
	}
	else{
		cout << "   ✕" << endl;
		cout << "Reformulator not found!" << endl;
		cout << "Reformulator: " + config.Reformulator.Content << endl;
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	if (config.DebugMode.Content) {
		// Checking filepaths in the config file
		cout << "Checking filepaths from the config...";
		report->Begin("Checking Filepaths");
		if (!PathsChecker::IsPathsOk(&config))
			return CommonInterface::RunResult::ErrorsEncountered;
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;
	}

	// Parse original PDDL files
	cout << "Parsing PDDL files...";
	report->Begin("Parsing PDDL");
	PDDLDriver originalDriver;
	originalDriver.parse(config.DomainFile.Content);
	originalDriver.parse(config.ProblemFile.Content);	
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Convert PDDL format
	cout << "Converting PDDL format...";
	report->Begin("Converison of PDDL format");
	PDDLDomain domain = PDDLDomain(originalDriver.domain);
	PDDLProblem problem = PDDLProblem(originalDriver.problem, &domain);
	PDDLInstance instance = PDDLInstance(&domain, &problem);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Reformulate the PDDL file
	cout << "Reformulating PDDL...";
	report->Begin("Reformulation of PDDL");
	PDDLInstance reformulatedInstance = reformulator->ReformulatePDDL(&instance);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Generate new PDDL files
	cout << "Generating PDDL files...";
	report->Begin("Generating PDDL");
	PDDLCodeGenerator pddlGenerator;
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Throw the new pddl files into Fast Downward
	cout << "Run new PDDL files with Fast Downward...";
	report->Begin("Running FastDownward");
	auto runRes = DownwardRunner::RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	if (runRes != DownwardRunner::FoundPlan) {
		cout << "   ✕" << endl;
		cout << "No solution could be found for the plan" << endl;
		t = report->Stop();
		return CommonInterface::RunResult::ErrorsEncountered;
	}
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	if (config.DebugMode.Content) {
		// Check to make sure the reformulated plan also matches the reformulated problem and domain
		cout << "Validate reformulated SAS plan...";
		report->Begin("Validating reformulated SAS plan");
		auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName);
		if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
			cout << "   ✕" << endl;
			cout << "Output plan is not valid for reformulated domain and problem!" << endl;
			t = report->Stop();
			return CommonInterface::RunResult::ErrorsEncountered;
		}
		t = report->Stop();
		cout << "   ✓ " << t << "ms" << endl;
	}

	// Parse the output SAS plan
	cout << "Parse SAS Plan...";
	report->Begin("Parse SAS plan");
	SASParser sasParser;
	filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
	SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Rebuild the SAS Plan
	cout << "Rebuild the SAS plan...";
	report->Begin("Rebuild SAS plan");
	SASPlan outputPlan = reformulator->RebuildSASPlan(&reformulatedSASPlan);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	// Output the new SAS plan
	cout << "Output new SAS Plan...";
	report->Begin("Output SAS plan");
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
	t = report->Stop();
	cout << "   ✓ " << t << "ms" << endl;

	if (config.DebugMode.Content) {
		// Validate reformulated plan works with original domain and problem
		cout << "Validate new SAS plan...";
		report->Begin("Validate new SAS plan");
		auto newSASValidatorResult = PlanValidator::ValidatePlan(config, config.DomainFile.Content, config.ProblemFile.Content, CommonInterface::OutputSASName);
		if (newSASValidatorResult != PlanValidator::PlanMatch) {
			cout << "   ✕" << endl;
			cout << "Output plan is not valid for original domain and problem!" << endl;
			t = report->Stop();
			return CommonInterface::RunResult::ErrorsEncountered;
		}
		t = report->Stop();
		cout << "   ✓" << t << "ms" << endl;
	}
	
	return CommonInterface::RunResult::RanWithoutErrors;
}
