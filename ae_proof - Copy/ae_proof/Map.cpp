#include "Map.h"

Map::Map() {}

Map::~Map() {}

//room set/replace 
void Map::setRoom(Room $room, uint32_t $x, uint32_t $y)
{
	if (($x < WIDTH) && ($y < HEIGHT)) {
		room_map[$y][$x] = $room;
	}
}

//map and hit building
void Map::buildMap() {}

void Map::buildHitData()
{
	_hit_width = WIDTH * Room::WIDTH;
	_hit_height = HEIGHT * Room::HEIGHT;

	for (uint32_t $i = 0; $i < _hit_height; $i++) {
		for (uint32_t $j = 0; $j < _hit_width; $j++) {
			_hit_map[$i][$j] = Tile::WALK;
		}
	}

	for (int $i = 0; $i < HEIGHT; $i++) {
		for (int $j = 0; $j < WIDTH; $j++) {
			buildRoomHit(&room_grid[$i][$j], $j, $i);
		}
	}
}

void Map::buildRoomHit(Room* $room, uint32_t $room_x, uint32_t $room_y)
{
	uint32_t $base_x = $room_x * Room::WIDTH;
	uint32_t $base_y = $room_y * Room::HEIGHT;

	for (int $i = 0; $i < Room::HEIGHT; $i++) {
		for (int $j = 0; $j < Room::WIDTH; $j++) {
			_hit_map[$base_y + $i][$base_x + $j] = $room->tile_grid[$i][$j].walk_value;
		}
	}

}

uint32_t Map::getHit(uint32_t $x, uint32_t $y)
{
	if ($y > _hit_height || $x > _hit_width)
	{
		return Tile::WALL;
	}
	if ($y < 0 || $x < 0)
	{
		return Tile::WALL;
	}
	else
	{
		return _hit_map[$y][$x];
	}
}

void Map::drawMap()
{
	if (background != NULL) {
		GameRect $fixed_rect;
		$fixed_rect.w = background->width;
		$fixed_rect.h = background->height;
		$fixed_rect.x = 0;
		$fixed_rect.y = 0;
		graphics->renderTextureFixed(background->sprite_texture, &$fixed_rect, 0, 0);
	}

	GameRect $bg_rect;
	$bg_rect.x = 0;
	$bg_rect.y = 0;
	$bg_rect.w = BackgroundTile::WIDTH;
	$bg_rect.h = BackgroundTile::HEIGHT;

	for (int $n = 0; $n < BG_HEIGHT; $n++) {
		for (int $m = 0; $m < BG_WIDTH; $m++) {
			BackgroundTile $bg_tile = background_grid[$n][$m];
			if ($bg_tile.sprite != NULL) {
				graphics->renderTexture($bg_tile.sprite->sprite_texture, &$bg_rect, ($m * BackgroundTile::WIDTH), ($n * BackgroundTile::HEIGHT), 8);
			}
		}
	}

	//NOT FINALIZED, DRAWS MUST BE SPRITE BASED, NOT TEXTURE
	GameRect $draw_rect;
	$draw_rect.x = 0;
	$draw_rect.y = 0;
	$draw_rect.w = Tile::WIDTH;
	$draw_rect.h = Tile::HEIGHT;

	for (int $i = 0; $i < HEIGHT; $i++) {
		for (int $j = 0; $j < WIDTH; $j++) {
			Room $room = room_grid[$i][$j];
			int $room_x = $j * Room::WIDTH * Tile::WIDTH;
			int $room_y = $i * Room::HEIGHT * Tile::HEIGHT;

			for (int $l = 0; $l < Room::HEIGHT; $l++) {
				for (int $k = 0; $k < Room::WIDTH; $k++) {
					Tile $tile = $room.tile_grid[$l][$k];
					if ($tile.sprite != NULL) {
						graphics->renderTexture($tile.sprite->sprite_texture, &$draw_rect, ($k * Tile::WIDTH) + $room_x, ($l * Tile::HEIGHT) + $room_y);
					}
				}
			}
		}
	}
}
