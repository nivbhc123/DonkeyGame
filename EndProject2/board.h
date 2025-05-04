#ifndef __board_H
#define __board_H

#include <vector>
#include <string>
#include <utility> //for pair

using  std::pair;
using  std::vector;
using  std::string;

class Board
{
public:
	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 25;
	enum class floorKeys { LEFT='<', RIGHT='>',SAME='=',EMPTY =' '};
	enum class gameObjectKeys {BARREL='O',MARIO='@',PAULINE='$',DONKEY_KONG='&',BORDER='Q',LADDER='H',BIG_HAMMER='P', HAMMER = 'p', REGULAR_GHOST = 'x',CLIMB_GHOST='X', MENU = 'L' };
private:
	char originalBoard[GAME_HEIGHT][GAME_WIDTH + 1];
	char currentBoard[GAME_HEIGHT][GAME_WIDTH + 1]; // +1 for null terminator

	vector<pair<int,int>> regularGhostStartPoint;
	vector<pair<int, int>> climbGhostStartPoint;

	int MarioXStartPos;
	int MarioYStartPos;
	int DonkeyXStartPos;
	int DonkeyYStartPos;
	int Lx;
	int Ly;
	int hammerXStartPos;
	int hammerYStartPos;



	vector<string>vec_to_fill;

	//"Display Player's Life Count Using Asterisks"
	void printLife(int life) const;

	void printScore(int score) const ;

	//"Print the Current Game Board and Display Player's Life"
	void print(int life,int score) const;

	//Check if all of the ghosts are on floor
	bool isAllGhostsOnFloor() const;
	bool isRegGhostsOnFloor() const;
	bool isClimbGhostsOnFloor() const;

	bool isSilent = false; 


public:

	Board() {
		getAllBoardFileNames();
	}

	//"Reset the Game Board to its Original State and Refresh the Display"
	void reset(int life,int score) ;

	//get char from the current board
	char getCharCurrBoard(int x, int y) const {
		return currentBoard[y][x];
	}

	//get char from the original board
	char getCharOriginalBoard(int x, int y) const {
		return originalBoard[y][x];
	}

	//set char in current board
	void setCurrentBoard(int x, int y, char sign)
	{
		currentBoard[y][x] = sign;
	}

	//set char in current board
	void setOriginalBoard(int x, int y, char sign)
	{
		originalBoard[y][x] = sign;
	}

	
	void getAllBoardFileNames();
	
	//load file and return true when it is a good file
	bool load(const std::string& filename);

	//get specific file name
	string getNameFileI(int num);

	//get board data members
	int getMarioXstartPose () const
	{
		return MarioXStartPos;
	}
	int getMarioYstartPose ()const
	{
		return MarioYStartPos;
	}
	int getDonkeyXstartPose () const
	{
		return DonkeyXStartPos;
	}
	int getDonkeyYstartPose () const
	{
		return DonkeyYStartPos;
	}
	int getLx() const
	{
		return Lx;
	}
	int getLy() const
	{
		return Ly;
	}
	int getHammerXstartPose()const
	{
		return hammerXStartPos;
	}
	int getHammerYstartPose()const
	{
		return hammerYStartPos;
	}

	//get the amount of file that the user insert
	int getAmountOfFiles() const
	{
		return vec_to_fill.size();
	}

	//return the regular ghosts points from the board
	const vector<pair<int, int>>& getRegGhostStartPoints() const
	{
		return regularGhostStartPoint;
	}

	//return the climb ghosts points from the board
	const vector<pair<int, int>>& getClimbGhostStartPoints() const
	{
		return climbGhostStartPoint;
	}

	//check if the char is floor key
	bool isFloor(char tav) const;

	//change the board to silent board
	void setSilent()
	{
		isSilent = true;
	}

	//return true if board is silent
	bool ifBoardIsInSilent() const
	{
		return isSilent;
	}
	
};

#endif

