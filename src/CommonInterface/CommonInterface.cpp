#include "CommonInterface.hh"

using namespace std;
namespace fs = std::filesystem;

InterfaceStep<BaseReformulator*> CommonInterface::GetReformulator(int reformulatorIndex) {
	ConsoleHelper::PrintInfo("Finding reformulator algorithm...");
	Report->Begin("Finding reformulator");
	BaseReformulator* reformulator;
	if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "sameoutput") {
		reformulator = new SameOutputReformulator(&config, Report);
	}
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "greedyWalker") {
		reformulator = new GreedyWalkerReformulator(&config, Report);
	}
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "greedyResumeWalker") {
		reformulator = new GreedyResumeWalkerReformulator(&config, Report);
	}
	else if (config.GetItem<vector<string>>("reformulator").at(reformulatorIndex) == "queueWalker") {
		reformulator = new QueueWalkerReformulator(&config, Report);
	}
	else {
		ConsoleHelper::PrintError("Reformulator not found! Reformulator: " + config.GetItem<string>("reformulator"));
		return InterfaceStep<BaseReformulator*>(reformulator, false);
	}
	Report->Stop();
	return InterfaceStep<BaseReformulator*>(reformulator);
}

InterfaceStep<void> CommonInterface::CheckFilePaths() {
	ConsoleHelper::PrintDebugInfo("Checking filepaths from the config...");
	Report->Begin("Checking Filepaths");
	string notFoundPath = PathsChecker::IsPathsOk(&config);
	if (notFoundPath != "") {
		ConsoleHelper::PrintDebugError("Some file paths where not found! Not found path: " + notFoundPath);
		return InterfaceStep<void>(false);
	}
	Report->Stop();
	return InterfaceStep<void>();
}

InterfaceStep<PDDLDriver*> CommonInterface::ParsePDDLFiles() {
	ConsoleHelper::PrintInfo("Parsing PDDL files...");
	PDDLDriver* originalDriver = new PDDLDriver();
	Report->Begin("Parsing PDDL Files");
	if (originalDriver->parse(config.GetItem<filesystem::path>("domain"))) {
		ConsoleHelper::PrintError("Error parsing the domain file!");
		return InterfaceStep<PDDLDriver*>(originalDriver, false);
	}
	if (originalDriver->parse(config.GetItem<filesystem::path>("problem"))) {
		ConsoleHelper::PrintError("Error parsing the problem file!");
		return InterfaceStep<PDDLDriver*>(originalDriver, false);
	}
	Report->Stop();
	return InterfaceStep<PDDLDriver*>(originalDriver);
}

InterfaceStep<PDDLInstance*> CommonInterface::ConvertPDDLFormat(PDDLDriver* driver) {
	ConsoleHelper::PrintInfo("Converting PDDL format...");
	Report->Begin("Converison of PDDL format");
	static PDDLDomain domain = PDDLConverter::Convert(driver->domain);
	static PDDLProblem problem = PDDLConverter::Convert(&domain, driver->problem);
	PDDLInstance* instance = new PDDLInstance(&domain, &problem);
	Report->Stop();
	return InterfaceStep<PDDLInstance*>(instance);
}

InterfaceStep<void> CommonInterface::RunIteratively(BaseReformulator* reformulator, PDDLInstance* instance) {
	int timeLeft = config.GetItem<int>("totalTimeLimit") * 1000;
	int currentIncrementTimeLimit = config.GetItem<int>("startIncrement") * 1000;

	int iterativeProcess = Report->Begin("Solving Problem");

	DownwardRunner::DownwardRunnerResult runRes;
	int counter = 1;
	while (timeLeft > 0) {
		int reformulatorTimeLimit = (currentIncrementTimeLimit * 2) * config.GetItem<double>("timelimitSplit");
		int downwardTimeLimit = (currentIncrementTimeLimit * 2) - reformulatorTimeLimit;

		int iterationID = Report->Begin("Iteration " + to_string(counter), iterativeProcess);
		ConsoleHelper::PrintInfo("Iteration " + to_string(counter) + "(reformulator: " + to_string(reformulatorTimeLimit) + "ms, downward: " + to_string(downwardTimeLimit) + "ms)");

		// Run an iteration of our reformulation method
		auto result = RunSingle(reformulator, instance, iterationID, reformulatorTimeLimit, downwardTimeLimit);
		Report->Stop(iterationID);
		if (result.RanWithoutErrors) {
			// If we found a solution, stop iterating
			runRes = result.Data;
			break;
		}

		// Subtract the time it took to execute this iteration from the total allowed time
		timeLeft -= currentIncrementTimeLimit * 2;
		// Increase the time limit for the next iteration
		currentIncrementTimeLimit *= config.GetItem<int>("incrementModifier");
		// If the next iteration will take too long, only spend the amount of time possible within the overall time limit
		if (timeLeft - currentIncrementTimeLimit * 2 < 0)
			currentIncrementTimeLimit = timeLeft / 2;
		counter++;
	}
	if (runRes != DownwardRunner::FoundPlan) {
		Report->Stop(iterativeProcess, "false");
		ConsoleHelper::PrintError("Fast downward did not find a plan in time!");
		return InterfaceStep<void>(false);
	}
	Report->Stop(iterativeProcess, "true");
	return InterfaceStep<void>();
}

