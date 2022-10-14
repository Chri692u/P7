#include "config.hh"

using namespace std;

int Config::ParseArgs(Config* config, int argc, char** argv){
    cxxopts::Options options("P7","Pure magic reformulations :)");

    config->DownwardOptions.Search.Description = GetSearchDesc();
    config->DownwardOptions.Heuristic.Description = GetSearchDesc();

    options.add_options()
        ("h,help", "Print usage")
        (config->DomainFile.Flag + "," + config->DomainFile.LongFlag, config->DomainFile.Description, cxxopts::value<std::string>()->default_value(config->DomainFile.DefaultContent))
        (config->ProblemFile.Flag + "," + config->ProblemFile.LongFlag, config->ProblemFile.Description, cxxopts::value<std::string>()->default_value(config->ProblemFile.DefaultContent))
        (config->DownwardPath.Flag + "," + config->DownwardPath.LongFlag, config->DownwardPath.Description, cxxopts::value<std::string>()->default_value(config->DownwardPath.DefaultContent))
        (config->DebugMode.Flag + "," + config->DebugMode.LongFlag, config->DebugMode.Description)
        (config->ValidatorPath.Flag + "," + config->ValidatorPath.LongFlag, config->ValidatorPath.Description, cxxopts::value<std::string>()->default_value(config->ValidatorPath.DefaultContent))
        (config->Reformulator.Flag + "," + config->Reformulator.LongFlag, config->Reformulator.Description, cxxopts::value<std::string>()->default_value(config->Reformulator.DefaultContent))
        (config->DownwardOptions.Search.Flag + "," + config->DownwardOptions.Search.LongFlag, config->DownwardOptions.Search.Description, cxxopts::value<std::string>()->default_value(config->DownwardOptions.Search.DefaultContent))
        (config->DownwardOptions.Heuristic.Flag + "," + config->DownwardOptions.Heuristic.LongFlag, config->DownwardOptions.Heuristic.Description, cxxopts::value<std::string>()->default_value(config->DownwardOptions.Heuristic.DefaultContent))
    ;

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        cout << options.help() << endl;
        return 1;
    }

    string domainPath = StringHelper::Trim(result[config->DomainFile.LongFlag].as<string>());
    StringHelper::RemoveCharacter(&domainPath, '\'');
    string problemPath = StringHelper::Trim(result[config->ProblemFile.LongFlag].as<string>());
    StringHelper::RemoveCharacter(&problemPath, '\'');
    string downwardpath = StringHelper::Trim(result[config->DownwardPath.LongFlag].as<string>());
    StringHelper::RemoveCharacter(&downwardpath, '\'');
    string validatorPath = StringHelper::Trim(result[config->ValidatorPath.LongFlag].as<string>());
    StringHelper::RemoveCharacter(&validatorPath, '\'');
    bool doValidate = false;
    if (result[config->DebugMode.LongFlag].count() != 0)
        doValidate = true;
    const string searchmethod = result[config->DownwardOptions.Search.LongFlag].as<string>();
    const string heuristicmethod = result[config->DownwardOptions.Heuristic.LongFlag].as<string>();
    string reformulatorAlgorithm = result[config->Reformulator.LongFlag].as<string>();
    StringHelper::Trim(&reformulatorAlgorithm);

    config->DownwardPath.Content = downwardpath;
    config->ValidatorPath.Content = validatorPath;
    config->DebugMode.Content = doValidate;
    config->DomainFile.Content = domainPath;
    config->ProblemFile.Content = problemPath;
    config->Reformulator.Content = reformulatorAlgorithm;
    config->DownwardOptions.Search.Content = searchmethod;
    config->DownwardOptions.Heuristic.Content = heuristicmethod;

    return 0;
}

// Options from here https://www.fast-downward.org/Doc/SearchEngine
string Config::GetSearchDesc() {
    return StringHelper::StringFormat("%s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n",
        "Search Method",
        "astar", "a* Search",
        "eager", "eager best-first search",
        "eager_greedy", "greedy search (eager)",
        "eager_wastar", "eager weighted A*",
        "ehc", "lazy enforced hill-climbing",
        "iterated", "iterated search",
        "lazy", "lazy best-first search",
        "lazy_greedy", "greedy search (lazy)",
        "lazy_wstar", "(weighted) A* search (lazy)");
}

// Options from here https://www.fast-downward.org/Doc/Evaluator
string Config::GetEvaluatorDesc() {
    return StringHelper::StringFormat("%s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n%-12s - %s\n",
        "Evaluator Method",
        "add", "additive heuristic",
        "blind", "blind heuristic",
        "cea", "context-enchanced additive heuristic",
        "cegar", "additive CEGAR heuristic",
        "cg", "causal graph heuristic",
        "ff", "FF heuristic",
        "hm", "h^m heuristic",
        "hmax", "Max heuristic",
        "lmcut", "Landmark-cut heuristic",
        "merge_and_shrink", "merge-and-shrink heuristic",
        "operatorcounting", "Operator-counting heuristic",
        "ipdb", "canonical pdb with hillclimbing algo");
}