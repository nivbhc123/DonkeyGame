#ifndef __ClimbGhost_H
#define __ClimbGhost_H
#include "ghost.h"
class ClimbGhost : public Ghost
{
	//bool if the climb ghost is in climb
	bool isClimbing = false;

public:
	using Ghost::Ghost;

	//the climb ghost is climbing
	void climb() override;

};

#endif

