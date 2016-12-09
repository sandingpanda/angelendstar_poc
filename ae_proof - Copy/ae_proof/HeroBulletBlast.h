#ifndef AE_HERO_BULLET_BLAST
#define AE_HERO_BULLET_BLAST

#include "BulletBase.h"

class HeroBulletBlast : public BulletBase {
public:
	HeroBulletBlast();
	~HeroBulletBlast();

	void think(Entity* $entity);
	void die();

	void fire();

	static const int WIDTH = 64;
	static const int HEIGHT = 128;
	static const char* SPRITE_PATH;

protected:
	const int _DAMAGE_VALUE = 8;
	const int _LIFE_SPAN = 20;

	const int _FIRE_SPEED_X = 30;
	const int _FIRE_SPEED_Y = 0;
	const int _FIRE_DIR_X = 1;
	const int _FIRE_DIR_Y = 1;

	const uint32_t _BOUND_WIDTH = 64;
	const uint32_t _BOUND_HEIGHT = 128;
};

#endif