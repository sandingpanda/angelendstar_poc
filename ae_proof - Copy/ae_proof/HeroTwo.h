#ifndef AE_HERO_TWO
#define AE_HERO_TWO

#include "HeroBase.h"
#include "HeroBulletMain.h"
#include "HeroBulletSecondary.h"
#include "HeroBulletBlade.h"

class HeroTwo : public HeroBase {
public:
	HeroTwo();
	~HeroTwo();

	void initHero();

	void shootMainBullet();
	void shootSecondaryBullet();
	void shootMissile();
	void shootChargeWeapon();

	void think(Entity* $entity);

	static const char* SPRITE_PATH;

protected:
	const int _MAIN_FIRERATE = 12;
	const int _SECONDARY_FIRERATE = 15;
	const int _MISSILE_FIRERATE = 30;
	const int _CHARGE_FIRERATE = 4;
	const int _CHARGE_DEPLETE = 12;
};

#endif