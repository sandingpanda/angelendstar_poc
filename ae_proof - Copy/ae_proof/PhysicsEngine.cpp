#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

//set entity list
void PhysicsEngine::setEntityList(EntityList* $entity_list)
{
	if ($entity_list == NULL) {
		printf("PhysicsEngine.setEntityList-> ERROR: INVALID ENTITYLIST\n");
		return;
	}

	_entity_list = $entity_list;

	//?? WHAT DOES THIS DO??
	if (_entity_count == 0) {
		_entity_count = sizeof(_entity_list);
	}
}

void PhysicsEngine::moveAllEntities()
{
	for (int $i = 0; $i < EntityList::MAX_ENTITIES; $i++) {
		Entity* $entity = _entity_list->forEachEntity($i);

		if ($entity != NULL) {
			if ($entity->active) {
				moveEntity($entity);
			}
		}
	}
}

void PhysicsEngine::getEntityCorners(Entity* $entity, uint32_t $x, uint32_t $y)
{
	int $up = (int)floor(($y - $entity->half_height) / Tile::HEIGHT);
	int $down = (int)floor(($y + $entity->half_height - 1) / Tile::HEIGHT);
	int $left = (int)floor(($x - $entity->half_width) / Tile::WIDTH);
	int $right = (int)floor(($x + $entity->half_width - 1) / Tile::WIDTH);

	$entity->ul = current_map->getHit($left, $up);
	$entity->ur = current_map->getHit($right, $up);
	$entity->dl = current_map->getHit($left, $down);
	$entity->dr = current_map->getHit($right, $down);
}

void PhysicsEngine::moveEntity(Entity* $entity)
{
	//PEAKING, FALLING, JUMPING
	if ($entity->falling) {
		if ($entity->y_speed < _MAX_GRAVITY) {
			$entity->y_speed = $entity->y_speed + $entity->fall_speed;
		}
		else
		{
			$entity->y_speed = _MAX_GRAVITY;
		}

		if ($entity->y_speed >= 0) {
			$entity->dir_y = 1;
			$entity->falling = true;
			$entity->jumping = false;
		}
	}

	//IF NOT COLLIDING
	if (!$entity->collide) {
		$entity->x += $entity->x_speed;
		$entity->y += $entity->y_speed;
		return;
	}

	if ($entity->scrolling) {
		//$entity->x_speed += scroll_speed_x * scroll_dir_x;
		//$entity->x_speed += scroll_speed_y * scroll_dir_y;
	}

	//VERTICAL MOTION WALL CHECK
	if (($entity->dir_y == -1) && ($entity->y_speed < 0))
	{
		getEntityCorners($entity, $entity->x, $entity->y + $entity->y_speed);

		if (($entity->ul == Tile::WALK) && ($entity->ur == Tile::WALK))
		{
			$entity->y += $entity->y_speed;
			$entity->wall_up = false;
		}
		else
		{
			int $tile_up = (int)floor((($entity->y + $entity->y_speed) - $entity->half_height) / Tile::HEIGHT);

			$entity->y = (($tile_up + 1)* Tile::HEIGHT) + $entity->half_height;
			//$entity->y = $entity->tile_y * Tile::HEIGHT + $entity->half_height;
			
			$entity->wall_up = true;
			if ($entity->gravity) {
				if ($entity->jumping) {
					$entity->y_speed = 0;
					$entity->dir_y = 0;
					$entity->jumping = false;
					$entity->falling = true;
				}
			}
		}
	}

	if (($entity->dir_y == 1) && ($entity->y_speed > 0))
	{
		getEntityCorners($entity, $entity->x, $entity->y + $entity->y_speed);

		if (($entity->dl == Tile::WALK) && ($entity->dr == Tile::WALK))
		{
			$entity->y += $entity->y_speed;
			$entity->wall_down = false;
		}
		else
		{
			int $tile_down = (int)floor((($entity->y + $entity->y_speed) + $entity->half_height - 1) / Tile::HEIGHT);

			$entity->y = (($tile_down)* Tile::HEIGHT) - $entity->half_height;
			//$entity->y = ($entity->tile_y + 1) * Tile::HEIGHT - $entity->half_height;
			
			$entity->wall_down = true;

			$entity->y_speed = 0;
			$entity->dir_y = 0;
			$entity->jumping = false;
			$entity->falling = false;
		}
	}

	//HORIZONTAL WALL CHECK
	//CHECKING LEFT
	if (($entity->dir_x == -1) && ($entity->x_speed < 0))
	{
		getEntityCorners($entity, $entity->x + $entity->x_speed, $entity->y);

		if (($entity->ul == Tile::WALK) && ($entity->dl == Tile::WALK))
		{
			$entity->x += $entity->x_speed;
			$entity->wall_left = false;

			fallCorner($entity);
		}
		else
		{
			int $left_tile = (int)floor((($entity->x + $entity->x_speed) - $entity->half_width) / Tile::WIDTH);

			$entity->x = ($left_tile + 1) * Tile::WIDTH + $entity->half_width;
			//$entity->x = $entity->tile_x* Tile::WIDTH + $entity->half_width;
			
			$entity->wall_left = true;
		}
	}

	//CHECKING RIGHT
	if (($entity->dir_x == 1) && ($entity->x_speed > 0))
	{
		getEntityCorners($entity, $entity->x + $entity->x_speed, $entity->y);

		if (($entity->ur == Tile::WALK) && ($entity->dr == Tile::WALK))
		{
			$entity->x += $entity->x_speed;
			$entity->wall_right = false;

			fallCorner($entity);
		}
		else
		{
			int $right_tile = (int)floor((($entity->x + $entity->x_speed) + $entity->half_width - 1) / Tile::WIDTH);

			$entity->x = ($right_tile)* Tile::WIDTH - $entity->half_width;
			//$entity->x = ($entity->tile_x + 1) * Tile::WIDTH - $entity->half_width;
			
			$entity->wall_right = true;
		}
	}

	$entity->tile_x = (int)floor($entity->x / Tile::WIDTH);
	$entity->tile_y = (int)floor($entity->y / Tile::HEIGHT);

	$entity->room_x = (int)floor($entity->tile_x / Room::WIDTH);
	$entity->room_y = (int)floor($entity->tile_y / Room::HEIGHT);
}

void PhysicsEngine::fallCorner(Entity* $entity)
{
	getEntityCorners($entity, $entity->x, $entity->y + $entity->half_height);

	if (($entity->dl == Tile::WALK) && ($entity->dr == Tile::WALK))
	{
		if ($entity->gravity) {
			if (!$entity->falling)
			{
				$entity->falling = true;
				$entity->dir_y = 1;
				$entity->y_speed = 0;
			}
		}
	}
}