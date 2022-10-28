#include <iostream>

#include "Config/Config.hh"
#include "CommonInterface/CommonInterface.hh"
#include "RunReport/RunReport.hh"

using namespace std;

int main(int argc, char** argv){
	 Config config;

	 std::filesystem::path fileName = std::filesystem::path("settings.ini");
	 if (argc > 1)
		 fileName = std::filesystem::path(argv[1]);
	 config.ParseConfigFile(fileName); 

	RunReport report = RunReport();

	cout << "Running reformulator..." << endl;
	CommonInterface interface = CommonInterface(config);
	auto result = interface.Run(&report);
	cout << "Done!" << endl;
	if (result == CommonInterface::RunResult::RanWithoutErrors)
		report.Print();
	return 0;
}