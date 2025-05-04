#include "DonkeyGame.h"
#include <chrono>


using namespace std;



//Controls the Main Gameplay Loop, Handling Player Movement, Barrel Interactions, and Game States
void DonkeyGame::run()
{
	Steps steps;
	Results results;
	
	//for random numbmer
	long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	srand(random_seed);
	steps.setRandomSeed(random_seed);


	bool deletedBarrel = false;
	int n;
	score = 0;
	int numOfFiles = Dboard.getAmountOfFiles();

	//there is not any file
	if (numOfFiles == 0)
	{
		system("cls");
		gotoxy(40, 12);
		cout << "THERE IS NO FILES" << endl;
		Sleep(3000);
		system("cls");
		return;
	}


	if (!loadBoardToTheGame())
	{
		//was the last file
		return;
	}

	Dboard.reset(3, score);

	Mario mario(Dboard);
	AllGhosts theGhosts(Dboard, mario);
	// Create the barrels.
	AllBarrels allBarrels(Dboard, mario);
	countStepsInGame = 0;


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

		Sleep(100);

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
				saveSteps(steps, Dboard.getNameFileI(curr_file));// save the steps at this game
				score = score - 50;
				results.addResult(iteration, Results::MARIO_DEAD);
				saveResults(results, Dboard.getNameFileI(curr_file));
				system("cls");
				gotoxy(40, 12);
				cout << "YOU DEAD GAME OVER" << endl;
				Sleep(3000);
				system("cls");
				gotoxy(0, 0);
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
				saveSteps(steps, Dboard.getNameFileI(curr_file));// save the steps at this game
				score = score + 100;
				results.addResult(iteration, Results::FINISHED);
				saveResults(results, Dboard.getNameFileI(curr_file));

				curr_file = 0;

				system("cls");
				gotoxy(40, 12);
				cout << "YOU ARE THE WINNER" << endl;
				gotoxy(41, 13);
				cout << "YOUR SCORE : " << score << endl;
				Sleep(3000);



				break;
			}
			else {//there are more maps

				saveSteps(steps, Dboard.getNameFileI(curr_file));// save the steps at this game
				results.addResult(iteration, Results::FINISHED);
				score = score + 100;
				saveResults(results, Dboard.getNameFileI(curr_file));

				//for random numbmer
				long random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
				srand(random_seed);
				steps.setRandomSeed(random_seed);

				system("cls");
				gotoxy(40, 12);
				cout << "YOU PASS TO NEXT MAP" << endl;
				Sleep(1000);

				system("cls");
				gotoxy(0, 0);


				curr_file++;


				if (!loadBoardToTheGame())
				{
					return;
				}
				resetGame(allBarrels, theGhosts, mario.getMarioLife()); // reset the game in the new board that was taken from load
				mario.resetMario();
			}
		}

	}

}

//get the key pressed from kbhit and add steps
void DonkeyGame::getKeys(int& keyPressed1, int& keyPressed2,size_t iteration, Steps& steps)
{
	bool getESC = false;
	char specificStep[3];
	specificStep[2] = '\0';
	if (_kbhit())
	{
		keyPressed1 = _getch();
		if (keyPressed1 == (int)Mario::eKeys::ESC)
		{
			freezeGame();//freeze the game
			getESC = true;
		}
		Sleep(40);
		if (!getESC) {
			specificStep[0] = (char)keyPressed1;
			if (_kbhit())
			{
				keyPressed2 = _getch();
				if (keyPressed2 == (int)Mario::eKeys::ESC)
				{
					freezeGame();//freeze the game
				}
				else {
					specificStep[1] = (char)keyPressed2;
				}
			}
			else {
				specificStep[1] = (char)keyPressed2;
			}
		}
		steps.addStep(iteration, std::string(specificStep));
	}
}

//save the list of steps to file if we are on save mode
void DonkeyGame::saveSteps(Steps& steps, const std::string& filename)
{
	if (isSave)
	{
		std::string newFilename = filename.substr(0, filename.find_last_of('.'));
		newFilename = newFilename + ".steps";
		steps.saveSteps(newFilename);
		steps.clearStepsFromVecSteps();
	}
}

//save the list of result to file if we are on save mode
void DonkeyGame::saveResults(Results& results, const std::string& filename)
{
	if (isSave)
	{
		std::string newFilename = filename.substr(0, filename.find_last_of('.'));
		newFilename = newFilename + ".result";
		results.saveResults(newFilename,score);
		results.clearResultsFromVecResult();
		iteration = 0;
	}
}

