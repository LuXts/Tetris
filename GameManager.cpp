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

	//��һ������
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			nextSquare[i][j].x = i;
			nextSquare[i][j].y = j;
		}
	}

}


//��ʼ����һ������
void GameManager::InitNextBrick()
{
	srand(time(0));
	brickNext = rand() % 7;
}


//����Ϸ��ʼ��
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


//��һ�ַ������ĳ�ʼ��
void GameManager::NewRound()
{
	brickType = brickNext;				//���������
	brickState = 0;						//�������ת��̬
	InitNextBrick();
	//��ʼ����������ڵ�ͼ�ϵ����ĵ�
	centre.set(WidthBySquare / 2, -3 );
}

//������д���ͼ
void GameManager::FixBricks()
{
	for (int i = 0; i < 4; i++)
	{
		bcgSquare[centre.x + bricks[brickType][brickState].p[i].x]
			[centre.y + bricks[brickType][brickState].p[i].y].state = 1;
	}
}

//�����ײ���
BOOL GameManager::LeftCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//��ÿ��С����ֱ���м��
	{
		//����Ƿ�Ϊ��д���ͼ�ķ���
		if (bcgSquare[p.x + d.p[i].x - 1][p.y + d.p[i].y].state)
		{
			return true;
		}

		//����Ƿ�Ϊǽ
		if (p.x + d.p[i].x >= WidthBySquare || p.x + d.p[i].x - 1 < 0)
		{
			return true;
		}
	}
	return false;
}

//�ұ���ײ���
BOOL GameManager::RightCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//��ÿ��С����ֱ���м��
	{
		//�ұ��Ƿ�Ϊ��д���ͼ�ķ���
		if (bcgSquare[p.x + d.p[i].x + 1][p.y + d.p[i].y].state)
		{
			return true;
		}

		//�ұ��Ƿ�Ϊǽ
		if (p.x + d.p[i].x + 1>= WidthBySquare)
		{
			return true;
		}
	}
	return false;
}

//�±���ײ���
BOOL GameManager::BelowCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//��ÿ��С����ֱ���м��
	{
		//�±��Ƿ�Ϊ��д���ͼ�ķ���
		if (bcgSquare[p.x + d.p[i].x][p.y + d.p[i].y + 1].state)
		{
			return true;
		}

		//�±��Ƿ�Ϊǽ
		if (p.y + d.p[i].y + 1 >= HeightBySquare)
		{
			return true;
		}
	}
	return false;
}

//�ϱ���ײ���
BOOL GameManager::TopCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//��ÿ��С����ֱ���м��
	{
		//�ϱ��Ƿ�Ϊǽ
		if (p.y + d.p[i].y == 0)
		{
			return true;
		}
	}
	return false;
}

//��ת��ײ���
BOOL GameManager::RotateCheck(point p, Bricks d)
{
	for (int i = 0; i < 4; i++)//��ÿ��С����ֱ���м��
	{
		//������ײ���
		if (bcgSquare[p.x + d.p[i].x ][p.y + d.p[i].y].state)
		{
			return true;
		}

		//ǽ��ײ���
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

//��������
BOOL GameManager::MoveDown()
{
	if (!BelowCheck(point(centre.x, centre.y + 1),bricks[brickType][brickState]))
	{
		centre.set(centre.x, centre.y + 1);

		return true;
	}
	return false;
}

//��������
BOOL GameManager::MoveLeft()
{
	if (!LeftCheck(point(centre.x - 1, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x - 1, centre.y);
		return true;
	}
	return false;
}

//��������
BOOL GameManager::MoveRight()
{
	if (!RightCheck(point(centre.x + 1, centre.y), bricks[brickType][brickState]))
	{
		centre.set(centre.x + 1, centre.y);
		return true;
	}
	return false;
}

//��ת
BOOL GameManager::RotateTop()
{
	if (!RotateCheck(centre, bricks[brickType][(brickState + 1) % 4]))
	{
		brickState = (brickState + 1) % 4;

		return true;
	}
	return false;
}

//ɾ��ָ��һ��
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

//�����
int GameManager::RowCheck()
{
	int a[HeightBySquare] = { 1 };     //��¼Ҫɾ������,������a[0]-1��������Ҫɾ��������
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
		DeleteRow(a[i]);		//ɾ���м�¼����
	}
	
	return a[0] - 1;			//����ɾ���˵�����
}
