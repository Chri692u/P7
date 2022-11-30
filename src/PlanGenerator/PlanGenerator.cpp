#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include "PlanGenerator.hh"
#include "../SASParser/SASParser.hh"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../IntermediatePDDL/PDDLConverter.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

using namespace std;
namespace fs = std::filesystem;

vector<pair<SASPlan, PDDLInstance>> PlanGenerator::GenerateSASPlans(Config config, string domainPath) {
    vector<string> filePaths; 
    vector<pair<SASPlan, PDDLInstance>> plans;
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
            //Save the plan + pddl instance
            fs::path relativePath = fs::current_path();
            SASPlan plan = parser.Parse(relativePath / "sas_plan");

            PDDLDriver driver;
            driver.parse(filePaths[attempt]);
            driver.parse(domainPath);
            
            PDDLDomain domain = PDDLConverter::Convert(driver.domain);
            PDDLProblem problem = PDDLConverter::Convert(&domain, driver.problem);
            PDDLInstance* instance = new PDDLInstance(&domain, &problem);
            filePaths.erase(filePaths.begin()+attempt);

            plans.push_back(make_pair(plan, *instance));
        } else {
            attempt = rand() % filePaths.size();
        }
    }
    return plans;
}
