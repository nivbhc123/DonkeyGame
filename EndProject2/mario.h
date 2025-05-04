
#ifndef __mario_H
#define __mario_H
#include "point.h"

class Board;

class Mario
{
	int xStartPoseMario;
	int yStartPoseMario;
	static constexpr char sign = '@';
	Board &Mboard;
	Point pointMario;

	//the dir move of mario
	int diff_x;
	int diff_y;

	//count mario's life
	int life;

	// if mario is while jumping
	bool isJump;

	//if mario is while falling from jumping
	bool isFallingFromJump = false;

	//count the "level" in the jump
	int countJump;

	//if mario is while falling 
	bool isFall;

	//if mario is while climbing 
	bool isclimb;

	//count how many lines mario fall
	int countFalling ;
	
	//if mario has the hammer
	bool hasHammer;

	//if mario press p and try to kill
	bool TryKill;




public:
	enum class eKeys { LEFT = 'A', left = 'a', RIGHT = 'D', right = 'd', UP = 'W', up = 'w', DOWN = 'X', down = 'x',KILL='P',kill='p', STAY = 'S', stay = 's', ESC = 27, MARIO_MAX_FALLING = 5 };
	
	//Constructor for Initializing Mario's State and Position on the Board
	Mario(Board& board);//ctor

	// return Mario's life
	int getMarioLife() const;

	//Handles Mario's Movement and Actions Based on Player Input and Game State
	void move(eKeys key);

	//Checks if Mario Collides with a Barrel and Resets His State Upon Collision
	bool meetBarrel() ;

	// return Mario's point
	const Point &getPoint() const;

	//Initializing Mario's State, Position on the Board, and Reducing His Life by One
	 void resetMario();

	 //"Checks if Mario Has Reached Pauline's Position"
	 bool ifMarioMeetPauline() const;

	 //kill mario
	 void marioDead();

	 //check if mario meet ghost
	 bool meetGhost();

	 //return if mario pressed p
	 bool isMarioWantKill() const
	 {
		 
		 return TryKill;
	 }

	 //get mario dirr
	 int getMarioDiffX() const
	 {
		 return diff_x;
	 }

	 //mario pressed p while he change dirr
	 void setTryToKill()
	 {
		 if ((hasHammer) && (diff_x!=0)){
			 TryKill = true;
		 }
	 }
};

#endif