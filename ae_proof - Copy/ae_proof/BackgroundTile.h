#ifndef AE_MAP_BG_TILE
#define AE_MAP_BG_TILE

//C++
#include <stdint.h>

//SYSTEM
#include "Sprite.h"

class BackgroundTile {
public:
	BackgroundTile();
	~BackgroundTile();

	//constant size in pixels
	static const uint32_t WIDTH = 120;
	static const uint32_t HEIGHT = 120;

	Sprite* sprite;
	std::string name;
};

#endif