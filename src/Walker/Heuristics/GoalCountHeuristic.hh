#ifndef GOAL_COUNT_HEURISTIC
#define GOAL_COUNT_HEURISTIC

#include "BaseHeuristic.hh"

class GoalCountHeuristic : public BaseHeuristic {
public:
	GoalCountHeuristic(const PDDLDomain *domain, const PDDLProblem *problem) : BaseHeuristic(domain, problem){};

	PDDLActionInstance* NextChoice(PDDLState * state, std::vector<PDDLActionInstance> *choices) const override {
		int bestIndex = -1;
		int bestValue = -1;
		const int currentValue = Eval(state);
		auto engine = std::default_random_engine{};

		// The purpose of this init bullshitery is making it take random choices in case of equal values
		int init = rand() % choices->size();
		int i = init + 1;
	
		while (i != init) {
			i++;
			if (i >= choices->size()) {
				i = 0;
			}

			state->DoAction(&choices->at(i));
			int value = Eval(state);
			state->UndoAction(&choices->at(i));
			if (value >= bestValue) {
				bestIndex = i;
				bestValue = value;
			}
		}

		return &choices->at(bestIndex);
	}

	int Eval(const PDDLState *state) const override {
		int value = 0;
		for (auto iter = problem->goalState.unaryFacts.begin(); iter != problem->goalState.unaryFacts.end(); iter++)
			for (auto fact : (*iter).second)
				if (state->ContainsFact((*iter).first, fact))
					value++;
		for (auto iter = problem->goalState.multiFacts.begin(); iter != problem->goalState.multiFacts.end(); iter++)
			for (auto fact : (*iter).second)
				if (state->ContainsFact((*iter).first, &fact))
					value++;
		return value;
	};
private:
	
};

#endif