//print the menu
void DonkeyGame::printMenu() const {
	cout << "(1) Start a full game" << endl;
	cout << "(2) Choose map" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

//Manages the Game Menu
void DonkeyGame::manageMenu() 
{
	printMenu();
		while (true)
		{
			int keyPressed = 0;
			if (_kbhit())
			{
				keyPressed = _getch();
				// // Start the game if '1' is pressed
				if (keyPressed == (int)DonkeyGame::MenuKeys::PLAY)
				{
					curr_file = 0;
					system("cls");
					run(); // Start the game by calling the run function
					system("cls");
					printMenu();
				}
				else if (keyPressed == (int)DonkeyGame::MenuKeys::CHOOSE_FILE)
				{
					system("cls");
					int numOfFiles = Dboard.getAmountOfFiles();
					cout << "CHOOSE SCREEN" << endl;
					for (int i = 0; i < numOfFiles; i++)
					{
						cout << i+1 << "." << Dboard.getNameFileI(i) << endl;
					}
					while (true)
					{
						cin >> keyPressed;
						if (keyPressed > 0 && keyPressed <= numOfFiles)
						{
							curr_file = keyPressed-1;
							system("cls");
							run(); // Start the game by calling the run function
							system("cls");
							printMenu();
							break;
						}
					}
				}
				else if (keyPressed == (int)DonkeyGame::MenuKeys::INSTRUCTION)//// Show instructions if '8' is pressed
				{
					system("cls");
					cout << "instruction" << endl;
					ShowInstructions();
					// Loop until '3' is pressed
					while (true)
					{
						keyPressed = _getch();
						if (keyPressed == (int)DonkeyGame::MenuKeys::BACKTOINSTRUCTION)  // Return to the menu if '3' is pressed
						{
							system("cls");
							printMenu();
							break;
						}
					}
				}
				else if (keyPressed == (int)DonkeyGame::MenuKeys::EXIT)// Exit the game if '9' is pressed
				{
					system("cls");
					break;
				}
			}
		}
}

//"Freeze the Game Until the ESC Key is Pressed"
void DonkeyGame::freezeGame() const
{
	int keyPressed = _getch();
		while ((keyPressed) != (int)Mario::eKeys::ESC)
		{
			keyPressed = _getch();
		}
	
}

// The instructions were provided by chat GPT
void DonkeyGame::ShowInstructions() const {
	// This function was written by the chat
	std::cout << "Donkey Kong - Game Instructions\n\n";
	std::cout << "Welcome to Donkey Kong!\n\n";
	std::cout << "In this game, you play as Mario (represented by '@'), and your goal is to rescue Pauline (represented by '$'). To succeed, you must reach Pauline's location while avoiding barrels thrown by Donkey Kong (represented by '&').\n\n";

	std::cout << "Main Menu:\n";
	std::cout << "1. Start New Game:\n";
	std::cout << "   Start the game at the first stage.\n";
	std::cout << "   You can choose Mario's movement direction during the game using the defined movement keys.\n\n";

	std::cout << "2. Select Map:\n";
	std::cout << "   Allows you to choose a specific stage from the available custom maps. Maps are loaded from .screen files.\n\n";

	std::cout << "8. Show Instructions and Keys:\n";
	std::cout << "   Displays the current game instructions.\n\n";

	std::cout << "9. Exit:\n";
	std::cout << "   Exit the game.\n\n";

	std::cout << "Movement Keys:\n";
	std::cout << "Left: 'a' or 'A' - Move Mario left.\n";
	std::cout << "Right: 'd' or 'D' - Move Mario right.\n";
	std::cout << "Up / Jump: 'w' or 'W' - Mario will jump upwards. If he is in motion, he will continue jumping in the direction he was moving.\n";
	std::cout << "   If Mario is on a ladder (represented by 'H'), pressing this key will make Mario climb the ladder.\n\n";
	std::cout << "Down: 'x' or 'X' - Move Mario down.\n";
	std::cout << "Stay: 's' or 'S' - Mario will stop moving.\n\n";

	std::cout << "Game Rules:\n";
	std::cout << "Donkey Kong & Barrels:\n";
	std::cout << "   Donkey Kong (represented by '&') stands at the top of the screen and throws barrels ('O') downward. The barrels will fall and hit various floors on the screen.\n";
	std::cout << "   When a barrel hits a floor (represented by '=', '<', '>'), it will move on the floor in the direction indicated by the floor's symbol (right, left, or straight).\n";
	std::cout << "   If a barrel doesn't hit a floor for 8 consecutive lines, it will explode and disappear. If Mario is within a radius of 2 units from the explosion (including diagonals), Mario will lose a life and the game will restart.\n\n";

	std::cout << "Floors and Ladders:\n";
	std::cout << "   Floors (represented by '=', '<', '>') allow barrels to move on them.\n";
	std::cout << "   If Mario is on a ladder (represented by 'H'), he can climb it by pressing the Up key ('w' or 'W').\n\n";

	std::cout << "Ghosts:\n";
	std::cout << "   Ghosts (represented by 'x') wander on the floors with random movement directions. They cannot climb ladders or fall off the floors.\n";
	std::cout << "   If Mario meets a ghost, he loses a life and the stage restarts.\n\n";

	std::cout << "The Hammer:\n";
	std::cout << "   The hammer (represented by 'p') is a power-up that Mario can collect. If Mario collects the hammer, he can use it to destroy barrels or kill ghosts by pressing 'p' or 'P'.\n";
	std::cout << "   The hammer only works in Mario's movement direction and must be activated before reaching the barrel or ghost.\n\n";

	std::cout << "Loading Custom Screens:\n";
	std::cout << "   The game supports custom stages loaded from .screen files. Files are named dkong_*.screen and loaded in lexicographical order.\n";
	std::cout << "   You can also choose to play a specific screen using option 2 from the menu.\n\n";

	std::cout << "Score:\n";
	std::cout << "   Mario earns 100 points for completing a stage successfully.\n";
	std::cout << "   If Mario loses a life, 50 points are deducted from his total score.\n";
	std::cout << "   Manage your score wisely to achieve the highest possible result!\n\n";

	std::cout << "Mario's Lives:\n";
	std::cout << "   Mario starts with three lives. If all lives are lost, the game will return to the main menu.\n\n";

	std::cout << "Game Boundaries:\n";
	std::cout << "   The game is played within a fixed screen size of 80x25 characters.\n";
	std::cout << "   Neither Mario nor barrels can move outside these boundaries.\n\n";
	std::cout << "   If a barrel reaches the boundary, it is destroyed and disappears from the game.\n\n";


	std::cout << "Winning the Game:\n";
	std::cout << "   If Mario reaches Pauline's location, he wins the stage. If there are more stages, Mario will continue with his remaining lives.\n\n";

	std::cout << "Good luck with the game!\n";
	std::cout << "Use the provided keys to avoid barrels, outsmart ghosts, and help Mario rescue Pauline!\n\n";

	std::cout << "Press 3 to return to the main menu.\n";
}

