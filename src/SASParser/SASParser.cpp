#include "SASParser.hh"

using namespace std;

SASPlan SASParser::Parse(filesystem::path path) {
    ifstream stream(path);
    string content( (istreambuf_iterator<char>(stream) ),
                       (istreambuf_iterator<char>()    ) );
    stream.close();
    return Parse(content);
}

SASPlan SASParser::Parse(string SAS) {
    vector<SASAction> actions;
    int cost;
    stringstream ss(SAS);
    string line;
    while (getline(ss, line)) {
        line = StringHelper::Trim(line);
        StringHelper::RemoveCharacter(&line, ')');
        StringHelper::RemoveCharacter(&line, '(');
        if (line[0] == ';') {
            cost = ParseCost(line);
        } else {
            SASAction newAction = ParseAction(line);
            actions.push_back(newAction);
        }
    }
    return SASPlan(actions, cost);
}

vector<string> tokenize(string const &str, const char delim) {
    stringstream ss(str);
    vector<string> tokens;
 
    string s;
    while (getline(ss, s, delim)) {
        tokens.push_back(s);
    }
    return tokens;
}

SASAction SASParser::ParseAction(string line) {
    StringHelper::RemoveCharacter(&line, '\r');
    StringHelper::RemoveCharacter(&line, '\n');
    vector<string> tokens = tokenize(line, ' ');
    string actionName = tokens.front(); tokens.erase(tokens.begin());
    vector<string> parameters = tokens;
    return SASAction(actionName, parameters);
}

int SASParser::ParseCost(string line) {
    int equalityIndex = line.find('=');
    if (equalityIndex == line.npos)
        return -1;
    line = line.substr(equalityIndex + 1);
    while (line.length() > 0 && !isdigit(line[0]))
        line = line.substr(1);
    
    string strInt = "";
    while (line.length() > 0 && isdigit(line[0])) {
        strInt += line[0];
        line = line.substr(1);
    }
    return atoi(strInt.c_str());
}