#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include "PlanGenerator.hh"


using namespace std;
namespace fs = std::filesystem;

void PlanGenerator::GenerateSASPlans(Config config, string domainFolder) {
    vector<string> filePaths;
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

            domains.push_back(PDDLConverter::Convert(driver->domain));
            problems.push_back(PDDLConverter::Convert(&(domains.at(i)), driver->problem));
            sasplans.push_back(plan);

            //Run downward
            runner.RunDownward(config, domainPath, problemPath, NoTimeLimit);

            filePaths.erase(filePaths.begin()+attempt);   
        } else {
            attempt = rand() % filePaths.size();
        }
    }
}