#include "PathChecker.hh"

using namespace std;

string PathsChecker::IsPathsOk(Config* config) {
	if (!CheckItem(config->GetPath("domain")))
		return config->GetPath("domain");
	if (!CheckItem(config->GetPath("problem")))
		return config->GetPath("problem");
	if (!CheckItem(config->GetPath("downwardpath")))
		return config->GetPath("downwardpath");
	if (!CheckItem(config->GetPath("validatorpath")))
		return config->GetPath("validatorpath");
	return "";
}

bool PathsChecker::CheckItem(filesystem::path path) {
	if (!FileHelper::DoesFileExist(path)) {
		return false;
	}
	return true;
}