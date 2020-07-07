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
		for (int j = -4, k = 20; j < 0; j++,k++) {
			bcgSquare[i][k].x = i;
			bcgSquare[i][k].y = j;
		}
	}

	//下一个方块
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			nextSquare[i][j].x = i;
			nextSquare[i][j].y = j;
		}
	}

}


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
	centre.set(WidthBySquare / 2, -3 );
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
		if (p.x + d.p[i].x + 1>= WidthBySquare)
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

//上边碰撞检测
BOOL GameManager::TopCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//对每个小方块分别进行检查
	{
		//上边是否为墙
		if (p.y + d.p[i].y == 0)
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
		if (bcgSquare[p.x + d.p[i].x ][p.y + d.p[i].y].state)
		{
			return true;
		}

		//墙碰撞检测
		if (p.x + d.p[i].x >= WidthBySquare || p.x + d.p[i].x < 0)
		{
			return true;
		}
		if (p.y + d.p[i].y >= HeightBySquare )
		{
			return true;
		}
	}
	return false;
}

//方块下移
BOOL GameManager::MoveDown()
{
	if (!BelowCheck(point(centre.x, centre.y + 1),bricks[brickType][brickState]))
	{
		centre.set(centre.x, centre.y + 1);

		return true;
	}
	return false;
}

//方块左移
BOOL GameManager::MoveLeft()
{
	if (!LeftCheck(point(centre.x - 1, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x - 1, centre.y);
		return true;
	}
	return false;
}

//方块右移
BOOL GameManager::MoveRight()
{
	if (!RightCheck(point(centre.x + 1, centre.y), bricks[brickType][brickState]))
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
