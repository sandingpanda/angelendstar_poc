#ifndef AE_MAP_TILE
#define AE_MAP_TILE

//C++
#include <stdint.h>

//SYSTEM
#include "Sprite.h"

class Tile {
public:
	Tile();
	~Tile();

	//constant size in pixels
	static const uint32_t WIDTH = 60;
	static const uint32_t HEIGHT = 60;

	//walk values
	static const int WALK = 0;
	static const int WALL = 1;

	Sprite* sprite;
	uint32_t walk_value = 0;
	std::string name;
};

#endif