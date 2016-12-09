#ifndef AE_HERO_BULLET_SECONDARY
#define AE_HERO_BULLET_SECONDARY

#include "BulletBase.h"

class HeroBulletSecondary : public BulletBase {
public:
	HeroBulletSecondary();
	~HeroBulletSecondary();

	void think(Entity* $entity);
	void die();

	void fire();

	static const int WIDTH = 32;
	static const int HEIGHT = 32;
	static const char* SPRITE_PATH;

protected:
	const int _DAMAGE_VALUE = 3;
	const int _LIFE_SPAN = 100;

	const int _FIRE_SPEED_X = 25;
	const int _FIRE_SPEED_Y = 0;
	const int _FIRE_DIR_X = 1;
	const int _FIRE_DIR_Y = 1;

	const uint32_t _BOUND_WIDTH = 32;
	const uint32_t _BOUND_HEIGHT = 32;
};

#endif