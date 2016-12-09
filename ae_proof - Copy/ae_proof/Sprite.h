#ifndef AE_SPRITE
#define AE_SPRITE

//C++ INCLUDES
#include <stdint.h>
#include <string>

//SYSTEM INCLUDES
#include "GameTexture.h"
#include "TextureList.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	//public usage attributes
	uint32_t used = 0;
	std::string name;
	bool visible = true;
	
	//dimensions
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t frame_x = 0;
	uint32_t frame_y = 0;

	//external objects
	GameTexture* sprite_texture;
	TextureList* texture_list;

	//load/unload functions
	void setTexture(GameTexture* $texture);
	void free();

	//animation functions
	GameRect* setFrame(uint32_t $frame);

private:
	static const int _MAX_FRAMES = 128;
	
	uint32_t _frames[_MAX_FRAMES][2];

	GameRect _animation_rect;

	void resetFrames();
};

#endif