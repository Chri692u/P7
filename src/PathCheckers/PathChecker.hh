#ifndef PathChecker_HH
#define PathChecker_HH

#include <iostream>

#include "../Config/Config.hh"
#include "../Helpers/FileHelper.hh"

class PathsChecker {
public:
	static std::string IsPathsOk(Config* config);
private:
	static bool CheckItem(std::filesystem::path path);
};

#endif
