#include "HeroBulletMain.h"

const char* HeroBulletMain::SPRITE_PATH = "./weapon.bmp";

HeroBulletMain::HeroBulletMain()
{
	damage = _DAMAGE_VALUE;
	life_time = _LIFE_SPAN;

	//show_bounds = true;

	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);
}

HeroBulletMain::~HeroBulletMain() {}

void HeroBulletMain::think(Entity* $entity)
{
	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;

	life_time--;

	if (life_time == 0) {
		dead = true;
	}

	Entity* $collide = collide_list->allEntitiesHit(this);

	if ($collide != NULL) {
		if ($collide->type == EntityType::ENEMY) {
			if ($collide->polarity == polarity) {
				$collide->health -= (_DAMAGE_VALUE >> 1);
			}
			else
			{
				$collide->health -= _DAMAGE_VALUE;
			}

			$collide->hit_polarity = polarity;
			dead = true;
		}
	}

	if (wall_left || wall_right) {
		dead = true;
	}
}

void HeroBulletMain::die()
{
	delete this;
}

void HeroBulletMain::fire()
{
	x_speed = _FIRE_SPEED_X;
	y_speed = _FIRE_SPEED_Y;
	dir_x = _FIRE_DIR_X;
	dir_y = _FIRE_DIR_Y;
}