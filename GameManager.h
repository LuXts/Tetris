#pragma once
#include "SingleSquare.h"
#include "Bricks.h"
#include "iostream"
using namespace std;

#define HeightBySquare 20		//������20������
#define WidthBySquare  10		//������10������

#define Time_Interval 500	//����������ʱ��

enum GameState {
	READY,
	RUNNING,
	PAUSE,
	END
};

class GameManager {
public:
	SingleSquare bcgSquare[WidthBySquare][HeightBySquare+4];		//�������飬���е�[][20],[][21],[][22],[][23]�ֱ�
																	//��ʾ��������������ȥ�ĵ�-4��-3��-2��-1��
	SingleSquare nextSquare[4][4];		//��һ������

	GameState gameState;		//��Ϸ״̬

	point centre;			//���ĵ�
	int brickType;			//���������
	int brickState;			//�������ת״̬
	int brickNext;			//��һ������


	int score;				//����
	int interTime;			//������ʱ��

	GameManager();

	BOOL MoveDown();		//��������
	BOOL RotateTop();		//������ת
	BOOL MoveLeft();		//��������	
	BOOL MoveRight();		//��������


	BOOL LeftCheck(point p, Bricks d);		//�����ײ���
	BOOL RightCheck(point p, Bricks d);		//�ұ���ײ���
	BOOL BelowCheck(point p, Bricks d);		//�·���ײ���
	BOOL TopCheck(point p, Bricks d);		//�Ϸ���ײ���
	BOOL RotateCheck(point p, Bricks d);	//��ת��ײ���

	void FixBricks();		//ȷ����ǰ����λ�ã�д���ͼ

	void NewRound();		//׼����һ�ַ�������ʼ��

	int RowCheck();			//��������У��ж����в���

	void DeleteRow(int n);		//���һ��

	void NewGame();		//����Ϸ��ʼ��

	void InitNextBrick();		//��ʼ����һ������
};