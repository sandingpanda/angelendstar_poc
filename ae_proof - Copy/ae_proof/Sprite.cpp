#include "Sprite.h"

//constructor/destructor
Sprite::Sprite() { }

Sprite::~Sprite()
{
	free();

	texture_list = NULL;
}

//load/unload properties
void Sprite::setTexture(GameTexture* $texture)
{
	if (width == 0 && height == 0) {
		printf("Sprite.loadTexture-> ERROR: SPRITE DIMENSIONS MUST BE MORE THAN 0\n");
		return;
	}

	if ($texture != NULL)
	{
		sprite_texture = $texture;

		int $columns = sprite_texture->width / width;
		int $rows = sprite_texture->height / height;
		int $next_x = 0;
		int $next_y = 0;
		int $next_frame = 0;
		int $total_frames = $columns * $rows;

		if ($total_frames < _MAX_FRAMES) {
			for (int $y = 0; $y < $rows; $y++) {
				for (int $x = 0; $x < $columns; $x++) {
					$next_x = $x * width;
					$next_y = $y * height;

					_frames[$next_frame][0] = $next_x;
					_frames[$next_frame][1] = $next_y;

					$next_frame++;
				}
			}
		}
		else
		{
			printf("Sprite.loadTexture-> ERROR: FRAME LIMIT EXCEEDED");
		}

		_animation_rect.w = width;
		_animation_rect.h = height;
	}
}

void Sprite::free()
{
	used = 0;
	name = "";
	visible = true;
	
	width = 0;
	height = 0;
	frame_x = 0;
	frame_y = 0;

	if (texture_list != NULL) {
		if (sprite_texture != NULL) {
			texture_list->freeTexture(sprite_texture->id);
			sprite_texture = NULL;
		}
	}
}

GameRect* Sprite::setFrame(uint32_t $frame)
{
	_animation_rect.x = _frames[$frame][0];
	_animation_rect.y = _frames[$frame][1];

	return &_animation_rect;
}

void Sprite::resetFrames()
{
	for (int $n = 0; $n < _MAX_FRAMES; $n++) {
		_frames[$n][0] = 0;
		_frames[$n][1] = 0;
	}
}