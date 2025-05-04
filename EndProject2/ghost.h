#ifndef __ghost_H
#define __ghost_H
#include "enemy.h"
#include <random>




class Ghost : public Enemy
{
protected:
	int diff_X = 1;
	int diff_Y = 0;



	//rando, number from 1-100
	std::mt19937 rng;
	std::uniform_int_distribution<int> dist;


	public:

		// Constructor for the Ghost class:
		Ghost(Board& board,int x,int y,char sign);

		virtual ~Ghost() {}

		// Function to execute the movement of the ghost
		void move();

		//virtual function of ghost, the climb ghost will climb
		virtual void climb() {}

		// Function to calculate the next move of the ghost.
		void calculateNextMove();

		//get ghost point
		Point getPoint()
		{
			return enemyPoint;
		}
		

};


#endif

