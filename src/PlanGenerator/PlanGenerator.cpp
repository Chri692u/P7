#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include "PlanGenerator.hh"


using namespace std;
namespace fs = std::filesystem;

vector<pair<SASPlan, PDDLInstance*>> PlanGenerator::GenerateSASPlans(Config config, string domainFolder) {
    vector<string> filePaths;
    vector<pair<SASPlan, PDDLInstance*>> plans;
    DownwardRunner runner = DownwardRunner();
    SASParser parser = SASParser();

    int problemAmount = 5;
    int NoTimeLimit = -1;

    srand(time(NULL));
    fs::path relativePath = fs::current_path();
    //Find path of x problems in the domain
    for (const auto & entry : fs::directory_iterator(domainFolder)){
        filePaths.push_back(relativePath / entry.path());
    }
    //Read domain path and choose problemAmount to work with
    for(int i = 0; i<problemAmount; ++i){
        int attempt = rand() % filePaths.size();
        if (filePaths[attempt] != "domain.pddl"){
            //Save the plan + pddl instance
            SASPlan plan = parser.Parse(relativePath / "sas_plan");
            PDDLDriver* driver = new PDDLDriver();
            fs::path domainPath = relativePath / domainFolder / "domain.pddl";
            fs::path problemPath = relativePath / domainFolder / filePaths[attempt];
            
            driver->parse(domainPath);
            driver->parse(problemPath);

            PDDLDomain domain = PDDLConverter::Convert(driver->domain);
            PDDLProblem problem = PDDLConverter::Convert(&domain, driver->problem);
            PDDLInstance* instance = new PDDLInstance(&domain, &problem);

            //Run downward
            runner.RunDownward(config, domainPath, problemPath, NoTimeLimit);

            filePaths.erase(filePaths.begin()+attempt);
            plans.push_back(make_pair(plan, instance));     
        } else {
            attempt = rand() % filePaths.size();
        }
    }
    return plans;
}