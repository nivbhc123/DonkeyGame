#include "barrel.h"

// ctor: Initialize Barrel Object and Set Initial Position on the Board
Barrel::Barrel(Board& board, const Point& marioPoint):Enemy(board,sign, xStartPoseBarrel, yStartPoseBarrel), marioPoint(marioPoint)
{
	xStartPoseBarrel= Eboard.getDonkeyXstartPose();
	yStartPoseBarrel= Eboard.getDonkeyYstartPose();
	enemyPoint.setPoint(xStartPoseBarrel, yStartPoseBarrel);
	countFallLines = 0;
	enemyPoint.draw(sign);
	enemyPoint.setPointInCurrentBoard(sign);
}

//"Move Barrel Based on Game Logic"
bool Barrel::move(bool& isMarioDead)
{
	char direction = this->enemyPoint.currPosFromOriginalBoard(0, 1);
	

	switch (Board::floorKeys(direction))
	{
	case Board::floorKeys::LEFT:
		diff_x = -1;
		diff_y = 0;
		rememberDiffX = diff_x;
		break;
	case Board::floorKeys::RIGHT:
		diff_x = 1;
		diff_y = 0;
		rememberDiffX = diff_x;
		break;
	case Board::floorKeys::SAME://continue same
		//diff_x like before
		diff_x = rememberDiffX;
		diff_y = 0;
		break;
	case Board::floorKeys::EMPTY://FALL
		diff_x = 0;
		diff_y = 1;
		countFallLines++;
		break;
	}

	// Check if the barrel has landed on the floor and didnt fall 8 lines or higher before; and stop falling 
	if (this->enemyPoint.isFloor(0, 1) && countFallLines < (int)eKeys::BARREL_MAX_FALLING)
	{
		countFallLines = 0;
	}

	// Check if the barrel reaches the end ('Q') and stop it.
	if (this->enemyPoint.checkBorder(diff_x,diff_y))
	{
		return false;
	}


	// Check if the barrel has fallen too far (over 8 fall lines), it bombs when he meet floor 
	if ((countFallLines >= (int)eKeys::BARREL_MAX_FALLING) && this->enemyPoint.isFloor (0, 1))
	{
		// Check if Mario is within range to trigger a "bomb".
		if (this->enemyPoint.ifPointInRadios2ToAnotherPoint(this->marioPoint))
		{
			isMarioDead = true;
		}
		return false;
	}

	if (this->enemyPoint.noFloorInMap())
	{
		return false;
	}


	// Move the barrel visually on the screen.
	this->enemyPoint.move(diff_x, diff_y, this->enemyPoint.currPosFromOriginalBoard(0, 0));

	// Update the barrel's position on the current board structure.
	this->enemyPoint.moveOnCurrBoard(diff_x, diff_y, this->enemyPoint.currPosFromOriginalBoard(0, 0));

	// Return true to indicate the move was successful.
	return true;
	
}
