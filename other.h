#pragma once 
#include"head.h"
inline void SetPos(int i, int j)			//控制光标位置， 列， 行
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

inline vector<int> GenerateDiffNumber(int min, int max, int num)//产生不重复的随机数
{
	int rnd;
	vector<int> diff;
	vector<int> tmp;
	for (int i = min; i < max + 1; i++)
	{
		tmp.push_back(i);
	}
	for (int i = 0; i < num; i++)
	{
		do {
			rnd = min + rand() % (max - min + 1);

		} while (tmp.at(rnd - min) == -1);
		diff.push_back(rnd);
		tmp.at(rnd - min) = -1;
	}
	return diff;
}

extern const int sharp[15][8];

extern const int high[15];
extern int map1[100][100];
extern int map2[100][100];