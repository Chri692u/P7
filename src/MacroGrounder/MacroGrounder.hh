#include "../Walker/Path.hpp"
#include "../EntanglementFinder/EntanglementOccurance.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

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
    int GetGoalsMet(std::vector<PDDLActionInstance> &seq);
    std::vector<EntanglementOccurance> GetTop(std::vector<std::vector<EntanglementOccurance>>);
};