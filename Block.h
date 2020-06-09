#pragma once 
#include"Tetris.h"

class Block {//方块类的基类
public:
	Tetris temp;//用于调用设置颜色的函数
	int Turn(int num);//旋转函数  
	void Draw(int x, int y, int num);//画方块
	void ReDraw(int x, int y, int num);//擦除方块
	virtual void readKey() = 0;//键盘读取
	virtual bool Judge(int x, int y, int num) = 0;//判断函数玩家一 
	virtual void Down() = 0;//下落函数
	virtual void Random() = 0;//随机生成方块函数 
	virtual int ClearLine(int p1, int p2, int idw) = 0; //消除行
	virtual void addline() = 0;//增加垃圾行
	friend class Tetris;
	friend class Game;
};