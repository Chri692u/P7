#include "PathChecker.hh"

using namespace std;

bool PathsChecker::IsPathsOk(Config* config) {
	if (!CheckItem(config->DomainFile))
		return false;
	if (!CheckItem(config->ProblemFile))
		return false;
	if (!CheckItem(config->DownwardPath))
		return false;
	if (!CheckItem(config->ValidatorPath))
		return false;
	return true;
}

template <typename T>
bool PathsChecker::CheckItem(ConfigItem<T> item) {
	if (item.Content != "") {
		if (!FileHelper::DoesFileExist(item.Content)) {
			cout << "ERROR: File not found!" << endl;
			cout << "Name: " + item.Name << endl;
			cout << "Description: " + item.Description << endl;
			cout << "Current Path: " + filesystem::current_path().string() << endl;
			cout << "File path: " + item.Content << endl;
			return false;
		}
	}
	else {
		if (!FileHelper::DoesFileExist(item.DefaultContent)) {
			cout << "ERROR: File (USING DEFAULT) not found!" << endl;
			cout << "Name: " + item.Name << endl;
			cout << "Description: " + item.Description << endl;
			cout << "Current Path: " + filesystem::current_path().string() << endl;
			cout << "File path: " + item.DefaultContent << endl;
			return false;
		}
	}
	return true;
}