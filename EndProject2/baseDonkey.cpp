#include "baseDonkey.h"
#include <Windows.h> // for Sleep 
#include <conio.h> // for kbhit+getch
#include "general.h"
#include <iostream>//for cout
#include "mario.h"
#include "board.h"
#include "barrel.h"
#include "AllBarrels.h"


using namespace std;




//"Reset the Game State by Resetting Barrels and Clearing Current Steps"
void BaseDonkey::resetGame(AllBarrels& allBarrels, AllGhosts& allGhosts, int marioLife)
{

	// reset the hammer
	this->Dboard.setOriginalBoard(Dboard.getHammerXstartPose(), Dboard.getHammerYstartPose(), (char)Board::gameObjectKeys::HAMMER);

	allGhosts.resetAllGhosts();
	allBarrels.resetBarrels();
	Dboard.reset(marioLife, score);
	isMarioDead = false;
	this->activeBarrels = 0;
	this->countStepsInGame = 0;
}


//load board to game
bool BaseDonkey::loadBoardToTheGame()
{
	int n;
	int numOfFiles = Dboard.getAmountOfFiles();
	while (!Dboard.load(Dboard.getNameFileI(curr_file)))
	{
		if (!Dboard.ifBoardIsInSilent())
		{
			system("cls");
			gotoxy(40, 12);
			cout << "EROR- INVALID MAP" << endl;
		}
		if (curr_file == numOfFiles - 1)
		{
			if (!Dboard.ifBoardIsInSilent())
			{
				gotoxy(40, 13);
				cout << "NO MORE FILES" << endl;
				Sleep(3000);
				system("cls");
			}
			return false;
		}
		if (!Dboard.ifBoardIsInSilent())
		{
			gotoxy(40, 13);
			cout << "PRESS N OR n TO NEXT MAP" << endl;
			while (true)
			{
				if (_kbhit()) {
					n = _getch();
					if (n == 'n' || n == 'N')
					{
						system("cls");
						gotoxy(0, 0);
						break;
					}
				}
			}
		}
		curr_file++;
	}
	return true;
}

