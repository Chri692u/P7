#include "PathChecker.hh"

using namespace std;

string PathsChecker::IsPathsOk(Config* config) {
	if (!CheckItem(config->DomainFile))
		return config->DomainFile.Content;
	if (!CheckItem(config->ProblemFile))
		return config->ProblemFile.Content;
	if (!CheckItem(config->DownwardPath))
		return config->DownwardPath.Content;
	if (!CheckItem(config->ValidatorPath))
		return config->ValidatorPath.Content;
	return "";
}

template <typename T>
bool PathsChecker::CheckItem(ConfigItem<T> item) {
	if (item.Content != "") {
		if (!FileHelper::DoesFileExist(item.Content)) {
			return false;
		}
	}
	else {
		if (!FileHelper::DoesFileExist(item.DefaultContent)) {
			return false;
		}
	}
	return true;
}