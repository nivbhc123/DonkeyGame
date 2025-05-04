#ifndef __baseDonkey_H
#define __baseDonkey_H
#include "AllBarrels.h"
#include "allGhosts.h"
#include "board.h"
#include "Steps.h"
#include "Results.h"

class BaseDonkey
{
public:
	enum class MenuKeys { PLAY = '1', CHOOSE_FILE = '2', INSTRUCTION = '8', BACKTOINSTRUCTION = '3', EXIT = '9' };

protected:

	Board Dboard;

	int curr_file = 0;

	//count the steps in the game
	size_t countStepsInGame = 0;

	//count the active barrels in the game
	int activeBarrels = 0;

	//count the iteration of the game
	size_t iteration = 0;

	//the score of the game
	int score = 0;

	//idicate if mario was bombes by the barrel
	bool isMarioDead = false;

	//Controls the Main Gameplay Loop, Handling Player Movement, Barrel Interactions, and Game States
	virtual void run() = 0;


	//"Reset the Game State by Resetting Barrels and Clearing Current Steps"
	void resetGame(AllBarrels& allBarrels, AllGhosts& allGhosts, int marioLife);

	//load board to game
	bool loadBoardToTheGame();

public:

	//ctor
	BaseDonkey(){}

	//virtual function to start a game
	virtual void startGame(){}



};

#endif

