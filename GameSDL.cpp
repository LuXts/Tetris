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

GameSDL::GameSDL(void* handle) :_win(NULL), _ren(NULL), _tex(NULL) {
	_win = SDL_CreateWindowFrom(handle);
	if (_win == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}
	_ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
	if (_ren == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_Surface* playerSur = IMG_Load("res\\brick.png");
	if (playerSur == nullptr) {
		LOG(lena::LOG_LEVEL_ERROR, "GameSDL: Surface could not be created! IMG_Error: %s\n", IMG_GetError());
	}
	_tex = SDL_CreateTextureFromSurface(_ren, playerSur);
	SDL_FreeSurface(playerSur);
	SDL_GetWindowSize(_win, &w, &h);
	LOG(lena::LOG_LEVEL_DEBUG, "WindowSize: %d, %d", w, h);
	SDL_SetRenderDrawColor(_ren, 40, 44, 52, 255);
	RendererClear();
}

GameSDL::~GameSDL() {
	if (_win) {
		SDL_DestroyWindow(_win);
	}
}

void GameSDL::RendererClear()
{
	SDL_RenderClear(_ren);
}

void GameSDL::MapAddBrick(int x, int y) {
	SDL_Rect rect;
	rect.x = (w / 10) * x;
	rect.y = (h / 20) * y;
	rect.w = w / 10;
	rect.h = h / 20;

	SDL_RenderCopy(_ren, _tex, NULL, &rect);
}

void GameSDL::RendererPresent() {
	SDL_RenderPresent(_ren);
}