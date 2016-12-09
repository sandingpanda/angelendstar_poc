#ifndef AE_PLAYER_BULLET
#define AE_PLAYER_BULLET

#include "EntityList.h"

class BulletBase : public Entity {
public:
	BulletBase();
	~BulletBase(); 

	EntityList* collide_list;

	int damage = 0;
	int life_time = 0;

	static const int WIDTH = 0;
	static const int HEIGHT = 0;

	virtual void fire() = 0;

	static const char* SPRITE_PATH;

protected:
	const int _DAMAGE_VALUE = 0;
	const int _LIFE_SPAN = 0;

	//firing constants
	const int _FIRE_SPEED_X = 0;
	const int _FIRE_SPEED_Y = 0;
	const int _FIRE_DIR_X = 0;
	const int _FIRE_DIR_Y = 0;
};

#endif