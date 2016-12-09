#include "HeroOne.h"

const char* HeroOne::SPRITE_PATH = "./rei.bmp";

HeroOne::HeroOne() { }

HeroOne::~HeroOne() {}

void HeroOne::initHero()
{
	_main_sprite = sprite_list->setSprite(HeroBulletMain::SPRITE_PATH, "hero_one_main", HeroBulletMain::WIDTH, HeroBulletMain::HEIGHT);
	_secondary_sprite = sprite_list->setSprite(HeroBulletSecondary::SPRITE_PATH, "hero_one_secondary", HeroBulletSecondary::WIDTH, HeroBulletSecondary::HEIGHT);
	_charge_sprite = sprite_list->setSprite(HeroBulletBlast::SPRITE_PATH, "hero_one_charge", HeroBulletBlast::WIDTH, HeroBulletBlast::HEIGHT);

	HeroBase::initHero();
}

void HeroOne::shootMainBullet()
{
	if (main_timer >= _MAIN_FIRERATE) {
		
		HeroBulletMain* $bullet_main = new HeroBulletMain();
		
		$bullet_main->sprite = _main_sprite;
		entity_list->addEntity($bullet_main);
		$bullet_main->collide_list = entity_list;

		//$bullet_main.parent = this;
		$bullet_main->polarity = polarity;
		$bullet_main->x = x;
		$bullet_main->y = y;
		$bullet_main->sprite_x = $bullet_main->half_width;
		$bullet_main->sprite_y = $bullet_main->half_height;
		$bullet_main->current_frame = 0;
		$bullet_main->fire();

		SFXLibrary::playSFX(SFXSample::SHOOT_ONE);

		main_timer = 0;
	}	
}

void HeroOne::shootSecondaryBullet()
{
	if (secondary_timer >= _SECONDARY_FIRERATE) {

		HeroBulletSecondary* $bullet_main = new HeroBulletSecondary();

		$bullet_main->sprite = _secondary_sprite;
		entity_list->addEntity($bullet_main);
		$bullet_main->collide_list = entity_list;

		//$bullet_main.parent = this;
		$bullet_main->polarity = polarity;
		$bullet_main->x = x;
		$bullet_main->y = y;
		$bullet_main->sprite_x = $bullet_main->half_width;
		$bullet_main->sprite_y = $bullet_main->half_height;
		$bullet_main->current_frame = 1;
		$bullet_main->fire();

		secondary_timer = 0;
	}
}

void HeroOne::shootMissile()
{
	missile_timer = 0;
}

void HeroOne::shootChargeWeapon()
{
	if (charge_timer >= _CHARGE_FIRERATE) {

		charge_ammo -= _CHARGE_DEPLETE;

		if (charge_ammo <= 0) {
			charge_ammo = 0;
		}

		HeroBulletBlast* $blast = new HeroBulletBlast();

		$blast->sprite = _charge_sprite;
		entity_list->addEntity($blast);
		$blast->collide_list = entity_list;

		//$bullet_main.parent = this;
		$blast->polarity = polarity;
		$blast->x = x;
		$blast->y = y;
		$blast->sprite_x = $blast->half_width;
		$blast->sprite_y = $blast->half_height;
		$blast->fire();

		SFXLibrary::playSFX(SFXSample::BLAST);

		charge_timer = 0;
	}
}

void HeroOne::think(Entity* $self)
{
	if (current_frame == 20) {
		current_frame = 10;
	}

	current_frame++;

	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;

	if (charge_ammo != 0) {
		shootChargeWeapon();
	}

	HeroBase::incrementTimers();
}
