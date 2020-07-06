#pragma once
#include "SingleSquare.h"
#include "Bricks.h"
#include "iostream"
using namespace std;

#define HeightBySquare 20		//������20������
#define WidthBySquare  10		//������10������

#define SquarePX 24		//����������ռ����

#define HegithByPX HeightBySquare*SquarePX		//������
#define WidthByPX WidthBySquare*SquarePX		//������

#define Time_Interval 500	//����������ʱ��

enum GameState {
	READY,
	RUNNING,
	PAUSE,
	END
};

class GameManager {
public:
	SingleSquare bcgSquare[WidthBySquare][HeightBySquare];		//��������
	SingleSquare nextSquare[4][5];		//��һ������

	GameState gameState;		//��Ϸ״̬

	point centre;			//���ĵ�
	int brickType;			//���������
	int brickState;		//�����״̬
	int brickNext;			//��һ������


	int score;				//����
	int interTime;			//������ʱ��

	BOOL MoveDown();		//��������
	BOOL RotateTop();		//������ת
	BOOL MoveLeft();		//��������	
	BOOL MoveRight();		//��������


	BOOL knockCheck(point p, Bricks d);		//��ײ���

	void FixBricks();		//ȷ����ǰ����λ�ã�д���ͼ

	void NewRound();		//׼����һ�ַ�������ʼ��

	int RowCheck();			//��������У��ж����в���

	void DeleteRow(int n);		//���һ��

	void NewGame();		//����Ϸ��ʼ��

	void InitNextBrick();		//��ʼ����һ������
};