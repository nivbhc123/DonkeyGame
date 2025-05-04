#include "enemy.h"

//ctor of Enemy
Enemy::Enemy(Board& board, char sign, int x, int y):Eboard(board),enemyPoint(sign,x,y,Eboard){}