#ifndef DOWNWARDRUNNER_HH
#define DOWNWARDRUNNER_HH

#include <string>
#include <fstream>

#include "../Config/Config.hh"

class DownwardRunner {
public:
    enum DownwardRunnerResult { None, FoundPlan, DidNotFindPlan };
    void RunDownward(Config config, std::string reformulatedDomain, std::string reformulatedProblem);
    DownwardRunnerResult ParseDownwardLog();

    std::string RunnerLogName = "downwardLog";
};

#endif
