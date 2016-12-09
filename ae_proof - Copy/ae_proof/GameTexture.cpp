#include "GameTexture.h"

//constructor/destructor
GameTexture::GameTexture()
{
	_sdl_texture = NULL;
	used = 0;
	width = 0;
	height = 0;
}

GameTexture::~GameTexture()
{
	free();
}

void GameTexture::setSDLTexture(SDL_Texture* $sdl_texture)
{
	if ($sdl_texture != NULL)
	{
		_sdl_texture = $sdl_texture;

		int $tex_width, $tex_height;

		SDL_QueryTexture($sdl_texture, NULL, NULL, &$tex_width, &$tex_height);

		width = $tex_width;
		height = $tex_height;
	}
	else
	{
		printf("GameTexture.setSDLTexture-> ERROR: SDL_TEXTURE INVALID POINTER\n");
	}
}

SDL_Texture* GameTexture::getSDLTexture()
{
	return _sdl_texture;
}

void GameTexture::free()
{
	if (_sdl_texture != NULL) {
		used = 0;
		width = 0;
		height = 0;

		SDL_DestroyTexture(_sdl_texture);
		_sdl_texture = NULL;
	}
}

//draw manipulators
void GameTexture::setBlendingMode(char $blend_mode)
{
	SDL_SetTextureBlendMode(_sdl_texture, SDL_BLENDMODE_BLEND);
}

