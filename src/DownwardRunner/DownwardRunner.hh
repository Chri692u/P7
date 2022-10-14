#ifndef DOWNWARDRUNNER_HH
#define DOWNWARDRUNNER_HH

#include <string>
#include <fstream>

#include "../Config/config.hh"

struct DownwardRunner {
    enum DownwardRunnerResult { None, FoundPlan, DidNotFindPlan };
    static enum DownwardRunnerResult RunDownward(Config config, std::string reformulatedDomain, std::string reformulatedProblem);
};

#endif
