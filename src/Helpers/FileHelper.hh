#ifndef FileHelper_HH
#define FileHelper_HH

#include <filesystem>

class FileHelper {
public:
	static bool DoesFileExist(std::filesystem::path fileName);
};

#endif