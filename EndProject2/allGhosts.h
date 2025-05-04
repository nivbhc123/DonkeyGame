#ifndef __AllGhost_H
#define __AllGhost_H
#include <vector>
#include "ghost.h"
#include "board.h"
#include "climbGhost.h"

using  std::vector;
class Mario;

class AllGhosts
{
	vector<Ghost*> allGhosts ;
	Board& allGhostsBoard;
	const Mario& mario;

 public:
	 // Constructor for AllGhosts class:
	 AllGhosts(Board& board, const Mario& mario1);

	 // Destructor for AllGhosts class:
	 ~AllGhosts(); 

	 // block copy ctor and assignment
	 AllGhosts(const AllGhosts& all_ghosts) = delete;
	 const AllGhosts& operator=(const AllGhosts& all_ghosts)=delete;

	 // Move function to update the positions of all ghosts and handle interactions with Mario.
	 void move();

	 // Reset function for all ghosts:
	 void resetAllGhosts();
};

#endif

