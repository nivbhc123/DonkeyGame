#include "point.h"
#include "general.h" //go to x,y
#include <iostream> // for cout
#include "board.h"
using namespace std;

Point::Point(const char _sign, int _x, int _y,  Board& board): sign(_sign), x(_x), y(_y),Pboard(board) {}

//Clears the current position of the point on the screen.
void Point::erase() const
{
	if (!Pboard.ifBoardIsInSilent())//if we are not in silent mode
	{
		gotoxy(x, y);
		cout << ' ';
	}
}

//Draws the point at its current position with the specified character.
void Point::draw(char ch) const
{
	if (!Pboard.ifBoardIsInSilent())//if we are not in silent mode
	{
		gotoxy(x, y);
		cout << ch;
	}
}

//Moves the point to a new position and updates its visual representation on the screen.
void Point::move(int diff_x,int diff_y,char ch)
{
	if ((ch ==(char)Board::gameObjectKeys::HAMMER)&& (this->sign=='@'))
	{
		this->Pboard.setOriginalBoard(x,y,(char)Board::floorKeys::EMPTY);
		draw((char)Board::floorKeys::EMPTY);
	}
	else {
		draw(ch);
	}
	x = x + diff_x;
	y = y + diff_y;
	draw(this->sign);
}

//Moves the point in the game's current board state and updates the board accordingly.
void Point::moveOnCurrBoard(int diff_x, int diff_y, char ch)
{
	//take him back
	x = x - diff_x;
	y = y - diff_y;
	if (!Pboard.ifBoardIsInSilent())
	{
		gotoxy(x, y);
	}
	this->Pboard.setCurrentBoard(x, y, ch);
	x = x + diff_x;
	y = y + diff_y;
	if (!Pboard.ifBoardIsInSilent())
	{
		gotoxy(x, y);
	}
	this->Pboard.setCurrentBoard(x, y,sign);
}

//Retrieves the character at a position relative to the point on the original board.
char Point::currPosFromOriginalBoard(int diff_x, int diff_y) const
{
	return this->Pboard.getCharOriginalBoard(x + diff_x, y + diff_y);
}

//Retrieves the character at a position relative to the point on the original board.
char Point::currPosFromCurrentBoard(int diff_x, int diff_y) const
{
	return this->Pboard.getCharCurrBoard(x + diff_x, y + diff_y);
}

//Checks if the point has reached the border of the game board.
bool Point:: checkBorder(int diff_x, int diff_y) const
{
	if (this->currPosFromOriginalBoard(diff_x, diff_y) == (char)Board::gameObjectKeys::BORDER)
	{
		return true;
	}

	if ((x+diff_x<=Board::GAME_WIDTH-1 && x + diff_x >=0) && (y+diff_y>=0)) 
	{
		return false;
	}
	return true;
}

//Checks if the point is on a ladder.
bool Point::ifLadder(int diff_x, int diff_y) const
{
	if ((this->currPosFromOriginalBoard(diff_x, diff_y) == (char) Board::gameObjectKeys::LADDER))
	{
		return true;
	}
	return false;
}

//Checks if the point is on a floor tile.
bool Point:: isFloor(int diff_x, int diff_y) const
{
	return ((this->currPosFromOriginalBoard(diff_x, diff_y) == (int)Board::floorKeys::LEFT) || (this->currPosFromOriginalBoard(diff_x, diff_y) == (int)Board::floorKeys::RIGHT) || (this->currPosFromOriginalBoard(diff_x, diff_y) == (int)Board::floorKeys::SAME));
}

//Checks if the point is on an empty space.
bool Point::isEmpty(int diff_x, int diff_y)const
{
	if ((this->currPosFromOriginalBoard(diff_x, diff_y) ==(char)Board::floorKeys::EMPTY))
	{
		return true;
	}
	return false;
}

//Updates the point's position to new coordinates.
void Point::setPoint(int newX, int newY)
{
	x = newX;
	y = newY;
}

//Updates the point's position in the current game board state.
void Point:: setPointInCurrentBoard(char sign)
{
	this->Pboard.setCurrentBoard(x, y, sign);
}

//Checks if the point is on a barrel.
bool Point::isBarrel() const
{
	char tav = this->Pboard.getCharCurrBoard(x, y);
	if (tav ==(char) Board::gameObjectKeys::BARREL)//if there is barrel in curr board
	{
		return true;
	}
	return false;
}

//Checks if another point is within a radius of 2 units.
bool Point::ifPointInRadios2ToAnotherPoint(Point p) const
{
	if ((p.x <= this->x + 2) && (p.x >= this->x - 2) && (p.y <= this->y + 2) && (p.y >= this->y - 2))
	{
		return true;
	}
	return false;
}

//Checks if the point is on Pauline's position.
bool Point::isPauline(int diff_x, int diff_y)const
{
	if ((this->currPosFromOriginalBoard(diff_x, diff_y) == (char)Board::gameObjectKeys::PAULINE))
	{
		return true;
	}
	return false;
}

//Checks if the point is on HAMMER
bool Point::isHammer() const
{
	
	char tav = this->Pboard.getCharOriginalBoard(x,y);
	if (tav == (char)Board::gameObjectKeys::HAMMER)//if there is barrel in curr board
	{
		return true;
	}
	return false;
}

//Checks if the point is on a Ghost.
bool Point::isGhost() const
{
	char tav = this->Pboard.getCharCurrBoard(x, y);
	if (tav == (char)Board::gameObjectKeys::REGULAR_GHOST || tav== (char)Board::gameObjectKeys::CLIMB_GHOST)//if there is barrel in curr board
	{
		return true;
	}
	return false;
}

//check if  mario fall out of border
bool Point::noFloorInMap ()const
{
	if ((y >= Board::GAME_HEIGHT-1) || (currPosFromOriginalBoard(0,1)==(char)Board::gameObjectKeys::BORDER))
	{
		return true;
	}
	return false;
}









