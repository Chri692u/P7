#ifndef EntanglementFinder_HH
#define EntanglementFinder_HH

#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Walker/Walker.hpp"
#include "EntanglementOccurance.hh"

class EntanglementFinder {
public:
	/// <summary>
	/// The ceiling of the search (leave as -1 if you want the full path size)
	/// </summary>
	const int SearchCeiling;
	/// <summary>
	/// The floor of the search, minimum is 2 and maximum is the full length of the path
	/// </summary>
	const int SearchFloor;
	/// <summary>
	/// By how much the level should be reduced in each iteration.
	/// </summary>
	const double LevelReductionFactor;
	/// <summary>
	/// The minimum amount of times an action sequence have to occure to be counted as valid
	/// </summary>
	const int MinimumOccurance;

	EntanglementFinder(int searchFloor = 2, int searchCeiling = -1, double levelReductionFactor = 2, int minimumOccurance = 5) : SearchCeiling(searchCeiling), SearchFloor(searchFloor), LevelReductionFactor(levelReductionFactor), MinimumOccurance(minimumOccurance) {};

	/// <summary>
	/// Find entanglement candidates from a vector of paths
	/// </summary>
	std::unordered_map<size_t,EntanglementOccurance> FindEntangledCandidates(std::vector<Path> paths);
	/// <summary>
	/// Takes a set of Paths and splits them up into sets of PDDLActionInstances based on the level.
	/// </summary>
	void GenerateActionSet(std::vector<std::vector<PDDLActionInstance>>* currentValues, const std::vector<Path>* paths, const int level);
	/// <summary>
	/// Based on the values generated in the "GenerateActionSet" method
	/// </summary>
	void AddCandidatesIfThere(std::unordered_map<size_t, EntanglementOccurance>* candidates, std::vector<std::vector<PDDLActionInstance>> currentValues);
	/// <summary>
	/// Removes those values in the unordered_map where the occurance is less than the "MinimumOccurance" variable.
	/// </summary>
	void RemoveIfBelowMinimum(std::unordered_map<size_t, EntanglementOccurance>* candidates);
	/// <summary>
	/// Checks if two vectors of PDDLActionInstances are the same.
	/// </summary>
	bool IsEqual(std::vector<PDDLActionInstance>* lhv, std::vector<PDDLActionInstance>* rhv);
private:

};

#endif