#include "allGhosts.h"
#include "mario.h"




// Constructor for AllGhosts class:
// Initializes the collection of ghost objects based on their starting positions on the board.
AllGhosts::AllGhosts(Board& board, const Mario& mario1) : allGhostsBoard(board), mario(mario1)
{
	const vector<pair<int, int>>& ghostRegStartPoint = board.getRegGhostStartPoints();

	for (const auto& point : ghostRegStartPoint)
	{
		Ghost* temp = new Ghost(board, point.first, point.second, (char) Board::gameObjectKeys::REGULAR_GHOST);
		allGhosts.push_back(temp);
	}

	const vector<pair<int, int>>& ghostClimbStartPoint = board.getClimbGhostStartPoints();

	for (const auto& point : ghostClimbStartPoint)
	{
		Ghost* temp = new ClimbGhost(board, point.first, point.second, (char)Board::gameObjectKeys::CLIMB_GHOST);
		allGhosts.push_back(temp);
	}

}

// Destructor for AllGhosts class:
// Frees the memory allocated for each ghost object to prevent memory leaks.
AllGhosts::~AllGhosts() {
	for (int i = 0; i < allGhosts.size(); i++)
	{
		delete[] allGhosts[i];
	}
}


// Move function to update the positions of all ghosts and handle interactions with Mario.
void AllGhosts::move()
{

	for (int i=0;i<allGhosts.size();i++)
	{
		//check if mario is near ghost
		if (((allGhosts[i]->getPoint().getX() - mario.getMarioDiffX() == mario.getPoint().getX()) && (allGhosts[i]->getPoint().getY() == mario.getPoint().getY())) || ((allGhosts[i]->getPoint().getX()== mario.getPoint().getX())&&(allGhosts[i]->getPoint().getY() == mario.getPoint().getY())))
		{
			//if mario want kill
			if (mario.isMarioWantKill())
			{
				int x = allGhosts[i]->getPoint().getX();
				int y = allGhosts[i]->getPoint().getY();
				allGhosts[i]->getPoint().draw(allGhostsBoard.getCharOriginalBoard(x, y));
				delete allGhosts[i];
				allGhosts.erase(allGhosts.begin() + i);
				this->allGhostsBoard.setCurrentBoard(x,y,allGhostsBoard.getCharOriginalBoard(x,y));
				i--;
			}
		}
		else {
			allGhosts[i]->calculateNextMove();
		}
	}

	for (int i = 0; i < allGhosts.size(); i++)
	{
		allGhosts[i]->move();
	}
}

// Reset function for all ghosts:
void AllGhosts::resetAllGhosts()
{
	for (int i = 0; i < allGhosts.size(); i++)
	{
     	delete [] allGhosts[i];
	}

	allGhosts.clear();

	const vector<pair<int, int>>& ghostRegStartPoint = allGhostsBoard.getRegGhostStartPoints();

	for (const auto& point : ghostRegStartPoint)
	{
		Ghost* temp = new Ghost(allGhostsBoard, point.first, point.second, (char)Board::gameObjectKeys::REGULAR_GHOST);
		allGhosts.push_back(temp);
	}

	const vector<pair<int, int>>& ghostClimbStartPoint = allGhostsBoard.getClimbGhostStartPoints();

	for (const auto& point : ghostClimbStartPoint)
	{
		Ghost* temp = new ClimbGhost(allGhostsBoard, point.first, point.second, (char)Board::gameObjectKeys::CLIMB_GHOST);
		allGhosts.push_back(temp);
	}

}