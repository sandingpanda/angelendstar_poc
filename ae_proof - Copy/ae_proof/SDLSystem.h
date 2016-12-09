#ifndef AE_SDL_SYSTEM
#define AE_SDL_SYSTEM

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>

class SDLSystem {
public:
	SDLSystem();
	~SDLSystem();

	bool initSystem(uint32_t $init_width, uint32_t $init_height);
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

private:
	//default color values for window renderer
	static const int DEFAULT_R = 0x00;
	static const int DEFAULT_G = 0x00;
	static const int DEFAULT_B = 0x00;
	static const int DEFAULT_A = 0xFF;

	uint32_t _window_width;
	uint32_t _window_height;

	bool initSDL();
	bool initGraphics();
	bool initWindow();

	SDL_Window* _window;
	SDL_Renderer* _renderer;
};


#endif