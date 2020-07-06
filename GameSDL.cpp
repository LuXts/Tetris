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
}

GameSDL::~GameSDL() {
	if (_win) {
		SDL_DestroyWindow(_win);
	}
}
