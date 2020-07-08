#pragma once
#include "SingleSquare.h"
#include "Bricks.h"
#include "iostream"
using namespace std;

#define HeightBySquare 20		//背景长20个方块
#define WidthBySquare  10		//背景宽10个方块

#define Time_Interval 500	//方块下落间隔时间

enum GameState {
	READY,
	RUNNING,
	PAUSE,
	END
};

class GameManager {
public:
	SingleSquare bcgSquare[WidthBySquare][HeightBySquare];		//背景方块，其中的[][20],[][21],[][22],[][23]分别
																	//表示从上往下数被隐去的第-4，-3，-2，-1行
	SingleSquare nextSquare[4][4];		//下一个方块

	GameState gameState;		//游戏状态

	point centre;			//中心点
	int brickType;			//方块的种类
	int brickState;			//方块的旋转状态
	int brickNext;			//下一个方块

	int score;				//分数
	int interTime;			//下落间隔时间

	GameManager();

	BOOL MoveDown();		//方块下移
	BOOL RotateTop();		//方块旋转
	BOOL MoveLeft();		//方块左移
	BOOL MoveRight();		//方块右移

	BOOL LeftCheck(point p, Bricks d);		//左边碰撞检测
	BOOL RightCheck(point p, Bricks d);		//右边碰撞检测
	BOOL BelowCheck(point p, Bricks d);		//下方碰撞检测
	BOOL TopCheck(point p, Bricks d);		//上方碰撞检测
	BOOL RotateCheck(point p, Bricks d);	//旋转碰撞检测

	BOOL ScoreCheck(int s);		//判断分数是否累计到需要加速

	void FixBricks();		//确定当前方块位置，写入地图

	void NewRound();		//准备新一轮方块掉落初始化

	int RowCheck();			//检查所有行，判断消行操作

	void DeleteRow(int n);		//清除一行

	void NewGame();		//新游戏初始化

	void InitNextBrick();		//初始化下一个方块
};
