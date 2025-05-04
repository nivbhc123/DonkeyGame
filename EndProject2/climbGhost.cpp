#include "climbGhost.h"

//the climb ghost is climbing
void ClimbGhost::climb() {

	if (enemyPoint.ifLadder(0,0))
	{
		diff_Y = -1;
		diff_X = 0;
		isClimbing = true;
	}
	else if (isClimbing)
	{

		//finish climb
		if (enemyPoint.isFloor(0, 1) || enemyPoint.isEmpty(0,0))
		{
			diff_Y = 0;
			diff_X = 1;//default move
			isClimbing = false;
		}

		//continue climbing
		else {
			diff_Y = -1;
			diff_X = 0;
		}
	}
	

}
