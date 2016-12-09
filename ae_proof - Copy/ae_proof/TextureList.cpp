#include "TextureList.h"

//constructor/destructor
TextureList::TextureList() { }

TextureList::~TextureList()
{
	for (int $n = 0; $n < MAX_TEXTURES; $n++) {
		_texture_list[$n].free();
	}
}

//system object initializers
void TextureList::setGraphics(Graphics* $graphics)
{
	if ($graphics == NULL) {
		printf("GameTexture.setGraphics-> ERROR: AE_GRAPHICS IS NOT VALID");
	}
	else
	{
		_graphics = $graphics;
	}
}

//loading functions
GameTexture* TextureList::loadTexture(std::string $path)
{
	if (_active_count >= MAX_TEXTURES) {
		printf("TextureList.loadTexture-> MAXIMUM TEXTURES ALLOCATED");
	}

	for (int $n = 0; $n < MAX_TEXTURES; $n++) {
		if (_texture_list[$n].path == $path) {
			_texture_list[$n].used++;

			return &_texture_list[$n];
			break;
		}
		else
		{
			if (_texture_list[$n].used == 0) {
				if (loadSDLTexture(&_texture_list[$n], $path)) {
					_texture_list[$n].used++;
					_active_count++;
					return &_texture_list[$n];
					break;
				}
			}
		}
	}

	return NULL;
}

void TextureList::freeTexture(uint32_t $id)
{
	for (int $n = 0; $n < MAX_TEXTURES; $n++) {
		if (_texture_list[$n].id == $id) {
			_texture_list[$n].used -= 1;

			if (_texture_list[$n].used == 0) {
				_texture_list[$n].free();
				_active_count -= 1;
			}
			break;
		}
	}
}

bool TextureList::loadSDLTexture(GameTexture* $texture, std::string $path)
{
	$texture->free();

	SDL_Texture* $sdl_texture = _graphics->loadTexture($path);

	if ($sdl_texture == NULL) {
		printf("TextureList.loadSDLTexture-> FAILURE TO LOAD TEXTURE %s\n", SDL_GetError());
		return false;
	}
	else
	{
		$texture->setSDLTexture($sdl_texture);
		$texture->path = $path;
	}

	return true;
}