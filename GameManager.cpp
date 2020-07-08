#include "pch.h"
#include "GameManager.h"
#include <ctime>

GameManager::GameManager()
{
	for (int i = 0; i < WidthBySquare; i++)
	{
		for (int j = 0; j < HeightBySquare; j++)
		{
			bcgSquare[i][j].x = i;
			bcgSquare[i][j].y = j;
		}
	}
}

//初始化下一个方块
void GameManager::InitNextBrick()
{
	static bool t = true;
	static int temp = 0;
	static bool a[7];

	if (t) {
		srand(time(0));
		t = false;
	}

	if (temp == 7) {
		for (int i = 0; i < 7; i++) {
			a[i] = false;
		}
		temp = 0;
	}

	while (true)
	{
		brickNext = rand() % 7;
		if (a[brickNext] == false) {
			a[brickNext] = true;
			break;
		}
	}
	temp++;
}

//新游戏初始化
void GameManager::NewGame()
{
	for (int i = 0; i < WidthBySquare; i++)
	{
		for (int j = 0; j < HeightBySquare; j++)
		{
			bcgSquare[i][j].state = 0;
		}
	}
	InitNextBrick();
	NewRound();
}

//新一轮方块掉落的初始化
void GameManager::NewRound()
{
	brickState = 0;						//方块的旋转形态
	brickType = brickNext;//方块的种类
	InitNextBrick();
	//初始化方块出现在地图上的中心点
	centre.set(WidthBySquare / 2, 2);
}

//将方块写入地图
void GameManager::FixBricks()
{
	for (int i = 0; i < 4; i++)
	{
		bcgSquare[centre.x + bricks[brickType][brickState].p[i].x]
			[centre.y + bricks[brickType][brickState].p[i].y].state = 1;
	}
}

//左边碰撞检测
BOOL GameManager::LeftCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//左边是否为被写入地图的方块
		if (bcgSquare[p.x + d.p[i].x - 1][p.y + d.p[i].y].state)
		{
			return true;
		}

		//左边是否为墙
		if (p.x + d.p[i].x >= WidthBySquare || p.x + d.p[i].x - 1 < 0)
		{
			return true;
		}
	}
	return false;
}

//右边碰撞检测
BOOL GameManager::RightCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//右边是否为被写入地图的方块
		if (bcgSquare[p.x + d.p[i].x + 1][p.y + d.p[i].y].state)
		{
			return true;
		}

		//右边是否为墙
		if (p.x + d.p[i].x + 1 >= WidthBySquare)
		{
			return true;
		}
	}
	return false;
}

//下边碰撞检测
BOOL GameManager::BelowCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//下边是否为被写入地图的方块
		if (bcgSquare[p.x + d.p[i].x][p.y + d.p[i].y + 1].state)
		{
			return true;
		}

		//下边是否为墙
		if (p.y + d.p[i].y + 1 >= HeightBySquare)
		{
			return true;
		}
	}
	return false;
}

//旋转碰撞检测
BOOL GameManager::RotateCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//方块碰撞检测
		if (bcgSquare[p.x + d.p[i].x][p.y + d.p[i].y].state)
		{
			return true;
		}

		//墙碰撞检测
		if (p.x + d.p[i].x >= WidthBySquare || p.x + d.p[i].x < 0)
		{
			return true;
		}
		if (p.y + d.p[i].y >= HeightBySquare)
		{
			return true;
		}
	}
	return false;
}

//方块下移
BOOL GameManager::MoveDown()
{
	if (!BelowCheck(point(centre.x, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x, centre.y + 1);

		return true;
	}
	return false;
}

//方块左移
BOOL GameManager::MoveLeft()
{
	if (!LeftCheck(point(centre.x, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x - 1, centre.y);
		return true;
	}
	return false;
}

//方块右移
BOOL GameManager::MoveRight()
{
	if (!RightCheck(point(centre.x, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x + 1, centre.y);
		return true;
	}
	return false;
}

//旋转
BOOL GameManager::RotateTop()
{
	if (!RotateCheck(centre, bricks[brickType][(brickState + 1) % 4]))
	{
		brickState = (brickState + 1) % 4;

		return true;
	}
	return false;
}

//删除指定一行
void GameManager::DeleteRow(int n)
{
	for (int i = 0; i < WidthBySquare; i++)
	{
		for (int j = n; j > 0; j--)
		{
			bcgSquare[i][j].state = bcgSquare[i][j - 1].state;
		}
	}
}

//检查行
int GameManager::RowCheck()
{
	int total = 0;
	int a[HeightBySquare] = { 0 };
	for (int j = 0; j < HeightBySquare; j++)
	{
		bool test = true;
		for (int i = 0; i < WidthBySquare; i++) {
			test = test & bcgSquare[i][j].state;
		}
		if (test) {
			a[j] = 1;
			total += 1;
		}
	}
	for (int j = 0; j < HeightBySquare; j++) {
		if (a[j] == 1) {
			DeleteRow(j);
		}
	}

	return total;			//返回删除了的行数
}

BOOL GameManager::TopCheck()
{
	bool test = false;
	for (int i = 0; i < WidthBySquare; i++) {
		test = test | bcgSquare[i][4].state;
	}
	return test;
}