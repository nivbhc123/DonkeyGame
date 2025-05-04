#include "ghost.h"

// Constructor for the Ghost class:
// Initializes the ghost object with the game board, starting position, and character representation.
Ghost::Ghost(Board& board, int x,int y,char sign):Enemy(board,sign,x,y){

}

// Function to calculate the next move of the ghost.
void Ghost::calculateNextMove()
{
	
	if (diff_X == 0)
	{
		diff_X = 1;
	}

	int random_number = rand() % 100;

	if (random_number > 95)
	{
		diff_X = - (diff_X);
	}


	
	//virtual function, it will work if you climb Ghost ('X')
	climb();


	//check if we at the end of floor
	if ((enemyPoint.currPosFromOriginalBoard(diff_X, 1) == (char)Board::floorKeys::EMPTY) || (enemyPoint.checkBorder(diff_X, diff_Y)) || (enemyPoint.currPosFromCurrentBoard(diff_X, diff_Y)==(char)Board::gameObjectKeys::REGULAR_GHOST) || (enemyPoint.currPosFromCurrentBoard(diff_X, diff_Y) == (char)Board::gameObjectKeys::CLIMB_GHOST))
	{
		if ((enemyPoint.currPosFromOriginalBoard(-diff_X, 1) == (char)Board::floorKeys::EMPTY) || (enemyPoint.checkBorder(-diff_X, diff_Y) || (enemyPoint.currPosFromCurrentBoard(-diff_X, diff_Y) == (char)Board::gameObjectKeys::REGULAR_GHOST)||(enemyPoint.currPosFromCurrentBoard(-diff_X, diff_Y) == (char)Board::gameObjectKeys::CLIMB_GHOST)))
		{
			diff_X = 0;
		}
		else {
			diff_X = -(diff_X);
		}
	}

}

// Function to execute the movement of the ghost
void Ghost::move()
{
	this->enemyPoint.move(diff_X, diff_Y, enemyPoint.currPosFromOriginalBoard(0, 0));
	this->enemyPoint.moveOnCurrBoard(diff_X, diff_Y, enemyPoint.currPosFromOriginalBoard(0, 0));
}


