#ifndef AE_ENEMY_JET
#define AE_ENEMY_JET

#include "SpriteList.h"
#include "EntityList.h"
#include "EnemyBullet.h"

class EnemyJet : public Entity {
public:
	EnemyJet();
	~EnemyJet();
	void initJet();

	void think(Entity* $self);
	void fire();
	void die();

	EnemyBullet* createBullet();

	//entity registry list
	EntityList* entity_list;
	SpriteList* sprite_list;

	Entity* target_hero;

	static const char* SPRITE_PATH;
	static const uint32_t SPRITE_WIDTH = 96;
	static const uint32_t SPRITE_HEIGHT = 64;

	const int FIRE_RATE = 25;
	const int THINK_RATE = 100;

protected:
	int shoot_timer = 0;
	int move_state = 0;

	Sprite* _bullet_sprite;

	const int _FLY_SPEED = 1;
	const int _BASE_HEALTH = 20;
	const int _SCORE_VALUE = 50;
	const int _TOUCH_DAMAGE = 6;

	const int _BULLETS_ON_DEATH = 8;
	const int _SPREAD_RANGE = 35;

	const uint32_t _BOUND_WIDTH = 64;
	const uint32_t _BOUND_HEIGHT = 64;
};


#endif