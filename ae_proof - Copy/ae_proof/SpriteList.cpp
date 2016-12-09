#include "SpriteList.h"

//constructor/destructor
SpriteList::SpriteList() { }

SpriteList::~SpriteList()
{
	for (int $n = 0; $n < _MAX_SPRITES; $n++)
	{
		_sprite_list[$n].free();
	}

	_texture_list = NULL;
}

//assignments
void SpriteList::setTextureList(TextureList* $texture_list)
{
	if ($texture_list != NULL)
	{
		_texture_list = $texture_list;

		for (int $n = 0; $n < _MAX_SPRITES; $n++)
		{
			_sprite_list[$n].texture_list = _texture_list;
		}
	}
	else
	{
		printf("SpriteList.setTextureList-> ERROR: INVALID TEXTURELIST ASSIGNEMENT\n");
	}
}

//set/free sprites
Sprite* SpriteList::setSprite(std::string $texture_path, char* $name, uint32_t $width, uint32_t $height)
{
	Sprite* $sprite = NULL;

	for (int $n = 0; $n < _MAX_SPRITES; $n++)
	{
		if (_sprite_list[$n].used > 0) {
			if (_sprite_list[$n].name == $name) {
				_sprite_list[$n].used++;
				$sprite = &_sprite_list[$n];
				break;
			}
		}
		else
		{
			$sprite = &_sprite_list[$n];
			$sprite->width = $width;
			$sprite->height = $height;
			$sprite->name = $name;
			$sprite->used++;
			$sprite->setTexture(_texture_list->loadTexture($texture_path));
			break;
		}
	}
	return $sprite;
}

void SpriteList::freeSprite(Sprite* $sprite)
{
	$sprite->used--;

	if ($sprite->used == 0) {
		$sprite->free();
	}
}