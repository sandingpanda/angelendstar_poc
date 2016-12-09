#ifndef AE_ENEMY_BOSS
#define AE_ENEMY_BOSS

#include "SpriteList.h"
#include "EntityList.h"
#include "EnemyBullet.h"

class EnemyBoss : public Entity {
public:
	EnemyBoss();
	~EnemyBoss();
	void initBoss();

	void think(Entity* $self);
	void fire();
	void die();

	EnemyBullet* createBullet();

	Entity* target_hero;

	//entity registry list
	EntityList* entity_list;
	SpriteList* sprite_list;

	static const char* SPRITE_PATH;
	static const uint32_t SPRITE_WIDTH = 256;
	static const uint32_t SPRITE_HEIGHT = 384;

	const int FIRE_RATE = 10;
	const int THINK_RATE = 100;
	const int ATTACK_RATE = 75;

protected:
	int shoot_timer = 0;
	int _attack_state = 0;
	int _time_to_attack = 0;

	Sprite* _bullet_sprite;

	const int _WALK_SPEED = 2;
	const int _BASE_HEALTH = 500;
	const int _SCORE_VALUE = 1000;
	const int _TOUCH_DAMAGE = 20;

	const uint32_t _BOUND_WIDTH = 128;
	const uint32_t _BOUND_HEIGHT = 128;
};


#endif