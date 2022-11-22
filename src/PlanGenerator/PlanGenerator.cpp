#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include "PlanGenerator.hh"
#include "../SASParser/SASParser.hh"
#include "../DownwardRunner/DownwardRunner.hh"

using namespace std;
namespace fs = std::filesystem;

vector<SASPlan> GenerateSASPlans(Config config, string domainPath) {
    vector<string> filePaths; 
    std::vector<SASPlan> plans;
    DownwardRunner runner = DownwardRunner();
    SASParser parser = SASParser();

    int problemAmount = 5;
    int NoTimeLimit = -1;

    srand(time(NULL));

    //Find path of x problems in the domain
    for (const auto & entry : fs::directory_iterator(domainPath))
        filePaths.push_back(entry.path());
    
    //Read domain path and choose problemAmount to work with
    for(int i = 0; i<problemAmount; ++i){
        int attempt = rand() % filePaths.size();
        if (filePaths[attempt] != "domain.pddl"){
            //Run downward
            runner.RunDownward(config, domainPath, filePaths[attempt], NoTimeLimit);
            //Save the plan
           SASPlan plan = parser.Parse(filePaths[attempt]);
           plans.push_back(plan);
        } else {
            attempt = rand() % filePaths.size();
        }
    }
    return plans;
}
