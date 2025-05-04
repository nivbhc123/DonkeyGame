#ifndef __ DonkeyGame_H
#define __ DonkeyGame_H
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



class DonkeyGame : public BaseDonkey
{

private:

	//check if we are on saev mode
	bool isSave = false;

	//print the menu
	void printMenu() const;

	//Manages the Game Menu
	void manageMenu();

	//"Freeze the Game Until the ESC Key is Pressed"
	void freezeGame() const;

	// The instructions were provided by chat GPT
	void ShowInstructions() const;

	//Controls the Main Gameplay Loop, Handling Player Movement, Barrel Interactions, and Game States
	void run() override;

	//get the key pressed from kbhit and add steps
	void getKeys(int& keyPressed1, int& keyPressed2, size_t iteration, Steps& steps);

	//save the list of steps to file if we are on save mode
	void saveSteps(Steps& steps, const std::string& filename);

	//save the list of result to file if we are on save mode
	void saveResults(Results& results, const std::string& filename);

	//start the GAME
	void startGame() override
	{
		manageMenu();
	}


public:

	//ctor
	DonkeyGame(bool isSave):isSave(isSave){}





};
#endif