InterfaceStep<void> CommonInterface::RunDirect(BaseReformulator* reformulator, PDDLInstance* instance) {
	int directProcess = Report->Begin("Solving Problem");
	int timeLimit = config.GetItem<int>("totalTimeLimit") * 1000;

	if (RunSingle(reformulator, instance, directProcess, timeLimit, timeLimit).RanWithoutErrors) {
		Report->Stop(directProcess, "true");
		return InterfaceStep<void>();
	}
	else {
		Report->Stop(directProcess, "true");
		return InterfaceStep<void>(false);
	}
}

InterfaceStep<DownwardRunner::DownwardRunnerResult> CommonInterface::RunSingle(BaseReformulator* reformulator, PDDLInstance* instance, int reportID, int reformulatorTimeLimit, int downwardTimeLimit) {
	ConsoleHelper::PrintInfo("Reformulating PDDL...", 1);
	int reformulationID = Report->Begin("Reformulation of PDDL", reportID);
	reformulator->ReportID = reformulationID;
	reformulator->TimeLimit = reformulatorTimeLimit;
	PDDLInstance reformulatedInstance = reformulator->ReformulatePDDL(instance);
	Report->Stop();
	Report->Stop(reformulationID);

	// Generate new PDDL files
	ConsoleHelper::PrintInfo("Generating PDDL files...", 1);
	Report->Begin("Generating PDDL", reportID);
	PDDLCodeGenerator pddlGenerator = PDDLCodeGenerator(PDDLDomainCodeGenerator(reformulatedInstance.domain), PDDLProblemCodeGenerator(reformulatedInstance.domain, reformulatedInstance.problem));
	pddlGenerator.GenerateCode(reformulatedInstance, CommonInterface::TempDomainName, CommonInterface::TempProblemName);
	Report->Stop();

	// Throw the new pddl files into Fast Downward
	ConsoleHelper::PrintInfo("Run new PDDL files with Fast Downward...", 1);
	Report->Begin("Running FastDownward", reportID);
	DownwardRunner runner = DownwardRunner();
	runner.RunDownward(config, CommonInterface::TempDomainName, CommonInterface::TempProblemName, downwardTimeLimit);
	auto runRes = runner.ParseDownwardLog();
	Report->Stop();
	if (runRes != DownwardRunner::FoundPlan) {
		return InterfaceStep<DownwardRunner::DownwardRunnerResult>(runRes, false);
	}
	return InterfaceStep<DownwardRunner::DownwardRunnerResult>(runRes);
}

InterfaceStep<void> CommonInterface::ValidatePlans(string domainFile, string problemFile, string sasFile, string reportName) {
	ConsoleHelper::PrintDebugInfo(reportName);
	int parent = Report->Begin(reportName);
	auto reformulatedSASValidatorResult = PlanValidator::ValidatePlan(config, domainFile, problemFile, sasFile);
	if (reformulatedSASValidatorResult != PlanValidator::PlanMatch) {
		Report->Stop(parent, "false");
		ConsoleHelper::PrintDebugError("Output plan is not valid for reformulated domain and problem!");
		return InterfaceStep<void>(false);
	}
	Report->Stop(parent, "true");
	return InterfaceStep<void>(true);
}

