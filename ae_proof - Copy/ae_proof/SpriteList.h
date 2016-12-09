#ifndef AE_SPRITE_LIST
#define AE_SPRITE_LIST

//C++
#include <string>
#include <stdint.h>

//system
#include "Sprite.h"

class SpriteList
{
public:
	SpriteList();
	~SpriteList();

	//initializers
	void setTextureList(TextureList* $texture_list);

	//public set/free
	Sprite* setSprite(std::string $path, char* $name, uint32_t $width, uint32_t $height);
	void freeSprite(Sprite* $sprite);

private:
	static const uint32_t _MAX_SPRITES = 64;
	
	uint32_t _active_count = 0;
	Sprite _sprite_list[_MAX_SPRITES];

	TextureList* _texture_list;
};

#endif