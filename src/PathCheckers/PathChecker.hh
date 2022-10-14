#ifndef PathChecker_HH
#define PathChecker_HH

#include <iostream>

#include "../Config/config.hh"
#include "../Helpers/FileHelper.hh"

class PathsChecker {
public:
	static bool IsPathsOk(Config* config);
private:
	template <typename T>
	static bool CheckItem(ConfigItem<T> item);
};

#endif
