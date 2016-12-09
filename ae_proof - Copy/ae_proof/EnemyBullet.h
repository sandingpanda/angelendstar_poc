#ifndef AE_ENEMY_BULLET
#define AE_ENEMY_BULLET

#include <math.h>

#include "BulletBase.h"

class EnemyBullet : public BulletBase {
public:
	EnemyBullet();
	~EnemyBullet();

	void think(Entity* $entity);
	void die();

	void fire();
	void fire(int $target_x = 0, int $target_y = 0);

	static const int WIDTH = 16;
	static const int HEIGHT = 16;
	static const char* SPRITE_PATH;
	static const char* SPRITE_PATH_NEGATIVE;

protected:
	const int _DAMAGE_VALUE = 5;
	const int _LIFE_SPAN = 100;
	const int _FIRE_SPEED = 6;

	const int _FIRE_SPEED_X = 6;
	const int _FIRE_SPEED_Y = 6;
	const int _FIRE_DIR_X = -1;
	const int _FIRE_DIR_Y = -1;

	const uint32_t _BOUND_WIDTH = 16;
	const uint32_t _BOUND_HEIGHT = 16;
};

#endif