#include <fstream>

#include "Steps.h"


// Loads steps from a file
Steps Steps::loadSteps(const std::string& filename,bool &isOpen) {
	Steps steps;
	std::ifstream steps_file(filename);
	if (!steps_file.is_open())
	{
		isOpen = false;
		return steps;
	}
	steps_file >> steps.randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		string step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

// Saves steps to a file
void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}
