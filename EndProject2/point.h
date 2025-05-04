#ifndef __point_H
#define __point_H
#include "board.h"


class Point
{
	const char sign;
	int x;
	int y;
	Board& Pboard;
	

public:

	//ctor
	Point(const char _sign, int _x, int _y,  Board& board);

	//Moves the point to a new position and updates its visual representation on the screen.
	void move(int diff_x, int diff_y,char ch);

	//Moves the point in the game's current board state and updates the board accordingly.
	void moveOnCurrBoard(int diff_x, int diff_y, char ch);

	//Draws the point at its current position with the specified character.
	void draw(char ch) const;

	//Retrieves the character at a position relative to the point on the original board.
	char currPosFromOriginalBoard(int diff_x, int diff_y) const;

	//Clears the current position of the point on the screen.
	void erase() const;

	//Checks if the point is on a floor tile.
	bool isFloor(int diff_x, int diff_y) const;


	//Checks if the point has reached the border of the game board.
	bool checkBorder(int diff_x, int diff_y) const;

	//Checks if the point is on a ladder.
	bool ifLadder(int diff_x, int diff_y) const;

	//Checks if the point is on an empty space.
	bool isEmpty (int diff_x,int diff_y)const;

	//Updates the point's position to new coordinates.
	void setPoint(int newX, int newY);

	//Updates the point's position in the current game board state.
	void setPointInCurrentBoard(char sign);

	//Checks if the point is on a barrel.
	bool isBarrel() const;

	//Checks if another point is within a radius of 2 units.
	bool ifPointInRadios2ToAnotherPoint(Point p) const;

	//Checks if the point is on Pauline's position.
	bool isPauline(int diff_x, int diff_y)const;

	//Checks if the point is on HAMMER
	bool isHammer() const;

	//Checks if the point is on a Ghost.
	bool isGhost() const;

	//Retrieves the character at a position relative to the point on the current board.
	char currPosFromCurrentBoard(int diff_x, int diff_y) const;

	//return x,y 
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}

	//check if  mario fall out of border
	bool noFloorInMap () const;



};

#endif

