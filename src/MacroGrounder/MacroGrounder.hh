#include "../Walker/Path.hpp"
#include "../EntanglementFinder/EntanglementOccurance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include <unordered_map>

class MacroGrounder {
public:
    struct RunData {
		double MinimumQualityPercent = 0;
		int MaxCandidates = 1;
	};
    
    RunData Data;
    std::vector<std::vector<PDDLAction>> macros;
    PDDLInstance* pddl;

    std::vector<EntanglementOccurance> WalkerWheelchair(std::vector<Path> &paths);
    MacroGrounder(RunData data, std::vector<std::vector<PDDLAction>> &macs) : Data(data), macros(macs) {};
private:
    bool CompareMacros(EntanglementOccurance m1, EntanglementOccurance m2);
    std::vector<EntanglementOccurance> GetTop(std::vector<EntanglementOccurance> &macs);
};