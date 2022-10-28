#ifndef EntanglementOccurance_HH
#define EntanglementOccurance_HH

#include <vector>

#include "../IntermediatePDDL/PDDLInstance.hh"

struct EntanglementOccurance {
public:
    size_t GetHash();
	std::vector<PDDLActionInstance*> Chain;
    int Occurance;
    int BetweenDifferentPaths;

    EntanglementOccurance(std::vector<PDDLActionInstance*> chain, int betweenDifferentPaths) : Chain(chain), Occurance(2), BetweenDifferentPaths(betweenDifferentPaths) {};
    EntanglementOccurance(std::vector<PDDLActionInstance*> chain, size_t hash, int betweenDifferentPaths) : Chain(chain), Occurance(2), Hash(hash), BetweenDifferentPaths(betweenDifferentPaths) {};
private:
    size_t Hash = 0;
};

#endif