#ifndef AE_TEXT_OBJECT
#define AE_TEXT_OBJECT

//C++
#include <stdint.h>
//SYSTEM
#include "GameTexture.h"
#include "GameRect.h"

class TextObject {
public:
	TextObject();
	~TextObject();

	//texture object
	GameTexture texture;
	
	//public drawing properties
	uint32_t used = 0;
	
	uint32_t screen_x;
	uint32_t screen_y;

	GameRect draw_rect;

	void getDimensions();
	void free();
};

#endif