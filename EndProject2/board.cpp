#include <cstring>
#include <iostream>
#include "board.h"
#include "general.h"
#include "point.h"
#include <Windows.h> // for Sleep and colors
#include <cstring>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <vector>

using namespace std;

void Board::printScore(int score) const
{
	gotoxy(Lx, Ly+1);
	cout << "Mario's Score: : "<<score;
}

//"Display Player's Life Count Using Asterisks"
void Board::printLife(int life) const
{
	gotoxy(Lx, Ly);
	cout << "Mario's Life : ";
	for (int i = 0; i < life; i++)
	{
		cout << "*";
	}
	
}

//"Reset the Game Board to its Original State and Refresh the Display"
void Board::reset(int life,int score) {
	system("cls");
	for (int i = 0; i < GAME_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], GAME_WIDTH + 1);
	}
	if (!isSilent)
	{
		print(life, score);
	}
}

//"Print the Current Game Board and Display Player's Life"
void Board::print(int life,int score) const {

	for (int i = 0; i < GAME_HEIGHT - 1; i++) {
		cout << currentBoard[i] << '\n';
	}
	cout << currentBoard[GAME_HEIGHT - 1];
	printLife(life);
	printScore(score);
}


void Board::getAllBoardFileNames() {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0,6) == "dkong_" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
	std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

//load file and return true when it is a good file
bool Board::load(const string& filename) {
	std::ifstream screen_file(filename);
	int curr_row = 0;
	int curr_col = 0;
	char c;
	bool wasM = false;
	bool wasHammer = false;
	bool wasPauline=false;
	bool wasD = false;
	bool wasL = false;
	bool eror = false;
	if (!screen_file.is_open()) {
		cout << "Failed to open file: " << filename << std::endl;
		eror = true;
	}
	else {
		regularGhostStartPoint.clear();
		climbGhostStartPoint.clear();

		while (!screen_file.get(c).eof() && curr_row < GAME_HEIGHT) {
			if (c == '\n') {
				if (curr_col < GAME_WIDTH)
				{
					// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
					strcpy(originalBoard[curr_row] + curr_col, std::string(GAME_WIDTH - curr_col, ' ').c_str());
				}
				++curr_row;
				curr_col = 0;
				continue;
			}
			if (curr_col < GAME_WIDTH) {
				if (c == (char)Board::gameObjectKeys::MARIO)
				{
					if (!wasM)
					{
						MarioXStartPos = curr_col;
						MarioYStartPos = curr_row;
						wasM = true;
					}
					originalBoard[curr_row][curr_col++] = ' ';
				}
				else if (c == (char)Board::gameObjectKeys::MENU)
				{
					if (!wasL)
					{
						Lx = curr_col;
						Ly = curr_row;
						wasL = true;
					}
					originalBoard[curr_row][curr_col++] = ' ';
				}
				else if (c == (char)Board::gameObjectKeys::REGULAR_GHOST)
				{
					regularGhostStartPoint.emplace_back(curr_col, curr_row);
					originalBoard[curr_row][curr_col++] = ' ';
				}
				else if (c == (char)Board::gameObjectKeys::CLIMB_GHOST)
				{
					climbGhostStartPoint.emplace_back(curr_col, curr_row);
					originalBoard[curr_row][curr_col++] = ' ';
				}
				else if (c == (char)Board::gameObjectKeys::DONKEY_KONG)
				{
					if (!wasD)
					{
						DonkeyXStartPos = curr_col;
						DonkeyYStartPos = curr_row;
						originalBoard[curr_row][curr_col++] = c;
						wasD = true;
					}
					else {
						originalBoard[curr_row][curr_col++] = ' ';
					}
				}
				else if (c == (char)Board::gameObjectKeys::PAULINE)
				{
					if (!wasPauline)
					{
						originalBoard[curr_row][curr_col++] = c;
						wasPauline = true;
					}
					else {
						originalBoard[curr_row][curr_col++] = ' ';
					}
				}
				else if (c == (char)Board::gameObjectKeys::HAMMER)
				{
					if (!wasHammer)
					{
						hammerXStartPos = curr_col;
						hammerYStartPos = curr_row;
						originalBoard[curr_row][curr_col++] = c;
						wasHammer = true;
					}
					else {
						originalBoard[curr_row][curr_col++] = ' ';
					}
				}
				else {
					originalBoard[curr_row][curr_col++] = c;
				}
			}
		}

		while (curr_col < GAME_WIDTH)
		{
			originalBoard[curr_row][curr_col++] = ' ';
		}

		curr_row++;
		while (curr_row < GAME_HEIGHT)
		{
			curr_col = 0;
			while (curr_col < GAME_WIDTH)
			{
				originalBoard[curr_row][curr_col++] = ' ';
			}
			curr_row++;
		}
 
		if (wasD && wasL && wasM && wasPauline && isAllGhostsOnFloor())
		{
			eror = false;
		}
		else {
			eror = true;
		}
	}
	return !eror;
}

//check if the char is floor key
bool Board::isFloor(char tav) const
{
	return ((tav == (char)floorKeys::LEFT) || (tav == (char)floorKeys::RIGHT) || (tav == (char)floorKeys::SAME));
}


//get specific file name
string Board::getNameFileI(int num) 
{
	return vec_to_fill[num];
}



//Check if all of the ghosts are on floor
bool Board::isRegGhostsOnFloor() const
{
	for (const auto& Pghost : regularGhostStartPoint)
	{
		if (Pghost.second + 1 == GAME_HEIGHT)
		{
			return false;
		}
		if (!isFloor(originalBoard[Pghost.second+1][Pghost.first]))
		{
			return false;
		}
	}
	return true;
}
bool Board::isClimbGhostsOnFloor() const
{
	for (const auto& Pghost : climbGhostStartPoint)
	{
		if (Pghost.second + 1 == GAME_HEIGHT)
		{
			return false;
		}
		if (!isFloor(originalBoard[Pghost.second + 1][Pghost.first]))
		{
			return false;
		}
	}
	return true;
}
bool Board::isAllGhostsOnFloor() const
{
	if(!isRegGhostsOnFloor())
	{
		return false;
	}
	if (!isClimbGhostsOnFloor())
	{
		return false;
	}
	return true;
}








