#ifndef __allBarrels_H
#define __allBarrels_H
#include "barrel.h"
#include <vector>

using  std::vector;

	class point;
	class board;

class AllBarrels
{
	vector<Barrel*> allBarrels;
	Board& board;
	const Mario &mario;
	
	

public:

	// Constructor: Initializes the AllBarrels object with the provided board reference and Mario's position.
	AllBarrels(Board& board, const Mario& mario1);


	// Retrieves a reference to a barrel at the specified index in the barrel array (no bounds checking).
	Barrel& getBarrel(int pos);

	// Resets all barrels in the barrel array by calling their resetBarrel() method.
	void resetBarrels();

	//dtor allBarrels
	~AllBarrels();

	// block copy ctor and assignment
	AllBarrels(const AllBarrels& other) = delete;
	AllBarrels& operator=(const AllBarrels& other) = delete;

	//erase one barrel from the vector
	void eraseBarrelIFromVec(int i);

	//"born" new barrel in the vector
	void bornNewBarrel();

	//get how mant barrel we have now
	const int getSize() const
	{
		return allBarrels.size();
	}
	




};






#endif

