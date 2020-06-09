#include"head.h"
#include "Block.h"
#include "Game.h"
#include "Mino1.h"
#include "Mino2.h"
#include "Tetris.h"

using namespace std;


int main()
{
	Tetris a;
	Game c;
	a.Welocme();
	system("cls");				//清除欢迎界面
	a.DrawMap();
	c.Run();
	return 0;
}