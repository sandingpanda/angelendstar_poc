#include "BulletBase.h"

BulletBase::BulletBase()
{
	type = EntityType::BULLET;
	damageable = false;
	gravity = false;
}

BulletBase::~BulletBase() {}
