#ifndef __Results_H
#define __Results_H

#include <list>


class Results {
public:
	enum ResultValue { MARIO_DEAD, FINISHED, noResult };
private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
public:

	// Loads results from a file and sets the score
	static Results loadResults(const std::string& filename,int& resultsScore,bool& isExist);

	// Saves results to a file with the final score
	void saveResults(const std::string& filename, int score) const;

	// Adds a new result
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}

	// Removes and returns the first result in the list
	std::pair<size_t, ResultValue> popResult() {
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}

	// Clears all stored results
	void clearResultsFromVecResult()
	{
		return results.clear();
	}

	// Compares the current results with the expected results
	bool areTheSameResults( Results truthResults);


};

#endif
