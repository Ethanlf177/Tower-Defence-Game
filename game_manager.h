#pragma once

#include "manager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>



class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv) 
	{
		Uint64 last_counter = SDL_GetPerformanceCounter();
		Uint64 counter_freq = SDL_GetPerformanceFrequency();

		while (!is_quit) 
		{
			while (SDL_PollEvent(&event)) 
				on_input();
			
			Uint64 current_counter = SDL_GetPerformanceCounter();
			double delta = (double)(current_counter - last_counter) / counter_freq;
			last_counter = current_counter;
			if (delta * 1000 < 1000.0 / fps)
				SDL_Delay((Uint32)(1000.0 / fps - delta * 1000));

			on_update();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			on_render();

			SDL_RenderPresent(renderer);
			

			//更新数据

			//绘制图像
		}

		return 0;
	}

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	bool is_quit = false;
	int fps = 60;

	void init_assert(bool flag, const char* err_msg) {
		if (flag) return;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
		exit(-1);
	}

	void on_input()
	{

	}

	void on_update()
	{

	}

	void on_render()
	{

	}


protected:
	GameManager() 
	{
		init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败！");
		init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_IMG 初始化失败！");
		init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_MIX 初始化失败！");
		init_assert(!TTF_Init(), u8"SDL_TTF 初始化失败！");

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

		window = SDL_CreateWindow(u8"村庄保卫战", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		init_assert(window, u8"窗口创建失败");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		init_assert(renderer, u8"渲染器创建失败");

	}
	~GameManager()
	{
		SDL_DestroyRenderer(renderer);    //释放顺序要与创建顺序相反
		SDL_DestroyWindow(window);

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
};

