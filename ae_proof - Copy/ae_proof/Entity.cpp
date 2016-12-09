#include "Entity.h"

const char* Entity::SPRITE_PATH = "";

void Entity::think(Entity* $self) {}

void Entity::die() {}

void Entity::reset()
{
	active = false;

	x = 0;
	y = 0;
	dir_x = 0;
	dir_y = 0;
	gravity = false;
	x_speed = 0;
	y_speed = 0;
	falling = false;
	jumping = false;
	collide = true;

	walk_speed = jump_speed = 0;

	room_x = room_y = 0;
	tile_x = tile_y = 0;

	bound_rect.x = 0;
	bound_rect.y = 0;
	bound_rect.w = 0;
	bound_rect.h = 0;

	show_bounds = false;

	half_width = 0;
	half_height = 0;
	wall_up = false;
	wall_down = false;
	wall_left = false;
	wall_right = false;

	time_to_think = 0;

	if (sprite != NULL) {
		sprite->free();
	}

	current_frame = 0;
	parent = NULL;
}

void Entity::initBounds(uint32_t $bound_w, uint32_t $bound_h)
{
	bound_rect.w = $bound_w;
	bound_rect.h = $bound_h;

	half_width = $bound_w / 2;
	half_height = $bound_h / 2;
}


void Entity::moveEntity(MoveDirection $move_dir)
{
	if ($move_dir == MoveDirection::MOVE_UP) {
		dir_y = -1;
	}
	if ($move_dir == MoveDirection::MOVE_DOWN) {
		dir_y = 1;
	}
	y_speed = walk_speed * dir_y;

	if ($move_dir == MoveDirection::MOVE_LEFT) {
		dir_x = -1;
	}
	if ($move_dir == MoveDirection::MOVE_RIGHT) {
		dir_x = 1;
	}
	x_speed = walk_speed * dir_x;
}

void Entity::jumpEntity()
{
	if (!falling) {
		dir_y = -1;
		y_speed = dir_y * jump_speed;
		jumping = true;
		falling = true;
	}
}

void Entity::stopHorizontalMove()
{
	dir_x = 0;
	x_speed = 0;
}

void Entity::stopVerticalMove()
{
	dir_y = 0;
	y_speed = 0;
}

void Entity::stopJumpEntity()
{
	if (jumping)
	{
		jumping = false;
		y_speed = 0;
	}
}
