#include "HeroBulletBlast.h"

const char* HeroBulletBlast::SPRITE_PATH = "./chargeweapon1.bmp";

HeroBulletBlast::HeroBulletBlast()
{
	damage = _DAMAGE_VALUE;
	life_time = _LIFE_SPAN;
	
	collide = false;

	//show_bounds = true;

	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);
}

HeroBulletBlast::~HeroBulletBlast() {}

void HeroBulletBlast::think(Entity* $entity)
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
			dead = true;
		}
	}

	if (current_frame == 0) {
		current_frame = 1;
	}
	else
	{
		current_frame = 0;
	}
}

void HeroBulletBlast::die()
{
	delete this;
}

void HeroBulletBlast::fire()
{
	x_speed = _FIRE_SPEED_X;
	y_speed = _FIRE_SPEED_Y;
	dir_x = _FIRE_DIR_X;
	dir_y = _FIRE_DIR_Y;
}