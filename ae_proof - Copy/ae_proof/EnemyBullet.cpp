#include "EnemyBullet.h"

const char* EnemyBullet::SPRITE_PATH = "./enemy_weapon.bmp";
const char* EnemyBullet::SPRITE_PATH_NEGATIVE = "./enemy_weapon2.bmp";

EnemyBullet::EnemyBullet()
{
	damage = _DAMAGE_VALUE;
	life_time = _LIFE_SPAN;

	//show_bounds = true;

	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);
}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::think(Entity* $entity)
{
	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;

	life_time--;

	if (life_time == 0) {
		dead = true;
	}

	Entity* $collide = collide_list->allEntitiesHit(this);

	if ($collide != NULL) {
		if ($collide->type == EntityType::HERO) {
			if ($collide->damageable) {
				if ($collide->polarity != polarity) {
					$collide->health -= _DAMAGE_VALUE;
				}
				else if ($collide->polarity == polarity)
				{
					$collide->absorb += _DAMAGE_VALUE;
				}
			}
			dead = true;
		}
	}

	if (wall_left || wall_right) {
		dead = true;
	}
	if (wall_up) {
		dead = true;
	}
	if (wall_down) {
		dead = true;
	}

	if (current_frame == 0) {
		current_frame = 1;
	}
	else
	{
		current_frame = 0;
	}
}

void EnemyBullet::die()
{
	delete this;
}

void EnemyBullet::fire()
{
	dir_x = _FIRE_DIR_X;
	dir_y = _FIRE_DIR_Y;
	x_speed = _FIRE_SPEED_X * dir_x;
	y_speed = _FIRE_SPEED_Y * dir_y;
}

void EnemyBullet::fire(int $target_x, int $target_y)
{
	float $x_diff = (int)x - $target_x;
	float $y_diff = (int)y - $target_y;

	float $tan = abs($y_diff / $x_diff);
	float $angle = atan($tan);

	if ($x_diff > 0) {
		dir_x = -1;
	}
	else
	{
		dir_x = 1;
	}

	if ($y_diff > 0) {
		dir_y = -1;
	}
	else
	{
		dir_y = 1;
	}

	x_speed = (int)(cos($angle) * _FIRE_SPEED * dir_x);
	y_speed = (int)(sin($angle) * _FIRE_SPEED * dir_y);

	//printf("final speeds: %i, %i\n", x_speed, y_speed);
}