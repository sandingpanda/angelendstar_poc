#ifndef AE_TEXTURE_LIST
#define AE_TEXTURE_LIST

//SYSTEM INCLUDES
#include <vector>
#include <stdint.h>
#include <SDL.h>

//GAME INCLUDES
#include "Graphics.h"
#include "GameTexture.h"

class TextureList
{
public:
	TextureList();
	~TextureList();

	//loading functions
	GameTexture* loadTexture(std::string $path);
	void freeTexture(uint32_t $id);
	void setGraphics(Graphics* $graphics);

	//static constants
	static const uint32_t MAX_TEXTURES = 256;

private:
	//list variables
	GameTexture _texture_list[MAX_TEXTURES];
	uint32_t _active_count = 0;

	bool loadSDLTexture(GameTexture* $texture, std::string $path);

	Graphics* _graphics;
};

#endif