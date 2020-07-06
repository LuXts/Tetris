#include "GameManager.h"
#include "framework.h"
#include <ctime>


//初始化下一个方块
void GameManager::InitNextBrick()
{
	srand(time(0));
	brickNext = rand() % 7;
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
	score = 0;
	gameState = READY;
}


//新一轮方块掉落的初始化
void GameManager::NewRound()
{
	brickType = brickNext;				//方块的种类
	brickState = 0;						//方块的旋转形态
	InitNextBrick();
	//初始化方块出现在地图上的中心点
	centre.set(WidthBySquare / 2, 0 );
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

//碰撞检测
BOOL GameManager::knockCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//方块碰撞检查
		if (bcgSquare[p.x + d.p[i].x ][p.y + d.p[i].y].state)
		{
			return true;
		}
		
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
	if (!knockCheck(point(centre.x, centre.y + 1),bricks[brickType][brickState]))
	{
		centre.set(centre.x, centre.y + 1);

		return true;
	}
	return false;
}

//方块左右移动
BOOL GameManager::MoveLeft()
{
	if (!knockCheck(point(centre.x - 1, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x - 1, centre.y);
		return true;
	}
	return false;
}
BOOL GameManager::MoveRight()
{
	if (!knockCheck(point(centre.x + 1, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x + 1, centre.y);
		return true;
	}
	return false;
}

//旋转
BOOL GameManager::RotateTop()
{
	if (!knockCheck(centre, bricks[brickType][(brickState + 1) % 4]))
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
		for (int j = HeightBySquare - 1; j >= n ; j--)
		{
			bcgSquare[i][j].state = bcgSquare[i][j -1].state;
		}
	}
}

//检查行
int GameManager::RowCheck()
{
	int a[HeightBySquare] = { 1 };     //记录要删除的行,过程中a[0]-1代表着需要删除的行数
	for (int j = HeightBySquare - 1; j >= 0 ; j--)
	{
		BOOL k = true;
		for (int i = 1; i <= WidthBySquare; i++)
		{
			if (!bcgSquare[i][j].state)
			{
				k = false;
				break;
			}
		}
		if (k)
		{
			a[a[0]++] = j;
		}
	}
	for (int i = a[0] - 1; i >= 1; i--)
	{
		DeleteRow(a[i]);		//删除有记录的行
	}
	
	return a[0] - 1;			//返回删除了的行数
}
