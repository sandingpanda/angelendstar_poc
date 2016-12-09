#ifndef AE_HERO_ONE
#define AE_HERO_ONE

#include "HeroBase.h"
#include "HeroBulletMain.h"
#include "HeroBulletSecondary.h"
#include "HeroBulletBlast.h"

class HeroOne : public HeroBase {
public:
	HeroOne();
	~HeroOne();

	void initHero();

	void shootMainBullet();
	void shootSecondaryBullet();
	void shootMissile();
	void shootChargeWeapon();

	void think(Entity* $entity);

	static const char* SPRITE_PATH;

protected:
	const int _MAIN_FIRERATE = 6;
	const int _SECONDARY_FIRERATE = 10;
	const int _MISSILE_FIRERATE = 39;
	const int _CHARGE_FIRERATE = 4;
	const int _CHARGE_DEPLETE = 5;
};

#endif