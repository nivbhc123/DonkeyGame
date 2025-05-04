#ifndef __barrel_H
#define __barrel_H
#include "enemy.h"


class Mario;

class Barrel :public Enemy
{
	
	
	const Point& marioPoint;

	//barrel start position
	int xStartPoseBarrel ;
	int yStartPoseBarrel ;

	//barrel's sign
	static constexpr char sign = 'O';

	//barrel's starting dir
	int diff_x = 0;
	int diff_y = 0;


	//count the falling of barrel
	int countFallLines;

	//remember the last diff x of the barrel
	int rememberDiffX=1;



 public:
	 enum class eKeys { BARREL_MAX_FALLING =8};

	 // ctor: Initialize Barrel Object and Set Initial Position on the Board
	 Barrel(Board& board, const Point& marioPoint);

	 //"Move Barrel Based on Game Logic"
	 bool move(bool &isMarioDead);

	 //get barrel point
	const Point getBarrelPoint() const
	 {
		 return enemyPoint;
	 }
		
	
};

#endif
