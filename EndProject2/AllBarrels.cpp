#include "AllBarrels.h"
#include "point.h"
#include "board.h"
#include"barrel.h"
#include "mario.h"

// Constructor: Initializes the AllBarrels object with the provided board reference and Mario's position.
AllBarrels::AllBarrels(Board& board, const Mario& mario1):board(board) ,mario(mario1)
{
};

// Retrieves a reference to a barrel at the specified index in the barrel array (no bounds checking).
  Barrel& AllBarrels::getBarrel(int pos) 
{
	  return *allBarrels[pos];
}

  // Resets all barrels in the barrel array by calling their resetBarrel() method.
  void AllBarrels::resetBarrels()
  {
	  int sizeAllBarrels = allBarrels.size();
	  for (int i = 0; i < sizeAllBarrels; ++i) {
		  delete allBarrels[i];
	  }
	  allBarrels.clear();
  }

  //dtor all barrels
  AllBarrels::~AllBarrels()
  {
	  int sizeAllBarrels = allBarrels.size();
	  for (int i = 0; i < sizeAllBarrels; ++i) {
		  delete allBarrels[i];
	  }
	  allBarrels.clear();
  }

  //"born" new barrel in the vector
  void AllBarrels::bornNewBarrel()
  {
	  Barrel* tempBarrel = new Barrel(board,mario.getPoint());
	  allBarrels.push_back(tempBarrel);
  }

  //erase one barrel from the vector
  void AllBarrels::eraseBarrelIFromVec(int i)
  {
	  int x = allBarrels[i]->getBarrelPoint().getX();
	  int y = allBarrels[i]->getBarrelPoint().getY();
	  allBarrels[i]->getBarrelPoint().draw(board.getCharOriginalBoard(x, y));
	  delete[] allBarrels[i];
	  allBarrels.erase(allBarrels.begin() + i);
	  board.setCurrentBoard(x,y,board.getCharOriginalBoard(x,y));
  }

 


