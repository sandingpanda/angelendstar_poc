#include "HeroBase.h"

HeroBase::HeroBase() {}

HeroBase::~HeroBase() {}

void HeroBase::initHero()
{
	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);

	walk_speed = _WALK_SPEED;
	jump_speed = _JUMP_SPEED;

	scrolling = true;
}

void HeroBase::incrementTimers()
{
	main_timer++;
	secondary_timer++;
	missile_timer++;
	charge_timer++;
}
