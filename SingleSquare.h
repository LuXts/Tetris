#pragma once

#include <windows.h>
#include<iostream>
using namespace std;

//һ��������������ȫ����Ϣ
class SingleSquare {
public:
	int x , y;			//����
	int state;					//����״̬	

	void SingleSqure() {
		x = 0; y = 0;
		state = 0;
	}
};