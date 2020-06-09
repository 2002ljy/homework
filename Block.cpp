#include"head.h"
#include "other.h"
#include"Block.h"

const int sharp[15][8] =					//组成图形的各个点的各个坐标，先纵后横
{
{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
{0,0,1,0,0,1,1,1},
{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
};

const int high[15] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3 };//记录每种方块的高度
int map1[100][100] = { 0 };//玩家一的画布
int map2[100][100] = { 0 };//玩家二的画布
#define a1  0			//条形
#define a2  1

#define b 2					// 方块

#define c1 3					//L形
#define c2 4
#define c3 5
#define c4 6

#define d1 7					//T形
#define d2 8 
#define d3 9
#define d4 10

#define e1 11				//闪电1形
#define e2 12

#define f1 13				//闪电2形
#define f2 14
int Block::Turn(int num)
{
	int id = 0;
	switch (num)
	{
	case a1: id = a2; break;					//条形互换
	case a2: id = a1; break;

	case b: id = b; break;					//方块无法旋转

	case c1: id = c2; break;					//各种L形互换
	case c2: id = c3; break;
	case c3: id = c4; break;
	case c4: id = c1; break;

	case d1: id = d2; break;					//各种T形互换
	case d2: id = d3; break;
	case d3: id = d4; break;
	case d4: id = d1; break;

	case e1: id = e2; break;					//两种Z形互换
	case e2: id = e1; break;

	case f1: id = f2; break;
	case f2: id = f1; break;
	}
	return id;
}
void Block::Draw(int x, int y, int num)
{
	int nx, ny;

	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		temp.SetColor(i + 1);
		cout << "■";

	}
}
void Block::ReDraw(int x, int y, int num)//擦除方块
{
	int nx, ny;

	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);//因为一个方块等于两个空格所以要删两个
		cout << " ";
		SetPos((ny + 1) * 2 + 1, nx + 1);
		cout << " ";
	}
}