#include "SDLSystem.h"

SDLSystem::SDLSystem() {}

SDLSystem::~SDLSystem()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	_window = NULL;
	_renderer = NULL;

	SDL_Quit();
}

bool SDLSystem::initSystem(uint32_t $init_width, uint32_t $init_height)
{
	_window_width = $init_width;
	_window_height = $init_height;

	bool $success = true;

	if (initSDL()) {
		if (initWindow()) {
			if (initGraphics()) {
			}
			else
			{
				printf("SDLSystem.initGraphics-> FAILURE: %s\n", SDL_GetError());
				$success = false;
			}
		}
		else
		{
			printf("SDLSystem.initWindow-> FAILURE: %s\n", SDL_GetError());
			$success = false;
		}
	}
	else
	{
		printf("SDLSystem.initSDL-> FAILURE: %s\n", SDL_GetError());
		$success = false;
	}

	return $success;
}

bool SDLSystem::initSDL()
{
	bool $success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
		printf("SDLSystem.initSDL-> FAILURE: %s\n", SDL_GetError());
		$success = false;
	}

	return $success;
}

bool SDLSystem::initWindow()
{
	bool $success = true;

	//_window = SDL_CreateWindow("Angel Endstar - Proof of Concept", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_SHOWN);
	_window = SDL_CreateWindow("Angel Endstar - Proof of Concept", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_FULLSCREEN_DESKTOP);

	if (_window == NULL) {
		printf("SDLSystem.initWindow-> FAILURE: %s\n", SDL_GetError());
		$success = false;
	}

	return $success;
}

bool SDLSystem::initGraphics()
{
	bool $success = true;

	//initialize window renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == NULL) {
		printf("SDLSystem.initGraphics-> FAILURE: %s\n", SDL_GetError());
		$success = false;
	}
	else
	{
		SDL_SetRenderDrawColor(_renderer, DEFAULT_R, DEFAULT_G, DEFAULT_B, DEFAULT_A);

		//VIEWPORT EXPERIMENTATIONS, IMPLEMENT AT LATER POINT
		int $width = 0;
		int $height = 0;

		SDL_GetWindowSize(_window, &$width, &$height);

		double $ratio = 1;

		if ((($width / _window_width) >= 2.0) && (($height / _window_height) >= 2.0)) {
			$ratio = 2.0;
		}

		if (SDL_RenderSetScale(_renderer, $ratio, $ratio) != 0) {
			printf("SDLSystem.initGraphics -> FAILED TO SCALE RENDERER %s\n", SDL_GetError());
		}
		SDL_Rect $viewport;

		$viewport.w = _window_width;
		$viewport.h = _window_height;

		$viewport.x = 0;// ($width - _window_width) >> 1;
		$viewport.y = 0;// ($height - _window_height) >> 1;

		printf(" w? %i h? %i\n", _window_width, _window_height);
		
		SDL_RenderSetViewport(_renderer, &$viewport);
	}

	return $success;
}

SDL_Renderer* SDLSystem::getRenderer()
{
	return _renderer;
}

SDL_Window* SDLSystem::getWindow()
{
	return _window;
}