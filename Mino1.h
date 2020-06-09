#pragma once 
#include"Block.h"
#include"Tetris.h"

class Mino1 :public Block {
private:
	int id1; //玩家一图形ID
	int next_id1; //玩家一下一块图形ID
	int point[2]; //两个基点
	int i;//用于下落函数中计算时间
public:
	Tetris player1;
	Mino1();
	void readKey();//键盘读取
	bool Judge(int x, int y, int num);//判断函数玩家一 
	void Down();//下落函数
	void Random();//随机生成方块函数 
	int ClearLine(int p1, int p2, int idw); //消除行
	void addline();//增加垃圾行
	friend class Mino2;
	friend class Tetris;
	friend class Game;
};