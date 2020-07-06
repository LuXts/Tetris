#pragma once

#include <windows.h>
#include<iostream>
using namespace std;

//一个方块所包含的全部信息
class SingleSquare {
public:
	int x , y;			//坐标
	int state;					//方块状态	

	void SingleSqure() {
		x = 0; y = 0;
		state = 0;
	}
};