#include "FileHelper.hh"

using namespace std;

bool FileHelper::DoesFileExist(filesystem::path fileName) {
	try {
		return filesystem::exists(filesystem::canonical(filesystem::absolute(fileName).lexically_normal()));
	}
	catch (const std::exception& e) {
		return false;
	}
	return false;
}