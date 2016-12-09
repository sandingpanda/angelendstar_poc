#ifndef AE_MAP
#define AE_MAP

//C++
#include <stdint.h>

//SYSTEM
#include "GameRect.h"
#include "Graphics.h"

//MAP INCLUDES
#include "Room.h"
#include "Tile.h"
#include "BackgroundTile.h"

class Map {
public:
	Map();
	~Map();

	//constant size in Room objects
	static const uint32_t WIDTH = 6;
	static const uint32_t HEIGHT = 1;

	static const uint32_t BG_WIDTH = 16;
	static const uint32_t BG_HEIGHT = 9;

	//Room map and hit grid
	Room room_map[HEIGHT][WIDTH];
	std::array< std::array<Room, WIDTH>, HEIGHT> room_grid;

	//background map
	std::array< std::array<BackgroundTile, BG_WIDTH>, BG_HEIGHT> background_grid;

	//static background
	Sprite* background;
	std::string background_path;

	//buildout functions
	void buildMap();
	void buildHitData();

	//room set
	void setRoom(Room $room, uint32_t $x, uint32_t $y);

	//hit grid retrieval
	uint32_t getHit(uint32_t $x, uint32_t $y);

	void drawMap();

	Graphics* graphics;

private:
	uint32_t _hit_width, _hit_height;
	uint32_t _hit_map[HEIGHT*Room::HEIGHT][WIDTH*Room::WIDTH];

	//internal hit buildout
	void buildRoomHit(Room* $room, uint32_t $room_x, uint32_t $room_y);
};

#endif