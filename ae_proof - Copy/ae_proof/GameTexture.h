#ifndef AE_GAME_TEXTURE
#define AE_GAME_TEXTURE

//system includes
#include <string>
#include <stdint.h>
#include <SDL.h>

class GameTexture {
public:
	GameTexture();
	~GameTexture();

	//label values
	std::string path;
	uint32_t id = 0;
	uint32_t used = 0;

	//dimensions
	uint32_t width;
	uint32_t height;

	//load/unload functions
	void setSDLTexture(SDL_Texture* $texture);
	SDL_Texture* getSDLTexture();
	void free();

	//manipulation functions
	void setBlendingMode(char $blend_mode);

private:
	//SDL objects
	SDL_Texture* _sdl_texture;
};

#endif