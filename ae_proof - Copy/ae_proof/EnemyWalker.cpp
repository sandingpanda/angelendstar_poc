#include "EnemyWalker.h"

const char* EnemyWalker::SPRITE_PATH = "./crawler.bmp";

EnemyWalker::EnemyWalker()
{
	initBounds(_BOUND_WIDTH, _BOUND_HEIGHT);

	type = EntityType::ENEMY;
	health = _BASE_HEALTH;

	walk_speed = _WALK_SPEED;
	dir_x = -1;
	gravity = true;
	fall_speed = 1;

	sprite_x = half_width;
	sprite_y = half_height;

	score_value = _SCORE_VALUE;
	polarity = Polarity::POSITIVE;

	//show_bounds = true;
}

EnemyWalker::~EnemyWalker() {}

void EnemyWalker::initWalker()
{
	_bullet_sprite = sprite_list->setSprite(EnemyBullet::SPRITE_PATH, "enemy_bullet", EnemyBullet::WIDTH, EnemyBullet::HEIGHT);
}

void EnemyWalker::think(Entity* $self)
{
	shoot_timer++;
	time_to_think--;
	current_frame++;

	if (shoot_timer >= FIRE_RATE) {
		fire();
		shoot_timer = 0;
	}

	Entity* $collide = entity_list->allEntitiesHit(this);

	if ($collide != NULL) {
		if ($collide->type == EntityType::HERO) {
			if ($collide->damageable) {
				$collide->health -= _TOUCH_DAMAGE;
			}
		}
	}

	if (time_to_think <= 0) {
		if (dir_x == 1) {
			moveEntity(MoveDirection::MOVE_LEFT);
			current_frame = 0;
		} else if (dir_x == -1) {
			moveEntity(MoveDirection::MOVE_RIGHT);
			current_frame = 9;
		}
		time_to_think = THINK_RATE;
	}

	if (health <= 0) {
		dead = true;
	}

	if (current_frame == 9) {
		current_frame = 0;
	}

	if (current_frame == 18) {
		current_frame = 9;
	}

	bound_rect.x = x - half_width;
	bound_rect.y = y - half_height;
}

void EnemyWalker::fire()
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

EnemyBullet* EnemyWalker::createBullet()
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

void EnemyWalker::die()
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
