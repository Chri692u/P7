#include "EntanglementEvaluator.hh"

using namespace std;

vector<EntanglementOccurance> EntanglementEvaluator::EvaluateAndSanitizeCandidates(unordered_map<size_t, EntanglementOccurance> candidates) {
	int preCount = candidates.size();

	// Setup default modifiers
	SetModifiersIfNotSet();

	// Modify remaining candidates Quality
	SetQualityByLength(&candidates);
	SetQualityByOccurance(&candidates);

	// Sanitize candidates
	RemoveMinimumQuality(&candidates);

	candidates = CandidateFilter(candidates);

	_RemovedCandidates = preCount - candidates.size();

	vector<EntanglementOccurance> sanitizedCandidates = SortCandidates(&candidates);
	if (sanitizedCandidates.size() > Data.MaxCandidates) {
		sanitizedCandidates.erase(sanitizedCandidates.begin() + Data.MaxCandidates, sanitizedCandidates.end());
	}

	return sanitizedCandidates;
}

vector<unordered_map<size_t, EntanglementOccurance>> EntanglementEvaluator::CandidateFilter(unordered_map<size_t, EntanglementOccurance> &candidates){
	vector<unordered_map<size_t, EntanglementOccurance>> realCandidates;

	for(auto cand : candidates){
		for (auto macro : macros){
			if (cand.second.Chain.size() != macro.size()) continue;
			for(int i = 0; macro.size() > i; ++i){
				if(macro.at(i).name != cand.second.Chain.at(i)->action->name){
					kasper = true;
				}
			}		
			if(!kasper) {
				realCandidates.push_back(cand);
			}
		}
	}
}

void EntanglementEvaluator::SetModifiersIfNotSet() {
	if (LengthModifier == nullptr)
		LengthModifier = EntanglementEvaluatorModifiers::LengthModifiers::Default;
	if (OccuranceModifier == nullptr)
		OccuranceModifier = EntanglementEvaluatorModifiers::OccuranceModifiers::Default;
}

void EntanglementEvaluator::RemoveMinimumQuality(unordered_map<size_t, EntanglementOccurance>* candidates) {
	const auto removeIfLessThan = [&](pair<size_t, EntanglementOccurance> const& x) { return x.second.Quality < Data.MinimumQualityPercent; };
	std::erase_if(*candidates, removeIfLessThan);
}

void EntanglementEvaluator::SetQualityByLength(unordered_map<size_t, EntanglementOccurance>* candidates) {
	double maxLength = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Chain.size() > maxLength)
			maxLength = (*itt).second.Chain.size();
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		double newQuality = (*itt).second.Quality * LengthModifier((*itt).second.Chain.size(), maxLength);
		(*itt).second.Quality *= min((double)1, newQuality);
	}
}

void EntanglementEvaluator::SetQualityByOccurance(unordered_map<size_t, EntanglementOccurance>* candidates) {
	double maxOccurance = 0;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		if ((*itt).second.Occurance > maxOccurance)
			maxOccurance = (*itt).second.Occurance;
	}
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		double newQuality = (*itt).second.Quality * OccuranceModifier((*itt).second.Occurance, maxOccurance);
		(*itt).second.Quality *= min((double)1, newQuality);
	}
}

vector<EntanglementOccurance> EntanglementEvaluator::SortCandidates(unordered_map<size_t, EntanglementOccurance>* candidates) {
	vector<EntanglementOccurance> sanitizedCandidates;
	for (auto itt = candidates->begin(); itt != candidates->end(); itt++) {
		int index = 0;
		for (int i = 0; i < sanitizedCandidates.size(); i++) {
			if ((*itt).second.Quality > sanitizedCandidates.at(i).Quality)
				break;
			index++;
		}
		auto realIndex = sanitizedCandidates.begin() + index;
		sanitizedCandidates.insert(realIndex, (*itt).second);
	}
	return sanitizedCandidates;
}
