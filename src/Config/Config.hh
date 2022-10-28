#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include <map>

#include "../Helpers/StringHelper.hh"
#include "../Helpers/ConsoleHelper.hh"

class Config {
public:

    void ParseConfigFile(std::filesystem::path path);
    void ParseConfigItem(std::string line);


    int GetInteger(std::string name);
    bool GetBool(std::string name);
    std::string GetString(std::string name);
    std::filesystem::path GetPath(std::string name);
private:
    std::map<std::string, std::string> stringItems;
    std::map<std::string, std::filesystem::path> pathItems;
    std::map<std::string, int> intItems;
    std::map<std::string, bool> boolItems;
};

#endif
