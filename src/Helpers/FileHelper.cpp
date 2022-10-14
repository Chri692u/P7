#include "FileHelper.hh"

using namespace std;

bool FileHelper::DoesFileExist(filesystem::path fileName) {
	bool exists = filesystem::exists(fileName);
	return exists;
}