#pragma once 
#include"Block.h"
#include"Mino1.h"

class Mino2 :public Block {
private:
	int id2; //玩家二图形ID
	int next_id2; //玩家二下一块图形ID
	int point[2]; //两个基点
	int i;//用于下落函数中计算时间
public:
	Tetris player2;
	Mino2();
	void Random();
	void readKey();//键盘读取
	bool Judge(int x, int y, int num);//判断函数玩家二 
	void Down();//下落函数
	int ClearLine(int p1, int p2, int idw); //消除行
	void addline();//增加垃圾行
	friend class Tetris;
	friend class Game;
};
