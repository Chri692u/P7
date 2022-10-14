#include "FileVerifier.hh"

using namespace std;

bool FileVerifier::VerifyFiles(string sourceFile, string targetFile) {
    return VerifyFiles(sourceFile, targetFile, {'\n', '\r', '\t', ' '});
}

bool FileVerifier::VerifyFiles(string sourceFile, string targetFile, vector<char> purgeChars) {
    ifstream sourceStream(sourceFile);
    string sourceBuffer((istreambuf_iterator<char>(sourceStream)),
        istreambuf_iterator<char>());
    ifstream targetStream(targetFile);
    string targetBuffer((istreambuf_iterator<char>(targetStream)),
        istreambuf_iterator<char>());

    for (char character : purgeChars)
        StringHelper::RemoveCharacter(&(sourceBuffer), character);
    for (char character : purgeChars)
        StringHelper::RemoveCharacter(&(targetBuffer), character);

    if (sourceBuffer != targetBuffer)
        return false;
    return true;
}