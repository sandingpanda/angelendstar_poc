#ifndef AE_ENTITY_HERO
#define AE_ENTITY_HERO

#include "SpriteList.h"
#include "EntityList.h"

class HeroBase : public Entity {
public:
	HeroBase();
	~HeroBase();

	//sprite variables
	static const std::string SPRITE_SHEET;
	static const uint32_t SPRITE_WIDTH = 128;
	static const uint32_t SPRITE_HEIGHT = 128;

	//weapons values
	int main_timer = 0;
	int secondary_timer = 0;
	int missile_timer = 0;
	int charge_timer = 0;
	int charge_ammo = 0;

	//entity registry list
	EntityList* entity_list;
	SpriteList* sprite_list;

	void initHero();

	//weapon functions
	void incrementTimers();
	virtual void shootMainBullet() = 0;
	virtual void shootSecondaryBullet() = 0;
	virtual void shootMissile() = 0;
	virtual void shootChargeWeapon() = 0;

protected:
	const int _MAIN_FIRERATE = 0;
	const int _SECONDARY_FIRERATE = 0;
	const int _MISSILE_FIRERATE = 0;
	const int _CHARGE_FIRERATE = 0;
	const int _CHARGE_DEPLETE = 0;

	//movement constants
	const int _WALK_SPEED = 7;
	const int _JUMP_SPEED = 32;

	//bounding box constants
	const uint32_t _BOUND_WIDTH = 60;
	const uint32_t _BOUND_HEIGHT = 60;

	//internal sprite data
	Sprite* _main_sprite;
	Sprite* _secondary_sprite;
	Sprite* _missile_sprite;
	Sprite* _charge_sprite;
};

#endif