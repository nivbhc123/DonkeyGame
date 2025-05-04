#include "mario.h"
#include "board.h"
#include "point.h"
#include "general.h"
#include <iostream> // for cout
using namespace std;

// return Mario's point
const Point& Mario:: getPoint() const
{
	return this->pointMario;
}

//Constructor for Initializing Mario's State and Position on the Board
Mario::Mario(Board& board) :Mboard(board), pointMario(sign, Mboard.getMarioXstartPose(), Mboard.getMarioYstartPose(), board)
{
	xStartPoseMario = Mboard.getMarioXstartPose();
	yStartPoseMario = Mboard.getMarioYstartPose();
	life = 3;
	diff_x = 0;
	diff_y = 0;
	countFalling = 0;
	countJump = 0;
	isJump=false;
	isclimb = false;
	isFall = false;
	hasHammer = false;
	TryKill = false;
	this->pointMario.draw(sign);
}

// return Mario's life
int Mario::getMarioLife() const
{
	return this->life;
}

//Initializing Mario's State, Position on the Board, and Reducing His Life by One
void Mario::resetMario()
{
	isFall = false;
	isJump = false;
	isclimb = false;
	hasHammer = false;
	TryKill = false;
	countFalling = 0;
	countJump = 0;
	diff_x = 0;
	diff_y = 0;

	xStartPoseMario = Mboard.getMarioXstartPose();
	yStartPoseMario = Mboard.getMarioYstartPose();

	
	this->pointMario.setPoint(xStartPoseMario,yStartPoseMario);
	this->pointMario.draw(sign);
}

