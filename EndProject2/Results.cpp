#include <limits>
#include <fstream>

#include "Results.h"
#include <iostream>//for cout
using namespace std;

// Loads results from a file and sets the score
Results Results::loadResults(const std::string& filename,int &resultsScore, bool& isExist) {
	std::ifstream results_file(filename);
	Results results;
	if (!results_file.is_open())
	{
		isExist = false;
		return results;
	}
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	results_file >> resultsScore;
	return results;
}

// Saves results to a file with the final score
void Results::saveResults(const std::string& filename,int score) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file << '\n' << score;
	results_file.close();
}

// Compares the current results with the expected results
bool Results:: areTheSameResults( Results truthResults)
{
	bool flag = true;
	while (!this->results.empty() && !truthResults.results.empty())
	{
		auto myResult = this->popResult();
		auto specificTruthResult = truthResults.popResult();

		if (myResult.first != specificTruthResult.first)
		{
			string specificTruthResultString;
			if ((int)specificTruthResult.second == 0)
			{
				specificTruthResultString = "Mario Dead";
			}
			else {
				specificTruthResultString = "Finished";
			}
			system("cls");
			cout << "TEST FAILED - the result in actual game was in " << myResult.first <<" iteration and in the expected result was "<< specificTruthResult.first <<" iteration" << endl;
			flag=false;
		}
		else if (myResult.second != specificTruthResult.second)
		{
			string myRestultString;
			string specificTruthResultString;
			if ((int)specificTruthResult.second == 0)
			{
				specificTruthResultString = "Mario Dead";
				myRestultString = "Finished";
				
			}
			else  if ((int)specificTruthResult.second == 1) {
				specificTruthResultString = "finished";
				myRestultString = "Mario Dead";
			}
			else
			{
				if ((int)myResult.second==0)
				{
					myRestultString = "Mario Dead";
				}
				else {
					myRestultString = "finished";
				}
				specificTruthResultString = "invalid value";
			}
			
			system("cls");
			cout << "TEST FAILED - the actual game says " << myRestultString << " and the expected result says " << specificTruthResultString << endl;
			cout << "That was at " << myResult.first << " iteration in the actual game" << endl;
			flag = false;
		}

	}
	if (!this->results.empty())
	{
		system("cls");
		cout << "TEST FAILED - the actual game result has more results than the expected game result"<<endl;
		flag = false;
	}
	else if (!truthResults.results.empty())
	{
		system("cls");
		cout << "TEST FAILED - The actual game result has less results than the expected game result";
		flag = false;
	}
	this->results.clear();
	return flag;
}

