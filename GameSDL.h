#pragma once

#include "SDL.h"
#include "SDL_image.h"

class GameSDL
{
private:
	SDL_Window* _win;
	SDL_Renderer* _ren;
	SDL_Texture* _tex;

public:
	//创建游戏界面
	GameSDL(void*);
	//退出游戏界面
	~GameSDL();
	//初始化 SDL 系统 必须调用一次！！！！ 在TetrisDlg.cpp 中已经调用
	static void InitGame();
	//释放 SDL 资源 必须调用一次！！！！ TODO: 未调用
	static void QuitGame();

	//以下为提供的接口
};