InterfaceStep<SASPlan> CommonInterface::ParseSASPlan() {
	ConsoleHelper::PrintInfo("Parsing SAS Plan...");
	Report->Begin("Parse SAS plan");
	SASParser sasParser;
	filesystem::path sasPath = filesystem::path(CommonInterface::FastDownwardSASName);
	SASPlan reformulatedSASPlan = sasParser.Parse(sasPath);
	Report->Stop(to_string(reformulatedSASPlan.cost));
	return InterfaceStep<SASPlan>(reformulatedSASPlan);
}

InterfaceStep<SASPlan> CommonInterface::RebuildSASPlan(SASPlan* reformulatedSASPlan, BaseReformulator* reformulator, PDDLInstance* instance) {
	ConsoleHelper::PrintInfo("Rebuilding the SAS plan...");
	Report->Begin("Rebuild SAS plan");
	SASPlan outputPlan = reformulator->RebuildSASPlan(instance, reformulatedSASPlan);
	Report->Stop(to_string(outputPlan.cost));
	return InterfaceStep<SASPlan>(outputPlan);
}

InterfaceStep<void> CommonInterface::GenerateNewSASPlan(SASPlan outputPlan) {
	ConsoleHelper::PrintInfo("Output new SAS Plan...");
	Report->Begin("Output SAS plan");
	SASCodeGenerator sasGenerator;
	sasGenerator.GenerateCode(outputPlan, CommonInterface::OutputSASName);
	Report->Stop();
	return InterfaceStep<void>();
}

InterfaceStep<vector<SASPlan>> CommonInterface::GenerateLearningPlans(string path){
	ConsoleHelper::PrintInfo("Generating SAS Plans for learning...");
	Report->Begin("Learning SAS plans");
	PlanGenerator sasGenerator = PlanGenerator();
	vector<SASPlan> plans = sasGenerator.GenerateSASPlans(config, path);
	Report->Stop();
	return InterfaceStep<vector<SASPlan>>(plans);
}
/*
InterfaceStep<void> CommonInterface::LearnPlans(){
	return
}
*/

enum CommonInterface::RunResult CommonInterface::Run(int reformulatorIndex) {

	auto getReformulatorStep = GetReformulator(reformulatorIndex);
	if (!getReformulatorStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("debugmode")) {
		auto checkFilePathsStep = CheckFilePaths();
		if (!checkFilePathsStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	auto parsePDDLFilesStep = ParsePDDLFiles();
	if (!parsePDDLFilesStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto convertPDDLFormatStep = ConvertPDDLFormat(parsePDDLFilesStep.Data);
	if (!convertPDDLFormatStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (!isDirect) {
		auto runIterativelyStep = RunIteratively(getReformulatorStep.Data, convertPDDLFormatStep.Data);
		if (!runIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}
	else {
		auto runNonIterativelyStep = RunDirect(getReformulatorStep.Data, convertPDDLFormatStep.Data);
		if (!runNonIterativelyStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	if (config.GetItem<bool>("validate")) {
		auto validateSASPlanStep = ValidatePlans(CommonInterface::TempDomainName, CommonInterface::TempProblemName, CommonInterface::FastDownwardSASName, "Validating reformulated plan");
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	auto parseSASPlanStep = ParseSASPlan();
	if (!parseSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto rebuildSASPlanStep = RebuildSASPlan(&parseSASPlanStep.Data, getReformulatorStep.Data, convertPDDLFormatStep.Data);
	if (!rebuildSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	auto generateNewSASPlanStep = GenerateNewSASPlan(rebuildSASPlanStep.Data);
	if (!generateNewSASPlanStep.RanWithoutErrors)
		return CommonInterface::RunResult::ErrorsEncountered;

	if (config.GetItem<bool>("validate")) {
		auto validateSASPlanStep = ValidatePlans(config.GetItem<filesystem::path>("domain"), config.GetItem<filesystem::path>("problem"), CommonInterface::OutputSASName, "Validating rebuilded plan");
		if (!validateSASPlanStep.RanWithoutErrors)
			return CommonInterface::RunResult::ErrorsEncountered;
	}

	return CommonInterface::RunResult::RanWithoutErrors;
}
