#include "EnemyJet.h"

const char* EnemyJet::SPRITE_PATH = "./enemy_hover.bmp";

EnemyJet::EnemyJet()
{
	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);

	type = EntityType::ENEMY;
	health = _BASE_HEALTH;

	walk_speed = _WALK_SPEED;
	dir_x = -1;
	gravity = false;

	sprite_x = SPRITE_WIDTH / 2;
	sprite_y = half_height;

	score_value = _SCORE_VALUE;
	polarity = Polarity::NEGATIVE;

	//show_bounds = true;
}

EnemyJet::~EnemyJet() {}

void EnemyJet::initJet()
{
	_bullet_sprite = sprite_list->setSprite(EnemyBullet::SPRITE_PATH_NEGATIVE, "enemy_bullet_neg", EnemyBullet::WIDTH, EnemyBullet::HEIGHT);
}

void EnemyJet::think(Entity* $self)
{
	shoot_timer++;
	time_to_think--;
	current_frame++;

	if (shoot_timer >= FIRE_RATE) {
		fire();
		shoot_timer = 0;
	}

	if (time_to_think <= 0) {
		
		if (move_state == 0)
		{
			dir_x = dir_y = 1;
			move_state = 1;
		}
		else if (move_state == 1)
		{
			dir_x = -1;
			dir_y = 1;
			move_state = 2;
		}
		else if (move_state == 2)
		{
			dir_x = dir_y = -1;
			move_state = 3;
		}
		else
		{
			dir_x = 1;
			dir_y = -1;
			move_state = 0;
		}

		x_speed = _FLY_SPEED * dir_x;
		y_speed = _FLY_SPEED * dir_y;

		time_to_think = THINK_RATE;
	}

	Entity* $collide = entity_list->allEntitiesHit(this);

	if ($collide != NULL) {
		if ($collide->type == EntityType::HERO) {
			if ($collide->damageable) {
				$collide->health -= _TOUCH_DAMAGE;
			}
		}
	}

	if (current_frame == 3) {
		current_frame = 0;
	}

	if (health <= 0) {
		dead = true;
	}

	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;
}

void EnemyJet::fire()
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

EnemyBullet* EnemyJet::createBullet()
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

void EnemyJet::die()
{
	if (hit_polarity == polarity) {
		for (int $n = 0; $n < _BULLETS_ON_DEATH; $n++) {
			EnemyBullet* $bullet = createBullet();

			int $rand_x = std::rand() % _SPREAD_RANGE;
			int $rand_y = std::rand() % _SPREAD_RANGE;
			int $rand_neg_x = std::rand() % 2;
			int $rand_neg_y = std::rand() % 2;

			if ($rand_neg_x == 0) {
				$rand_x *= -1;
			}

			if ($rand_neg_y == 0) {
				$rand_y *= -1;
			}

			$bullet->fire((int)target_hero->x + $rand_x, (int)target_hero->y + $rand_y);
		}
	}

	SFXLibrary::playSFX(SFXSample::EXPLOSION);
}
