#include "EnemyBoss.h"

const char* EnemyBoss::SPRITE_PATH = "./boss.bmp";

EnemyBoss::EnemyBoss()
{
	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);

	type = EntityType::ENEMY;
	health = _BASE_HEALTH;

	walk_speed = _WALK_SPEED;
	dir_y = 1;
	gravity = false;
	fall_speed = 1;

	sprite_x = half_width;
	sprite_y = half_height;

	score_value = _SCORE_VALUE;
	polarity = Polarity::POSITIVE;

	show_bounds = true;

}

EnemyBoss::~EnemyBoss() {}

void EnemyBoss::initBoss()
{
	_bullet_sprite = sprite_list->setSprite(EnemyBullet::SPRITE_PATH, "enemy_bullet", EnemyBullet::WIDTH, EnemyBullet::HEIGHT);
}

void EnemyBoss::think(Entity* $self)
{
	shoot_timer++;
	time_to_think--;
	_time_to_attack--;

	if (_attack_state == 1)
	{
		if (shoot_timer >= FIRE_RATE) {
			fire();
			shoot_timer = 0;
		}
	}
	
	if (time_to_think <= 0) {
		if (dir_y == 1) {
			moveEntity(MoveDirection::MOVE_UP);
		}
		else if (dir_y == -1) {
			moveEntity(MoveDirection::MOVE_DOWN);
		}
		time_to_think = THINK_RATE;
	}

	if (_time_to_attack <= 0) {
		if (_attack_state == 0) {
			_attack_state = 1;
		}
		else
		{
			_attack_state = 0;	
		}
		_time_to_attack = ATTACK_RATE;
	}

	Entity* $collide = entity_list->allEntitiesHit(this);

	if ($collide != NULL) {
		if ($collide->type == EntityType::HERO) {
			if ($collide->damageable) {
				$collide->health -= _TOUCH_DAMAGE;
			}
		}
	}

	if (health <= 0) {
		dead = true;
	}

	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;
}

void EnemyBoss::fire()
{
	if (target_hero == NULL || !target_hero->damageable) {
		for (int $n = 0; $n < EntityList::MAX_ENTITIES; $n++) {
			Entity* $entity = entity_list->forEachEntity($n);
			if ($entity->type == EntityType::HERO && $entity->damageable) {
				target_hero = $entity;
				break;
			}
		}
	}

	EnemyBullet* $bullet = createBullet();

	$bullet->fire(target_hero->x, target_hero->y);
}

EnemyBullet* EnemyBoss::createBullet()
{
	EnemyBullet* $bullet = new EnemyBullet();

	$bullet->sprite = _bullet_sprite;
	entity_list->addEntity($bullet);
	$bullet->collide_list = entity_list;

	//$bullet_main.parent = this;
	$bullet->polarity = polarity;
	$bullet->x = x;
	$bullet->y = y;
	$bullet->sprite_x = $bullet->half_width;
	$bullet->sprite_y = $bullet->half_height;

	return $bullet;
}

void EnemyBoss::die()
{
}
