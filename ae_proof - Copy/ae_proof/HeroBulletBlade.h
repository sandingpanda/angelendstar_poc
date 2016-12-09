#ifndef AE_HERO_BULLET_BLADE
#define AE_HERO_BULLET_BLADE

#include <math.h>

#include "BulletBase.h"

class HeroBulletBlade : public BulletBase {
public:
	HeroBulletBlade();
	~HeroBulletBlade();

	void think(Entity* $entity);
	void die();

	void fire();

	static const int WIDTH = 128;
	static const int HEIGHT = 128;
	static const char* SPRITE_PATH;

protected:
	float angle = 0;

	const int _RADIUS = 128;
	const double _ANGLE_ADD = 0.18;

	const int _DAMAGE_VALUE = 14;
	const int _LIFE_SPAN = 65;
	
	const uint32_t _BOUND_WIDTH = 128;
	const uint32_t _BOUND_HEIGHT = 128;
};

#endif