#ifndef FileVerifier_HH
#define FileVerifier_HH

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

#include "../Helpers/StringHelper.hh"

class FileVerifier {
public:
	bool VerifyFiles(std::string sourceFile, std::string targetFile);
	bool VerifyFiles(std::string sourceFile, std::string targetFile, std::vector<char> purgeChars);
};

#endif