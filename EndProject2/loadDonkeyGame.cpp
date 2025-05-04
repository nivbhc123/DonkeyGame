#include "loadDonkeyGame.h"
#include "baseDonkey.h"

using namespace std;


// Gets the key pressed from steps and updates keyPressed1 and keyPressed2
void LoadDonkeyGame::getKeys(int& keyPressed1, int& keyPressed2, size_t iteration, Steps& steps)
{
	keyPressed1 = 0;
	keyPressed2 = 0;
	if (steps.isNextStepOnIteration(iteration))
	{
		string newStep= steps.popStep();
		keyPressed1 = newStep[0];
		keyPressed2 = newStep[1];
	}

}

// Runs the main game loop, handling movement, barrels, ghosts, and game state
void LoadDonkeyGame::run()
{
	Steps steps;
	Results results;
	if (isSilent)
	{
		Dboard.setSilent();
	}

	bool deletedBarrel = false;
	int n;
	score = 0;
	int numOfFiles = Dboard.getAmountOfFiles();

	//there is not any file
	if (numOfFiles == 0)
	{
		if (!isSilent)
		{
			system("cls");
			gotoxy(40, 12);
			cout << "THERE IS NO FILES" << endl;
			Sleep(3000);
			system("cls");
		}
		return;
	}


	if (!loadBoardToTheGame())
	{
		//was the last file
		return;
	}

	

	Mario mario(Dboard);
	AllGhosts theGhosts(Dboard, mario);
	// Create the barrels.
	AllBarrels allBarrels(Dboard, mario);
	countStepsInGame = 0;

	bool stepFileIsOpen = true;
	bool resultsFileIsOpen = true;

	//load the steps and result
	steps = Steps::loadSteps(changeFileNameToStep(), stepFileIsOpen);
	long random_seed = steps.getRandomSeed();
	srand(random_seed);

	if (!stepFileIsOpen)
	{
		system("cls");
		cout << "There is not steps file for: " << Dboard.getNameFileI(curr_file) << endl;
		return;
	}

	Dboard.reset(3, score);


	// Main game loop
	while (true)
	{
		iteration++;
		// Every 20 steps, increase the number of active barrels if possible.
		if (countStepsInGame % 20 == 0)
		{
			allBarrels.bornNewBarrel();
		}
		countStepsInGame++;
		int prevLife = mario.getMarioLife();
		int keyPressed1 = 0;
		int keyPressed2 = 0;

		getKeys(keyPressed1, keyPressed2, iteration, steps);

		if (!isSilent)
		{
			Sleep(50);
		}

		//check if mario meet barrel or meet ghost
		if ((!(mario.meetBarrel())) && (!(mario.meetGhost())))
		{
			mario.move(Mario::eKeys(keyPressed1));

			//KILL WHEN MARIO TURN AROUND
			if ((keyPressed2 == (char)Board::gameObjectKeys::HAMMER) || (keyPressed2 == (char)Board::gameObjectKeys::BIG_HAMMER))
			{
				mario.setTryToKill();
			}


			if ((!(mario.meetBarrel())) && (!(mario.meetGhost())))
			{
				for (int i = 0; i < allBarrels.getSize(); i++)//move every barrel
				{
					deletedBarrel = false;
					//check if mario "kill" barrel
					if (((allBarrels.getBarrel(i).getBarrelPoint().getX() - mario.getMarioDiffX() == mario.getPoint().getX()) && (allBarrels.getBarrel(i).getBarrelPoint().getY() == mario.getPoint().getY())) || ((allBarrels.getBarrel(i).getBarrelPoint().getX() == mario.getPoint().getX()) && allBarrels.getBarrel(i).getBarrelPoint().getY() == mario.getPoint().getY()))
					{
						if (mario.isMarioWantKill())
						{
							allBarrels.eraseBarrelIFromVec(i);
							deletedBarrel = true;
							i--;
						}
					}

					//move if this is not a deleted barrel
					if (!deletedBarrel) {
						if (!(allBarrels.getBarrel(i).move(isMarioDead)))//if move return false, thats mean that the barrel bomb and we need to reset mario
						{
							allBarrels.eraseBarrelIFromVec(i);
							i--;
						}
					}
					if (isMarioDead)
					{
						mario.marioDead();
						break;
					}
				}
				theGhosts.move();
			}

		}


		// Check if Mario's life has changed (Mario died).
		if (mario.getMarioLife() != prevLife)
		{
			if (mario.getMarioLife() == 0)//game over
			{
				
				score = score - 50;
				results.addResult(iteration, Results::MARIO_DEAD);

				//check if the results is good
				if (!ifTheResultIsGood(results))
				{
					if (!isSilent)
					{
						Sleep(500);
					}
					break;
				}

				if (!isSilent) {
					system("cls");
					gotoxy(40, 12);
					cout << "YOU DEAD GAME OVER" << endl;
					Sleep(3000);
					system("cls");
					gotoxy(0, 0);
					cout << "TEST PASSED";
				}
				else {
					cout << "TEST PASSED";
				}
				curr_file = 0;

				break;
			}
			else//only fault - if he fault, mario wae reset becouse he died
			{
				score = score - 50;
				results.addResult(iteration, Results::MARIO_DEAD);
				resetGame(allBarrels, theGhosts, mario.getMarioLife());
			}
		}
		if (mario.ifMarioMeetPauline())
		{
			//win all of the maps
			if (curr_file == numOfFiles - 1)
			{
				
				score = score + 100;
				results.addResult(iteration, Results::FINISHED);

				//check if the results is good
				if (!ifTheResultIsGood(results))
				{
					if (!isSilent)
					{
						Sleep(500);
					}
					break;
				}


				curr_file = 0;

				if (!isSilent)
				{
					system("cls");
					gotoxy(40, 12);
					cout << "YOU ARE THE WINNER" << endl;
					gotoxy(41, 13);
					cout << "YOUR SCORE : " << score << endl;
					Sleep(3000);
					system("cls");
					cout << "TEST PASSED";
				}
				else {
					cout << "TEST PASSED";
				}

				



				break;
			}
			else {//there are more maps

				results.addResult(iteration, Results::FINISHED);
				score = score + 100;
				//check if the results is good
				if (!ifTheResultIsGood(results))
				{
					if (!isSilent) {
						Sleep(500);
					}
					break;
				}

				if (!isSilent)
				{

					system("cls");
					gotoxy(40, 12);
					cout << "YOU PASS TO NEXT MAP" << endl;
					Sleep(1000);
					system("cls");
					gotoxy(0, 0);
				}

				curr_file++;

				if (!loadBoardToTheGame())
				{
					return;
				}

				//load the steps and result
				steps = Steps::loadSteps(changeFileNameToStep(), stepFileIsOpen);
				if (!stepFileIsOpen)
				{
					system("cls");
					cout << "There is not steps file for: " << Dboard.getNameFileI(curr_file) << endl;
					return;
				}
				long random_seed = steps.getRandomSeed();
				srand(random_seed);

				resetGame(allBarrels, theGhosts, mario.getMarioLife()); // reset the game in the new board that was taken from load
				mario.resetMario();

				
			
				iteration = 0;
			}
		}

	}

}


// Changes the file extension to ".steps"
string LoadDonkeyGame::changeFileNameToStep()
{
	string file =Dboard.getNameFileI(curr_file);
	file=file.substr(0, file.find_last_of('.'));
	string newFile = file + ".steps";
	return newFile;
}


// Changes the file extension to ".result"
string LoadDonkeyGame::changeFileNameToResult()
{
	string file = Dboard.getNameFileI(curr_file);
	file = file.substr(0, file.find_last_of('.'));
	string newFile = file + ".result";
	return newFile;
}


// Checks if the game results match the expected results
bool LoadDonkeyGame:: ifTheResultIsGood(Results& myResult)
{
	bool isExist = true;
	int truthScore;
	Results truthResult= Results::loadResults(changeFileNameToResult(),truthScore,isExist);

	if (!isExist)
	{
		system("cls");
		cout << "There is not result file for: " << Dboard.getNameFileI(curr_file) << endl;
		return false;
	}

	if (!myResult.areTheSameResults(truthResult))
	{
		return false;
	}
	else if (score != truthScore)
	{	
		system("cls");
		cout <<"The score is different" <<endl;
		return false;
	}
	return true;
}


