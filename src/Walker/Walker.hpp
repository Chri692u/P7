#ifndef WALKER
#define WALKER

#include <vector>
#include <list>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristic.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "WidthFunctions/BaseWidthFunction.hh"
#include "ActionGenerator.hpp"
#include "../RunReport/RunReport.hh"
#include "../Helpers/ProgressBarHelper.hh"

#include "../Config/Config.hh"
#include "../Helpers/Hashes.hh"

struct Path {
    std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};

    friend bool operator==(const Path& lhs, const Path& rhs) {
        return lhs.steps == rhs.steps;
    }
};

namespace std {
    template <>
    struct hash<Path> {
        auto operator()(const Path& s) const -> size_t {
            std::size_t seed = s.steps.size();
            for (auto& i : s.steps) {
                seed ^= hash<PDDLActionInstance>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

class Walker {
public:
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, Config *config) : 
    instance(instance), actionGenerator(actionGenerator), config(config) {}
    Path Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunction, const PDDLState *state);
    std::vector<Path> Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc);
    unsigned int GetTotalActionsGenerated() { return actionGenerator.GetTotalActionsGenerated(); };
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    Config *config;
};

#endif
