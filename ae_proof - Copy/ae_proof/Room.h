#ifndef AE_MAP_ROOM
#define AE_MAP_ROOM

//C++
#include <array>
#include <stdint.h>

//MAP INCLUDES
#include "Tile.h"
#include "Formation.h"
#include "BackgroundTile.h"

enum class ScrollFlag { NO_CHANGE, START_SCROLL, STOP_SCROLL, CHANGE_SCROLL};

class Room {
public:
	Room();
	~Room();

	static const uint32_t WIDTH = 16;
	static const uint32_t HEIGHT = 9;

	Tile* tile_map[HEIGHT][WIDTH];
	std::array< std::array<Tile, WIDTH>, HEIGHT> tile_grid;

	std::array< Formation, WIDTH> formation_line;

	uint32_t id = 0;
	std::string room_name;

	//scroll values
	ScrollFlag scroll_flag = ScrollFlag::NO_CHANGE;
	int scroll_dir_x = 0;
	int scroll_dir_y = 0;
	int scroll_speed_x = 0;
	int scroll_speed_y = 0;
};

#endif