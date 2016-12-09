#include "HeroBulletBlade.h"

const char* HeroBulletBlade::SPRITE_PATH = "./chargeweapon2.bmp";

HeroBulletBlade::HeroBulletBlade()
{
	damage = _DAMAGE_VALUE;
	life_time = _LIFE_SPAN;

	collide = false;

	//show_bounds = true;

	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);
}

HeroBulletBlade::~HeroBulletBlade() {}

void HeroBulletBlade::think(Entity* $entity)
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

	x = (int)(_RADIUS * cos(angle) + parent->x);
	y = (int)(_RADIUS * sin(angle) + parent->y);
	angle += _ANGLE_ADD;
}

void HeroBulletBlade::die()
{
	delete this;
}

void HeroBulletBlade::fire()
{
	x = parent->x + _RADIUS;
	y = parent->y;
	angle = 0;
}