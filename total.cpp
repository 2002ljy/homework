#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void SetPos(int i, int j)			//控制光标位置， 列， 行
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
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

#define e1 11				//Z形1
#define e2 12

#define f1 13				//Z形2
#define f2 14

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
	int i, flag, idt = idw;
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

////////////////////////////////////////////////////////////////
class Block {//方块类的基类
public:
	Tetris temp;//用于调用设置颜色的函数
	int Turn(int num);//旋转函数  
	void Draw(int x, int y, int num);//画方块
	void ReDraw(int x, int y, int num);//擦除方块
	vector<int> GenerateDiffNumber(int min, int max, int num);//产生不重复的随机数
	virtual void readKey() = 0;//键盘读取
	virtual bool Judge(int x, int y, int num) = 0;//判断函数玩家一 
	virtual void Down() = 0;//下落函数
	virtual void Random() = 0;//随机生成方块函数 
	virtual int ClearLine(int p1, int p2, int idw) = 0; //消除行
	virtual void addline() = 0;//增加垃圾行
	friend class Tetris;
	friend class Game;
};

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
vector<int> Block::GenerateDiffNumber(int min, int max, int num)//产生不重复的随机数
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
class Mino2 :public Block {
private:
	int id2; //玩家二图形ID
	int next_id2; //玩家二下一块图形ID
	int point[2]; //两个基点
	int i;//用于下落函数中计算时间
public:
	Tetris player2;
	Mino2();
	void readKey();//键盘读取
	bool Judge(int x, int y, int num);//判断函数玩家二 
	void Down();//下落函数
	void Random();//随机生成方块函数 
	int ClearLine(int p1, int p2, int idw); //消除行
	void addline();//增加垃圾行
	friend class Mino2;
	friend class Tetris;
	friend class Game;
};
//全部拆成两份 
Mino1::Mino1()
{
	point[0] = 0;//玩家一 
	point[1] = 4;
	i = 0;
	id1 = 0;
	next_id1 = 0;
}
Mino2::Mino2()
{
	point[0] = 0;//玩家二 
	point[1] = 35;
	i = 0;
	id2 = 0;
	next_id2 = 0;
}
bool Mino1::Judge(int x, int y, int num)				//判定在x, y 所指位置是否可画编号为
{													//num 的图形， 若不可画则反回true
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		if (!(nx < 21 && nx >= 0 && ny < 10 && ny >= 0 && !map1[nx][ny]))//玩家一 ,nx是高度，纵坐标
			return true;
	}
	return false;
}
bool Mino2::Judge(int x, int y, int num)				//判定在x, y 所指位置是否可画编号为
{													//num 的图形， 若不可画则反回true
	int nx, ny;
	for (int i = 0; i < 4; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		if (!(nx < 21 && nx >= 0 && ny < 41 && ny >= 31 && !map2[nx][ny]))//玩家二,nx是高度
			return true;
	}
	return false;
}
void Mino1::Down()//下落函数
{
	int t;
	while (1)
	{

		if (!(i < 75))				//i 与 count 用于控制时间
		{
			i = 0;
			if (Judge(point[0] + 1, point[1], id1))			//玩家一在某一位置不能下落的话
			{
				player1.Updata(point[0], point[1], id1, 1);//画最后一次，以及更新画布
				t = ClearLine(point[0], point[1], id1);//t用于接收是否有消行
				if (t)//如果有消行则使玩家二增行
					addline();
				id1 = next_id1;

				ReDraw(6, 14, next_id1);
				next_id1 = rand() % 15;

				point[0] = 0; point[1] = 4;//更新
				Draw(point[0], point[1], id1);
				Draw(6, 14, next_id1);

				if (Judge(point[0], point[1], id1))//玩家一失败 
				{
					system("cls");
					SetPos(15 + 31, 10);
					cout << "游戏结束！" << endl;
					SetPos(15 + 31, 12);
					cout << "玩家一失败" << endl;
					SetPos(15 + 31, 14);
					system("pause");
					exit(1);
				}
			}
			else					//继续下落
			{
				ReDraw(point[0], point[1], id1);//玩家一
				point[0]++;
				Draw(point[0], point[1], id1);
			}
		}
		readKey();//调用键盘读取 
		Sleep(1);
		i++;				//控制下落间隔
		break;
	}
}
void Mino2::Down()//下落函数
{
	int t = 0;
	while (1)
	{

		if (!(i < 75))				//i 与 count 用于控制时间
		{
			i = 0;
			if (Judge(point[0] + 1, point[1], id2))			//玩家二在某一位置不能下落的话
			{
				player2.Updata(point[0], point[1], id2, 2);//画最后一次，以及更新画布
				t = ClearLine(point[0], point[1], id2);//t用于接收是否有消行
				if (t)//如果有消行则使玩家一增行
					addline();
				id2 = next_id2;

				ReDraw(6, 45, next_id2);
				next_id2 = rand() % 15;

				point[0] = 0; point[1] = 35;//更新
				Draw(point[0], point[1], id2);
				Draw(6, 45, next_id2);

				if (Judge(point[0], point[1], id2))//玩家二失败 
				{
					system("cls");
					SetPos(15 + 31, 10);
					cout << "游戏结束！" << endl;
					SetPos(15 + 31, 12);
					cout << "玩家二失败" << endl;
					SetPos(15 + 31, 14);
					system("pause");
					exit(1);
				}
			}
			else					//继续下落
			{
				ReDraw(point[0], point[1], id2);//玩家二 
				point[0]++;
				Draw(point[0], point[1], id2);
			}
		}
		readKey();//调用键盘读取 
		Sleep(1);
		i++;				//控制下落间隔
		break;
	}
}
void Mino1::Random()
{
	srand((int)time(0));

	id1 = rand() % 15;//玩家一 
	next_id1 = rand() % 15;
	Draw(point[0], point[1], id1);//玩家一 
	Draw(6, 14, next_id1);
}
void Mino2::Random()
{
	srand((int)time(0));

	id2 = rand() % 15;//玩家二 
	next_id2 = rand() % 15;
	Draw(point[0], point[1], id2);//玩家二 
	Draw(6, 45, next_id2);
}
void Mino1::readKey()
{
	if (_kbhit())				//键盘输入值时 
	{
		int key, key2;
		key = _getch();
		//要设置两个point记录两个选手的point对应操作 
		//wsad方向键 ，要切换成英文输入法才能不用按回车
		if (key == 'w')			//按向上方向键时
		{
			int temp = id1;
			id1 = Turn(id1);
			if (Judge(point[0], point[1], id1))
				id1 = temp;
			ReDraw(point[0], point[1], temp);
			Draw(point[0], point[1], id1);
		}
		if (key == 's')				//按向下方向键时
		{
			if (!Judge(point[0] + 2, point[1], id1))
			{
				ReDraw(point[0], point[1], id1);
				point[0] += 2;
				Draw(point[0], point[1], id1);
			}
		}
		if (key == 'a')				//按向左方向键时
		{
			if (!Judge(point[0], point[1] - 1, id1))
			{
				ReDraw(point[0], point[1], id1);
				point[1]--;
				Draw(point[0], point[1], id1);
			}
		}
		if (key == 'd')					//按向右方向键时
		{
			if (!Judge(point[0], point[1] + 1, id1))
			{
				ReDraw(point[0], point[1], id1);
				point[1]++;
				Draw(point[0], point[1], id1);
			}
		}
		if (key == 32)					// 按下空格暂停
			player1.Pause();
	}
}
void Mino2::readKey()
{
	if (_kbhit())				//键盘输入值时 
	{

		int key, key2;
		key = _getch();
		if (key == 224) //如果是↑↓←→ 
		{
			key2 = _getch();

			if (key2 == 72)			//按向上方向键时
			{
				int temp = id2;
				id2 = Turn(id2);
				if (Judge(point[0], point[1], id2))
					id2 = temp;
				ReDraw(point[0], point[1], temp);
				Draw(point[0], point[1], id2);
			}
			if (key2 == 80)				//按向下方向键时
			{
				if (!Judge(point[0] + 2, point[1], id2))
				{
					ReDraw(point[0], point[1], id2);
					point[0] += 2;
					Draw(point[0], point[1], id2);
				}
			}
			if (key2 == 75)				//按向左方向键时
			{
				if (!Judge(point[0], point[1] - 1, id2))
				{
					ReDraw(point[0], point[1], id2);
					point[1]--;
					Draw(point[0], point[1], id2);
				}
			}
			if (key2 == 77)					//按向右方向键时
			{
				if (!Judge(point[0], point[1] + 1, id2))
				{
					ReDraw(point[0], point[1], id2);
					point[1]++;
					Draw(point[0], point[1], id2);
				}
			}
		}
		if (key == 32)					// 按下空格暂停
			player2.Pause();

	}
}
////////////////////////////////////////////////////////////////////
int Mino1::ClearLine(int p1, int p2, int idw) //消除行
{
	int flag = 1, t = 0;
	int l, m, k, p;
	if (p1 < player1.top)
		player1.top = p1;					//最高点的更新

	for (;;)
	{
		for (i = p1; i < p1 + high[idw]; i++)			//消除行
		{
			flag = 1;
			for (int j = 0; j < 10; j++)					//判定某一行是否满， 用flag来标记
				if (map1[i][j] == 0)
					flag = 0;
			if (flag == 1)//如果该行满了
			{
				t = 1;
				for (k = i; k >= player1.top; k--)//将整体画布坐标下移
				{
					for (p = 0; p < 10; p++)
					{
						map1[k][p] = map1[k - 1][p];
					}
				}
			}
			if (flag == 1)
			{
				for (k = i; k >= player1.top; k--)//将全部方块都清空
				{
					for (l = 0; l < 10; l++)
					{
						SetPos((l + 1) * 2, k + 1);
						cout << " ";
						SetPos((l + 1) * 2 + 1, k + 1);
						cout << " ";
					}
				}
			}

			for (k = i; k >= player1.top; k--)//重新根据画布画图形
			{
				for (p = 0; p < 10; p++)
				{

					if (map1[k][p] == 1)
					{
						SetPos((p + 1) * 2, k + 1);
						player1.SetColor(0);
						cout << "■";
					}

					else
					{
						SetPos((p + 1) * 2, k + 1);//因为一个方块等于两个空格所以要删两个
						cout << " ";
						SetPos((p + 1) * 2 + 1, k + 1);
						cout << " ";
					}
				}
			}

		}
		if (flag == 0)//如果不满行了，就退出
			break;
	}
	return t;
}
int Mino2::ClearLine(int p1, int p2, int idw) //消除行
{
	int flag, t = 0;
	int l, m, k, p;
	if (p1 < player2.top)
		player2.top = p1;					//最高点的更新
for (;;)
		{
	for (i = p1; i < p1 + high[idw]; i++)			//消除行
	{
		flag = 1;
		
			for (int j = 31; j < 41; j++)					//判定某一行是否满， 用flag来标记
				if (map2[i][j] == 0)
					flag = 0;
			if (flag == 1)//如果该行满了
			{
				t = 1;
				for (k = i; k >= player2.top; k--)//将整体画布坐标下移
				{
					for (p = 31; p < 41; p++)
					{
						map2[k][p] = map2[k - 1][p];
					}
				}
			}
			if (flag == 1)
			{
				for (k = i; k >= player2.top; k--)//清空所有方块
				{
					for (l = 31; l < 41; l++)
					{
						SetPos((l + 1) * 2, k + 1);
						cout << " ";
						SetPos((l + 1) * 2 + 1, k + 1);
						cout << " ";
					}
				}
			}

			for (k = i; k >= player2.top; k--)//重新根据画布画图形
			{
				for (p = 31; p < 41; p++)
				{

					if (map2[k][p] == 1)
					{
						SetPos((p + 1) * 2, k + 1);
						player2.SetColor(0);
						cout << "■";
					}

					else//因为一个方块等于两个空格所以要删两个
					{
						SetPos((p + 1) * 2, k + 1);
						cout << " ";
						SetPos((p + 1) * 2 + 1, k + 1);
						cout << " ";
					}
				}
			}
			
		}
		if (flag == 0)//如果不满行了，就退出
				break;

	}
	return t;
}
void Mino2::addline()//生成垃圾行
{
	Tetris temp;
	int k, p, l;
	for (k = 1; k <= 20; k++)//将整体画布坐标上移
	{
		for (p = 1; p < 10; p++)
		{
			map1[k - 1][p] = map1[k][p];
		}
	}

	for (k = 0; k <= 20; k++)//将全部方块都清空
	{
		for (l = 0; l < 10; l++)
		{
			SetPos((l + 1) * 2, k + 1);
			cout << " ";
			SetPos((l + 1) * 2 + 1, k + 1);
			cout << " ";
		}
	}
	srand((unsigned)time(NULL));   //根据不同时间生成不同的种子
	int x = (rand() % (9)) + 2;//随机产生生成行的方块数
	vector<int> diff = GenerateDiffNumber(1, 9, x);//随机获取生成方块的位置
	for (int j = 0; j < 10; j++)
		map1[20][j] = 0;
	for (int i = 0; i < x; i++)
		map1[20][diff[i]] = 1;
	for (k = 0; k <= 20; k++)//重新根据画布画图形
	{
		for (p = 0; p < 10; p++)
		{

			if (map1[k][p] == 1)
			{
				SetPos((p + 1) * 2, k + 1);
				temp.SetColor(0);
				cout << "■";
			}
		}
	}

}
void Mino1::addline()
{
	int k, p, l;
	Tetris temp;
	for (k = 0; k <= 20; k++)//将整体画布坐标上移
	{
		for (p = 31; p < 41; p++)
		{
			map2[k - 1][p] = map2[k][p];
		}
	}

	for (k = 0; k <= 20; k++)//将全部方块都清空
	{
		for (l = 31; l < 41; l++)
		{
			SetPos((l + 1) * 2, k + 1);
			cout << " ";
			SetPos((l + 1) * 2 + 1, k + 1);
			cout << " ";
		}
	}
	srand((unsigned)time(NULL));   //根据不同时间生成不同的种子
	int x = (rand() % (9)) + 1;//随机产生生成行的方块数
	vector<int> diff = GenerateDiffNumber(32, 40, x);//随机获取生成方块的位置
	for (int j = 31; j < 41; j++)
		map2[20][j] = 0;
	for (int i = 0; i < x; i++)
		map2[20][diff[i]] = 1;
	for (k = 0; k <= 20; k++)//重新根据画布画图形
	{
		for (p = 31; p < 41; p++)
		{

			if (map2[k][p] == 1)
			{
				SetPos((p + 1) * 2, k + 1);
				temp.SetColor(0);
				cout << "■";
			}
			else//因为一个方块等于两个空格所以要删两个
			{
				SetPos((p + 1) * 2, k + 1);
				cout << " ";
				SetPos((p + 1) * 2 + 1, k + 1);
				cout << " ";
			}
		}

	}
}
class Game {
public:
	void Run();
};
void Game::Run()
{
	Mino1 player1;
	player1.Random();
	Mino2 player2;
	player2.Random();
	while (1)
	{
		player1.Down();
		player2.Down();
	}
}
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