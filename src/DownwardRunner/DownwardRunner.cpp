#include "DownwardRunner.hh"

using namespace std;

const string RunnerLogName = "downwardLog";

DownwardRunner::DownwardRunnerResult DownwardRunner::RunDownward(Config config, string reformulatedDomain, string reformulatedProblem) {
    string path = config.DownwardPath.Content;
    string search = config.DownwardOptions.Search.Content;
    string heuristic = config.DownwardOptions.Heuristic.Content;

    string command = path + " " + reformulatedDomain + " " + reformulatedProblem + " --search \"" + search + "(" + heuristic + "())\"" + " > " + RunnerLogName;
    system(command.c_str());

	ifstream stream(RunnerLogName);
	string content((istreambuf_iterator<char>(stream)),
		(istreambuf_iterator<char>()));
	stream.close();
	if (content.find("Solution found.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::FoundPlan;
	if (content.find("Search stopped without finding a solution.") != string::npos)
		return DownwardRunner::DownwardRunnerResult::DidNotFindPlan;
	return DownwardRunner::DownwardRunnerResult::None;
}
