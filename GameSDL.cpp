#include "pch.h"
#include "GameSDL.h"
#include "Log.h"

Mix_Chunk* GameSDL::_bgm = NULL;
Mix_Chunk* GameSDL::_Sound_Effect_Button_Hover = NULL;
Mix_Chunk* GameSDL::_Sound_Effect_Button_Down = NULL;

void GameSDL::DealMusic(int  channel) {
	static bool t = true;
	static int temp = 3;
	if (t) {
		srand(time(0));
		t = false;
	}

	if (channel == 1) {
		int i;
		while (true) {
			i = rand() % 3;
			if (i != temp) {
				temp = i;
				break;
			}
		}

		switch (i) {
		case 0:
			Mix_FreeChunk(_bgm);
			_bgm = Mix_LoadWAV("res\\bgm1.mp3");
			Mix_FadeInChannel(channel, _bgm, 1, 1000);
			break;
		case 1:
			Mix_FreeChunk(_bgm);
			_bgm = Mix_LoadWAV("res\\bgm2.mp3");
			Mix_FadeInChannel(channel, _bgm, 1, 1000);
			break;
		case 2:
			Mix_FreeChunk(_bgm);
			_bgm = Mix_LoadWAV("res\\bgm3.mp3");
			Mix_FadeInChannel(channel, _bgm, 1, 1000);
			break;
		}
	}
}

void GameSDL::StartBKMusic() {
	DealMusic(1);
	Mix_ChannelFinished(DealMusic);
}

void GameSDL::EndBKMusic() {
	Mix_FadeOutChannel(1, 1000);
}

void GameSDL::ButtonHoverSound() {
	Mix_PlayChannel(2, _Sound_Effect_Button_Hover, 1);
}

void GameSDL::ButtonDownSound() {
	Mix_PlayChannel(3, _Sound_Effect_Button_Hover, 1);
}

void GameSDL::InitGame() {
	int SDL_flag = SDL_INIT_EVERYTHING;
	int SDL_initted = SDL_Init(SDL_flag);
	if ((SDL_initted & SDL_flag) != SDL_flag) {
		LOG(lena::LOG_LEVEL_ERROR, "SDL_Init: Failed to init SDL2 support!\n");
		LOG(lena::LOG_LEVEL_ERROR, "SDL_Init: %s\n", SDL_GetError());
	}
	int image_flag = IMG_INIT_PNG;
	int image_initted = IMG_Init(image_flag);
	if ((image_initted & image_flag) != image_flag) {
		LOG(lena::LOG_LEVEL_ERROR, "IMG_Init: Failed to init required png support!\n");
		LOG(lena::LOG_LEVEL_ERROR, "IMG_Init: %s\n", IMG_GetError());
	}
	int MIX_flag = MIX_INIT_MP3;
	int MIX_initted = Mix_Init(MIX_flag);
	if ((MIX_initted & MIX_flag) != MIX_flag) {
		LOG(lena::LOG_LEVEL_ERROR, "Mix_Init: Failed to init required music support!\n");
		LOG(lena::LOG_LEVEL_ERROR, "Mix_Init: %s\n", Mix_GetError());
	}

	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);

	_Sound_Effect_Button_Hover = Mix_LoadWAV("res\\Button.wav");

	Mix_Volume(2, 24);
	Mix_Volume(3, 24);

	if (_Sound_Effect_Button_Hover == NULL) {
		LOG(lena::LOG_LEVEL_ERROR, "Mix_Init: Failed to load music!\n");
		LOG(lena::LOG_LEVEL_ERROR, "Mix_Init: %s\n", Mix_GetError());
	}
}

void GameSDL::QuitGame() {
	Mix_FreeChunk(_bgm);
	Mix_FreeChunk(_Sound_Effect_Button_Down);
	Mix_FreeChunk(_Sound_Effect_Button_Hover);
	Mix_CloseAudio();
	Mix_Quit();
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
	LOG_DEBUG("WindowSize: %d, %d", _Main_W, _Main_H);
	LOG_DEBUG("WindowSize: %d, %d", _Next_W, _Next_H);

	// 设置渲染器背景色
	SDL_SetRenderDrawColor(_Main_ren, 40, 44, 52, 255);
	SDL_SetRenderDrawColor(_Next_ren, 40, 44, 52, 255);

	// 清空主渲染器内容 改变完背景色之后必须清空内容，才能显示新的背景色上去。
	MainRendererClear();
	NextRendererClear();
}

GameSDL::~GameSDL() {
	if (_Next_tex) {
		SDL_DestroyTexture(_Next_tex);
	}
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