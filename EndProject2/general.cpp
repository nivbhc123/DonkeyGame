#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream> // for cout
using namespace std;

// Taken from Keren's practice
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


// Taken from Keren's practice
void clrscr()
{
	system("cls");
}