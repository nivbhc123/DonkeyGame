#ifndef __LoadDonkeyGame_H
#define __LoadDonkeyGame_H
#include "baseDonkey.h"
#include "Steps.h"
#include "AllBarrels.h"
#include "allGhosts.h"
#include <Windows.h> // for Sleep 
#include <conio.h> // for kbhit+getch
#include "general.h"
#include <iostream>//for cout
#include "mario.h"
#include "board.h"
#include "barrel.h"



class LoadDonkeyGame : public BaseDonkey
{

	bool isSilent = false;

	//start the GAME
	void startGame() override
	{
		run();
	}

	// Runs the main game loop, handling movement, barrels, ghosts, and game state
	void run() override;

	// Gets the key pressed from steps and updates keyPressed1 and keyPressed2
	void getKeys(int& keyPressed1, int& keyPressed2, size_t iteration, Steps& steps);

	// Changes the file extension to ".steps"
	string changeFileNameToStep();

	// Changes the file extension to ".result"
	string changeFileNameToResult();

	// Checks if the game results match the expected results
	bool ifTheResultIsGood(Results& myResult);



public:

	//ctor
	LoadDonkeyGame(bool isSilent) :isSilent(isSilent) {}



};
#endif

