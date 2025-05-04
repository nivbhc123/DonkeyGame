#ifndef __ENEMY_H
#define __ENEMY_H
#include "point.h"
#include "board.h"


class Enemy
{
protected:

	Board& Eboard;
	Point enemyPoint;

public:

	//ctor of Enemy
	Enemy(Board& board,char sign,int x,int y);

};

#endif

