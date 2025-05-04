#ifndef __Steps_H
#define __Steps_H

#include <list>

using std::string;

class Steps {
	long randomSeed = 0;
	std::list<std::pair<size_t, string>> steps; // pair: iteration, step
public:

	// Loads steps from a file
	static Steps loadSteps(const string& filename, bool& flag);

	// Saves steps to a file
	void saveSteps(const string& filename) const;

	// Sets the random seed value
	void setRandomSeed(long seed) {
		randomSeed = seed;
	}

	// Returns the random seed value
	long getRandomSeed() const {
		return randomSeed;
	}

	// Adds a step to the steps list
	void addStep(size_t iteration, string step) {
		steps.push_back({ iteration, step });
	}

	// Checks if the next step corresponds to the given iteration
	bool isNextStepOnIteration(size_t iteration) const {
		return !steps.empty() && steps.front().first == iteration;
	}

	// Retrieves and removes the next step from the list
	string popStep() {
		string step = steps.front().second;
		steps.pop_front();
		return step;
	}

	// Clears all steps from the list
	void clearStepsFromVecSteps()
	{
		steps.clear();
	}
};

#endif
