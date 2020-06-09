#pragma once 
class Tetris
{
private:
	int point[2];			//两基点
	int top;					//最高点高度
public:
	Tetris();
	void Welocme();			//首界面
	void DrawMap();			//游戏界面
	void SetColor(int);		//控制颜色		
	void Updata(int p1, int p2, int idw, int play);				// 更新界面
	void Pause();				//游戏暂停
	friend class Mino1;
	friend class Mino2;
	friend class Game;
};