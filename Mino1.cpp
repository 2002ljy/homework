#include"head.h"
#include "other.h"
#include"Mino1.h"
Mino1::Mino1()
{
	point[0] = 0;//玩家一 
	point[1] = 4;
	i = 0;
	id1 = 0;
	next_id1 = 0;
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
void Mino1::Down()//下落函数
{
	int t;
	while (1)
	{

		if (!(i < 150))				//i 与 count 用于控制时间
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
					SetPos(15, 10);
					cout << "游戏结束！" << endl;
					SetPos(15, 12);
					cout << "玩家一失败" << endl;
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
void Mino1::Random()
{
	srand((int)time(0));

	id1 = rand() % 15;//玩家一 
	next_id1 = rand() % 15;
	Draw(point[0], point[1], id1);//玩家一 
	Draw(6, 14, next_id1);
}
void Mino1::readKey()
{
	if (_kbhit())				//键盘输入值时 
	{
		int key;
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
int Mino1::ClearLine(int p1, int p2, int idw) //消除行
{
	int flag = 1, t = 0;
	int l, k, p;
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