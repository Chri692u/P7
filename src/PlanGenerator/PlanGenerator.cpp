#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include "PlanGenerator.hh"

using namespace std;
namespace fs = std::filesystem;

void PlanGenerator::GenerateSASPlans(Config config, string domainFile) {
    vector<string> filePaths;
    DownwardRunner runner = DownwardRunner();
    SASParser parser = SASParser();

    int problemAmount = 5;
    int NoTimeLimit = -1;

    string domainFolder = domainFile.substr(0, domainFile.find_last_of("\\/"));
    string domainName = domainFolder.substr(domainFolder.find_last_of("/\\") + 1);

    srand(time(NULL));
    fs::path relativePath = fs::current_path();

    //Find path of x problems in the domain
    for (const auto & entry : fs::directory_iterator(domainFolder)){
        filePaths.push_back(relativePath / entry.path());
    }

    string cdstring = "";
    while (!fs::is_directory(cdstring + "src") || !fs::exists(cdstring + "src")) {
        cdstring = cdstring + "../";
    }

    if (!fs::is_directory(cdstring + domainName + "Plans") || !fs::exists(cdstring + domainName + "Plans")) {
        cout << "didnt find plans, running downward" << endl;
        fs::create_directory(cdstring + domainName + "Plans");
        unordered_set<int> attempts;
        for(int i = 0; i < problemAmount && i < filePaths.size()-1; ++i){
            // int attempt = rand() % filePaths.size();
            // // least retarded c++ code
            int attempt = i;
            while (filePaths[attempt].substr(filePaths[attempt].find_last_of("/\\") + 1) == "domain.pddl" || attempts.contains(attempt)){
                attempt += 1;
            }
            attempts.emplace(attempt);
            PDDLDriver* driver = new PDDLDriver();
            fs::path domainPath = relativePath / domainFile;
            fs::path problemPath = relativePath / domainFolder / filePaths[attempt];
            
            driver->parse(domainPath);
            driver->parse(problemPath);

            domains.push_back(PDDLConverter::Convert(driver->domain));
            problems.push_back(PDDLConverter::Convert(&(domains.at(i)), driver->problem));

            cout << "running downward for problem " << attempt << endl;
            runner.RunDownward(config, domainPath, problemPath, NoTimeLimit);

            //Save the plan
            SASPlan plan = parser.Parse(relativePath / "sas_plan");
            sasplans.push_back(plan);
            // create plan file
            ofstream ffs(cdstring + domainName + "Plans/" + to_string(attempt));
            ffs.close();
            SASCodeGenerator sascodegen;
            sascodegen.GenerateCode(plan, cdstring + domainName + "Plans/" + to_string(attempt));
        }
    } else {
        cout << "found domain sas plans" << endl;

        vector<int> attempts;
        bool flag = false;
        while (!flag){
            for (const auto & entry : fs::directory_iterator(cdstring + domainName + "Plans")){
                string path = entry.path();
                attempts.push_back(stoi(path.substr(path.find_last_of("/\\") + 1)));
            }
            if (attempts.size() == problemAmount) {
                flag = true;
            } else {
                attempts.clear();
            }
        }
        for (int i = 0; i < attempts.size(); ++i) {
            int attempt = attempts.at(i);
            PDDLDriver* driver = new PDDLDriver();
            fs::path domainPath = relativePath / domainFile;
            fs::path problemPath = relativePath / domainFolder / filePaths[attempt];
            
            driver->parse(domainPath);
            driver->parse(problemPath);

            domains.push_back(PDDLConverter::Convert(driver->domain));
            problems.push_back(PDDLConverter::Convert(&(domains.at(i)), driver->problem));

            //Save the plan
            SASPlan plan = parser.Parse(relativePath / (cdstring + domainName + "Plans") / to_string(attempt));
            sasplans.push_back(plan);
        }
    }
}