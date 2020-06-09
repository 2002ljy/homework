#include"head.h"
#include "other.h"
#include"Tetris.h"
using namespace std;

Tetris::Tetris()				//构造函数， 初始化各个值
{
	point[0] = 0;
	point[1] = 5;
	top = 20;
}
void Tetris::Pause()				// 暂停函数
{
	SetPos(31, 10);
	cout << "游戏暂停!" << endl;
	char temp;
	while (1)
	{
		while (1)
		{
			if (_kbhit())
			{
				temp = _getch();
				break;
			}
		}
		if (temp == 32)
			break;
	}
	SetPos(32, 10);					// 清除暂停时显示的信息
	cout << "         ";
	SetPos(30, 11);
	cout << "              ";
}

void Tetris::Updata(int p1, int p2, int idw, int play)					//更新函数
{
	int i, idt = idw;
	int nx, ny;
	for (i = 0; i < 4; i++)//画上最后一次的方块
	{
		nx = p1 + sharp[idt][i * 2];
		ny = p2 + sharp[idt][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		SetColor(0);
		cout << "■";
		if (play == 1)//玩家一
			map1[nx][ny] = 1;					//界面各个点是否为空的更新
		if (play == 2)//玩家二
			map2[nx][ny] = 1;
	}

	if (p1 < top)
		top = p1;					//最高点的更新

}

void Tetris::Welocme()			//欢迎界面
{
	SetColor(1);
	char x;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "           我  罗  斯  方  块		" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "       疫  情  宅  家  无  事  做		" << endl;
		cout << "       来  玩  我  罗  斯  方  块		" << endl;
		cout << "            双  人  运  动		    " << endl;
		cout << "            激  情  对  战		    " << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "	Press any key to continue " << endl;
		SetPos(20, 10);
		x = getchar();
		break;

	}
}

void Tetris::SetColor(int color_num)			//设置颜色
{
	int n;
	switch (color_num)
	{
	case 0: n = 0x08; break;
	case 1: n = 0x0C; break;
	case 2: n = 0x0D; break;
	case 3: n = 0x0E; break;
	case 4: n = 0x0A; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}

void Tetris::DrawMap()				//画游戏时界面
{
	int i;
	SetColor(0);

	for (i = 0; i < 22; i++)		//宽10格
	{
		SetPos(i * 2, 0);
		cout << "■";
		SetPos(i * 2, 22);
		cout << "■";
	}

	for (i = 0; i < 22; i++)		//高20格
	{
		SetPos(0, i);
		cout << "■";
		SetPos(22, i);
		cout << "■";
		SetPos(42, i);
		cout << "■";
	}
	SetPos(25, 19);
	SetColor(4);
	cout << "左移";
	SetPos(29, 19);
	SetColor(4);
	cout << "A";


	SetPos(32, 19);
	SetColor(4);
	cout << "S";
	SetPos(30, 20);
	SetColor(4);
	cout << "加 速";

	SetPos(35, 19);
	SetColor(4);
	cout << "D";
	SetPos(36, 19);
	SetColor(4);
	cout << "右移";

	SetPos(32, 17);
	SetColor(4);
	cout << "W";
	SetPos(30, 16);
	SetColor(4);
	cout << "翻 转";
	SetColor(0);
	for (i = 0; i < 22; i++)		//宽10格
	{
		SetPos(i * 2 + 62, 0);
		cout << "■";
		SetPos(i * 2 + 62, 22);
		cout << "■";
	}

	for (i = 0; i < 22; i++)		//高20格
	{
		SetPos(0 + 62, i);
		cout << "■";
		SetPos(22 + 62, i);
		cout << "■";
		SetPos(42 + 62, i);
		cout << "■";
	}

	SetPos(25 + 62, 19);
	SetColor(4);
	cout << "左移";
	SetPos(29 + 62, 19);
	SetColor(4);
	cout << "←";


	SetPos(32 + 62, 19);
	SetColor(4);
	cout << "↓";
	SetPos(30 + 62, 20);
	SetColor(4);
	cout << "加 速";

	SetPos(35 + 62, 19);
	SetColor(4);
	cout << "→";
	SetPos(36 + 62, 19);
	SetColor(4);
	cout << "右移";

	SetPos(32 + 62, 17);
	SetColor(4);
	cout << "↑";
	SetPos(30 + 62, 16);
	SetColor(4);
	cout << "翻 转";


	SetColor(3);
	SetPos(28, 2);
	cout << "下一图形";
	SetPos(28 + 62, 2);
	cout << "下一图形";
}