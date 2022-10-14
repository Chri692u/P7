#ifndef RandomHeuristics_HH
#define RandomHeuristics_HH

#include <vector>

#include "BaseHeuristics.hh"
#include "Contexts/PDDLContext.hh"

template <class T>
class RandomHeuristic : public BaseHeuristics<T, PDDLContext> {
public:
	RandomHeuristic(PDDLContext context) : BaseHeuristics<T, PDDLContext>(context){
		// 0 for debugging purposes
		srand(0);
		//srand(time(NULL));
	}
	T NextChoice(std::vector<T> choices) override;
};

template <class T>
T RandomHeuristic<T>::NextChoice(std::vector<T> choices) {
	int rndNum = rand() % choices.size();
	return choices[rndNum];
}

#endif