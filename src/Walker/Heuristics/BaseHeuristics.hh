#ifndef BaseHeuristics_HH
#define BaseHeuristics_HH

#include <string>
#include <iostream>
#include <vector>

#include "Contexts/BaseContext.hh"

template <class T, class U>
class BaseHeuristics {
public:
	U Context;
	BaseHeuristics(U context) : Context(context) {}

	virtual T NextChoice(std::vector<T> choices) = 0;
};

#endif