//Handles Mario's Movement and Actions Based on Player Input and Game State
void Mario::move(eKeys key)
{
	TryKill = false;

	switch (key)
	{
	case eKeys::LEFT:
	case eKeys::left:
		// Move left if there's no floor blocking the way and Mario is not jumping
		if ((!(this->pointMario.isFloor(-1, 0)))&&(!isJump))
		{
			diff_x = -1;
		}
		break;
	case eKeys::RIGHT:
	case eKeys::right:
		// Move right if there's no floor blocking the way and Mario is not jumping
		if ((!(this->pointMario.isFloor(1, 0))) && (!isJump))
		{
			diff_x = 1;
		}
		break;
	case eKeys::UP:
	case eKeys::up:
			diff_y = -1;// Set movement direction to up
		break;
	case eKeys::DOWN:
	case eKeys::down:
		// Check if there's a ladder below Mario or you stand on floor and there is ladder under the floor; if so, allow downward movement
		if (this->pointMario.ifLadder(0, 2)|| this->pointMario.ifLadder(0, 1))
		{
			diff_x = 0;
			diff_y = 1;
		}
		break;
	case eKeys::STAY:
	case eKeys::stay:
		// If Mario is not on the floor, make him stay in place
		if (!(this->pointMario.isFloor(0, 0)))
		{
			diff_x = 0;
			diff_y = 0;
		}
		break;
	case eKeys::KILL:
	case eKeys::kill:
		// Check if mario is trying to kill
		if (hasHammer)
		{
			TryKill=true;
		}
		break;
	}
	
	//check if Mario take the Hammer
	if (this->pointMario.isHammer())
	{
		if (!Mboard.ifBoardIsInSilent())
		{
			gotoxy(Mboard.getLx(), Mboard.getLy() + 2);
			cout << "Mario Has Hammmer!!!";
		}
		hasHammer = true;
	}

	// Check if Mario reached the border of the board
	if (this->pointMario.checkBorder(diff_x, diff_y)) //check if we on border while walk
	{
		diff_x = 0;
		diff_y = 0;


		// If Mario was jumping, set him to fall from jumping
		if (countJump == 1)
		{
			isFallingFromJump = true;
		}
	}

	// Handle falling after jumping
	if ((isFallingFromJump) && (countJump == 0))
	{
		// If the space below Mario is empty, make him fall
		if ((this->pointMario.isEmpty(0, 1)))
		{
			countFalling = 2;
		}
		isFallingFromJump = false;// Reset jump state
		isJump = false; // Mark jumping as complete
		diff_y = 0;
	}
	if (isFallingFromJump)
	{
		diff_y = 1;
		countJump--;
	}
	

	// Handle upward movement
	if (diff_y == -1 && !isFall)
	{

		// If Mario is already jumping or not on a ladder, initiate a jump
		if ((isJump||(!(this->pointMario.ifLadder(0, 0)))) && (isclimb == false))
		{
			if ((countJump == 0)&& pointMario.isFloor(diff_x, diff_y)) // if there is florr when he want jump - we cancel it
			{
				diff_y = 0;
			}
			else if ((countJump == 1) && pointMario.isFloor(diff_x, diff_y)) // is there is floor 2 up from us we let him jump once
			{
				isJump = true;
				isFallingFromJump = true;
				diff_y = 0;
			}
			else { //Let him jump as usual.
				isJump = true;
				countJump++;
				if (countJump == 2)
				{
					isFallingFromJump = true;
				}
			}
		}

		// If Mario is on a ladder or floor and not jumping, climb
		else if ((this->pointMario.ifLadder(0, 0) || this->pointMario.isFloor(0, 0)) && (!isJump))//  to climb 
		{
			isclimb = true;
			diff_x = 0;
			//diff_y=-1
		}

		// If Mario is finishing a climb, stop movement
		else if (this->pointMario.isFloor(0, 1) && this->pointMario.ifLadder(0,2) && isclimb==true)//finish climb
		{
			isclimb = false;
			diff_x = 0;
			diff_y = 0;

		}

	}


	// Stop climbing when reaching the end of a ladder
	if ((diff_y == 1) && (this->pointMario.ifLadder(0, 0)) && (this->pointMario.isFloor(0, 1)))
	{
		isclimb = false;
		diff_x = 0;
		diff_y = 0;
	}


	// Handle Mario's fall
	if ((isFall == true) && (this->pointMario.isFloor(0,1))&& (countFalling < (int)eKeys::MARIO_MAX_FALLING))// finish the fall
	{
		diff_x = 0;
		diff_y = 0;
		countFalling = 0;
		isFall = false;
	}
	if ((this->pointMario.isEmpty(0,1)) && (!isJump))// in falling
	{
		diff_x = 0;
		diff_y = 1;
		countFalling++;
		isFall = true;
		isclimb = false;//if he was while climbing
	}

	// If Mario has fallen too far, he death when he meet floor
	if (countFalling >= (int)eKeys::MARIO_MAX_FALLING && this->pointMario.isFloor(0, 1))
	{
		marioDead();// Reset Mario's position and life
	}


	//if mario out of bounds and need to died
	if (pointMario.noFloorInMap())
	{
		marioDead();
	}



	// Move Mario to the new position
	this->pointMario.move(diff_x, diff_y, this->pointMario.currPosFromOriginalBoard(0, 0));
	

}

//Checks if Mario Collides with a Barrel and Resets His State Upon Collision
bool Mario::meetBarrel() 
{
	if (this->pointMario.isBarrel())
	{
		if (TryKill)
		{
			return false;
		}
		else {
			marioDead();
			return true;
		}
	}
	else {
		return false;
	}
	
}

//Checks if Mario Collides with a Ghost and Resets His State Upon Collision
bool Mario::meetGhost()
{
	if (this->pointMario.isGhost())
	{
		if (TryKill)
		{
			return false;
		}
		else {
			marioDead();
			return true;
		}
	}
	else {
		return false;
	}

}

//"Checks if Mario Has Reached Pauline's Position"
bool Mario::ifMarioMeetPauline() const
{
	if (this->pointMario.isPauline(0,0))
	{
		return true;
	}
	return false;
}

//reset mario and minus 1 to his life
void Mario::marioDead()
{
	life = life - 1;
	resetMario();
}







