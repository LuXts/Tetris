#include "pch.h"
#include "GameSDL.h"
#include "Log.h"

void GameSDL::InitGame() {
	int SDL_flag = SDL_INIT_EVERYTHING;
	int SDL_initted = SDL_Init(SDL_flag);
	if (SDL_initted != 0) {
		LOG(lena::LOG_LEVEL_ERROR, "SDL_Init: Failed to init SDL2 support!\n");
		LOG(lena::LOG_LEVEL_ERROR, "SDL_Init: %s\n", SDL_GetError());
	}
	int image_flag = IMG_INIT_PNG;
	int image_initted = IMG_Init(image_flag);
	if ((image_initted & image_flag) != image_flag) {
		LOG(lena::LOG_LEVEL_ERROR, "IMG_Init: Failed to init required png support!\n");
		LOG(lena::LOG_LEVEL_ERROR, "IMG_Init: %s\n", IMG_GetError());
	}
}

void GameSDL::QuitGame() {
	IMG_Quit();
	SDL_Quit();
}

GameSDL::GameSDL(void* handle_1, void* handle_2) :_Main_win(NULL), _Main_ren(NULL), _Next_win(NULL), _Next_ren(NULL), _Main_tex(NULL), _Next_tex(NULL), _Main_W(0), _Main_H(0), _Next_W(0), _Next_H(0) {
	// 注册游戏主要窗口
	_Main_win = SDL_CreateWindowFrom(handle_1);
	if (_Main_win == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Main Game Window could not be created!\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	// 注册游戏主渲染器
	_Main_ren = SDL_CreateRenderer(_Main_win, -1, SDL_RENDERER_ACCELERATED);
	if (_Main_ren == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Main Game Renderer could not be created!\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	// 注册下个方块窗口
	_Next_win = SDL_CreateWindowFrom(handle_2);
	if (_Next_win == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: NeXt Brick Window could not be created!\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	// 注册下个方块渲染器
	_Next_ren = SDL_CreateRenderer(_Next_win, -1, SDL_RENDERER_ACCELERATED);
	if (_Next_ren == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: NeXt Brick Renderer could not be created!\n SDL_Error: %s\n", SDL_GetError());
		return;
	}

	// 加载贴图
	SDL_Surface* playerSur = IMG_Load("res\\brick.png");
	if (playerSur == nullptr) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Main Game Surface could not be created!\n IMG_Error: %s\n", IMG_GetError());
		return;
	}
	_Main_tex = SDL_CreateTextureFromSurface(_Main_ren, playerSur);
	_Next_tex = SDL_CreateTextureFromSurface(_Next_ren, playerSur);
	SDL_FreeSurface(playerSur);

	// 获取窗口宽度
	SDL_GetWindowSize(_Main_win, &_Main_W, &_Main_H);
	SDL_GetWindowSize(_Next_win, &_Next_W, &_Next_H);

	// 输出窗口宽度检查
	LOG(lena::LOG_LEVEL_DEBUG, "WindowSize: %d, %d", _Main_W, _Main_H);
	LOG(lena::LOG_LEVEL_DEBUG, "WindowSize: %d, %d", _Next_W, _Next_H);

	// 设置渲染器背景色
	SDL_SetRenderDrawColor(_Main_ren, 40, 44, 52, 255);
	SDL_SetRenderDrawColor(_Next_ren, 40, 44, 52, 255);

	// 清空主渲染器内容 改变完背景色之后必须清空内容，才能显示新的背景色上去。
	MainRendererClear();
	NextRendererClear();
}

GameSDL::~GameSDL() {
	if (_Main_tex) {
		SDL_DestroyTexture(_Main_tex);
	}
	if (_Next_ren) {
		SDL_DestroyRenderer(_Next_ren);
	}
	if (_Next_win) {
		SDL_DestroyWindow(_Next_win);
	}
	if (_Main_ren) {
		SDL_DestroyRenderer(_Main_ren);
	}
	if (_Main_win) {
		SDL_DestroyWindow(_Main_win);
	}
}

void GameSDL::MainRendererClear()
{
	SDL_RenderClear(_Main_ren);
}

void GameSDL::MainAddBrick(int x, int y) {
	SDL_Rect rect;
	rect.x = (_Main_W / 10) * x;
	rect.y = (_Main_H / 20) * y;
	rect.w = _Main_W / 10;
	rect.h = _Main_H / 20;

	SDL_Rect tex_rect;
	tex_rect.x = 0;
	tex_rect.y = 256;
	tex_rect.w = 256;
	tex_rect.h = 256;

	SDL_RenderCopy(_Main_ren, _Main_tex, &tex_rect, &rect);
}

void GameSDL::MainRendererPresent() {
	SDL_RenderPresent(_Main_ren);
}

void GameSDL::NextRendererClear() {
	SDL_RenderClear(_Next_ren);
}

void GameSDL::NextAddBrick(int x, int y) {
	SDL_Rect rect;
	rect.x = (_Next_W / 4) * x;
	rect.y = (_Next_H / 4) * y;
	rect.w = _Next_W / 4;
	rect.h = _Next_H / 4;

	SDL_Rect tex_rect;
	tex_rect.x = 256;
	tex_rect.y = 0;
	tex_rect.w = 256;
	tex_rect.h = 256;

	SDL_RenderCopy(_Next_ren, _Next_tex, &tex_rect, &rect);
}

void GameSDL::NextRendererPresent() {
	SDL_RenderPresent(_Next_ren);
}