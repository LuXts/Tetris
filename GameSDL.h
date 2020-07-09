#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

class GameSDL
{
private:
	SDL_Window* _Main_win;
	SDL_Renderer* _Main_ren;
	SDL_Window* _Next_win;
	SDL_Renderer* _Next_ren;

	SDL_Texture* _Main_tex;
	SDL_Texture* _Next_tex;

	static Mix_Chunk* _bgm;

	static Mix_Chunk* _Sound_Effect_Button_Hover;
	static Mix_Chunk* _Sound_Effect_Button_Down;

	int _Main_W, _Main_H;
	int _Next_W, _Next_H;

public:
	// 创建游戏界面
	GameSDL(void*, void*);
	// 退出游戏界面
	~GameSDL();
	// 初始化 SDL 系统 必须调用一次！！！！ 在TetrisDlg.cpp 中已经调用
	static void InitGame();
	// 释放 SDL 资源 必须调用一次！！！！ TODO: 未调用
	static void QuitGame();

	// 以下为提供的接口

	// 清空主场景画布
	void MainRendererClear();
	// 主场景添加正方形
	void MainAddBrick(int x, int y);
	// 显示主场景画布
	void MainRendererPresent();

	// 清空下一个方块场景画布
	void NextRendererClear();
	// 下一个方块场景添加正方形
	void NextAddBrick(int x, int y);
	// 显示下一个方块场景画布
	void NextRendererPresent();

	// 音频相关接口

	// 开始背景音乐
	static void StartBKMusic();

	// 停止背景音乐
	static void EndBKMusic();

	// 播放鼠标移动到按钮音效
	static void ButtonHoverSound();

	// 播放按钮按下音效
	static void ButtonDownSound();

	// 音频处理回调函数
	static void DealMusic(int  channel);
};
