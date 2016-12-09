#include "Player.h"

Player::Player() { }

Player::~Player() {}

void Player::initialize(EntityList* $entity_list, SpriteList* $sprite_list)
{	
	_hero_one.reset();
	_hero_two.reset();
	
	_entity_list = $entity_list;
	_sprite_list = $sprite_list;

	_entity_list->addEntity(&_hero_one);
	_entity_list->addEntity(&_hero_two);

	_hero_one.entity_list = _entity_list;
	_hero_one.sprite_list = _sprite_list;

	_hero_two.entity_list = _entity_list;
	_hero_two.sprite_list = _sprite_list;

	std::string $hero_1(HeroOne::SPRITE_PATH);
	_hero_one.sprite = _sprite_list->setSprite($hero_1, "hero_one", _hero_one.SPRITE_WIDTH, _hero_one.SPRITE_HEIGHT);
	_hero_one.initHero();

	std::string $hero_2(HeroTwo::SPRITE_PATH);
	_hero_two.sprite = _sprite_list->setSprite($hero_2, "hero_two", _hero_two.SPRITE_WIDTH, _hero_two.SPRITE_HEIGHT);
	_hero_two.initHero();

	_active_hero = &_hero_one;
	_sub_hero = &_hero_two;
	_sub_hero->damageable = false;

	_hero_one.health = _MAX_HEALTH;
	_hero_two.health = _MAX_HEALTH;

	_hero_one.polarity = Polarity::POSITIVE;
	_hero_two.polarity = Polarity::NEGATIVE;

	health_1 = _hero_one.health;
	health_2 = _hero_two.health;

	//TESTING VALUES
	//_hero_one.gravity = true;
	_hero_one.x = 256;
	_hero_one.y = 256;
	_hero_one.sprite_x = 128 - _hero_one.bound_rect.w;
	_hero_one.sprite_y = 128 - _hero_one.bound_rect.h;

	_hero_two.x = 256;
	_hero_two.y = 256;
	_hero_two.sprite_x = 128 - _hero_two.bound_rect.w;
	_hero_two.sprite_y = 128 - _hero_two.bound_rect.h;

	//DEBUG VALUES
	_hero_one.show_bounds = true;
	_hero_two.show_bounds = true;
	//collide = false;

	initBuffer();
}

//initialize the move buffer
void Player::initBuffer()
{
	for (int $i = 0; $i < _MOVE_BUFFER_SIZE; $i++) {
		_move_buffer[$i][0] = _active_hero->x;
		_move_buffer[$i][1] = _active_hero->y;
	}

	_buffer_next = 0;
	_buffer_current = 1;
}

//moving active player
void Player::moveLeft()
{
	_active_hero->moveEntity(MoveDirection::MOVE_LEFT);
	_moving_h = true;
}

void Player::moveRight()
{
	_active_hero->moveEntity(MoveDirection::MOVE_RIGHT);
	_moving_h = true;
}

void Player::moveUp()
{
	_active_hero->moveEntity(MoveDirection::MOVE_UP);
	_moving_v = true;
}

void Player::moveDown()
{
	_active_hero->moveEntity(MoveDirection::MOVE_DOWN);
	_moving_v = true;
}

void Player::moveJump()
{
	_active_hero->jumpEntity();
}

void Player::stopMoveHorizontal()
{
	_active_hero->stopHorizontalMove();
	_moving_h = false;
}

void Player::stopMoveVertical()
{
	_active_hero->stopVerticalMove();
	_moving_v = false;
}

void Player::stopJump()
{
	_active_hero->stopJumpEntity();
}

void Player::swapPlayers()
{
	if (firing_charge || _switching || _player_locked) {
		return;
	}

	_recovering = false;
	_switching = true;

	int $sub_x = _sub_hero->x;
	int $sub_y = _sub_hero->y;

	stopMoveHorizontal();
	stopMoveVertical(); 

	_sub_hero->x = _active_hero->x;
	_sub_hero->y = _active_hero->y;

	if (_two_active) {
		_two_active = false;

		_active_hero = &_hero_one;
		_sub_hero = &_hero_two;

		_active_hero->polarity = Polarity::POSITIVE;
	}
	else
	{
		_two_active = true;
		_active_hero = &_hero_two;
		_sub_hero = &_hero_one;

		_active_hero->polarity = Polarity::NEGATIVE;
	}

	_sub_hero->x = $sub_x;
	_sub_hero->y = $sub_y;
	_sub_hero->damageable = false;
	_active_hero->damageable = true;
	_active_hero->sprite->visible = true;
	_sub_hero->sprite->visible = true;
	_sub_hero->polarity = _active_hero->polarity;

	_switching = false;
}

void Player::updateStatus()
{
	if (_recovering) {
		if (_active_hero->sprite->visible) {
			_active_hero->sprite->visible = false;
		}
		else
		{
			_active_hero->sprite->visible = true;
		}
		
		_recovery_time--;

		if (_recovery_time <= 0) {
			_recovering = false;
			_active_hero->sprite->visible = true;
			_active_hero->damageable = true;
		}
	}
	
	if (_hero_one.health != health_1) {
		if (_recovering) {
			_hero_one.health = health_1;
		}
		else
		{
			health_1 = _hero_one.health;
			update_health = true;
			_recovery_time = _MAX_RECOVERY;
			_recovering = true;
		}
		
	}

	if (_hero_two.health != health_2) {
		if (_recovering) {
			_hero_two.health = health_2;
		}
		else
		{
			health_2 = _hero_two.health;
			update_health = true;
			_recovery_time = _MAX_RECOVERY;
			_recovering = true;
		}
		
	}
	

	if (!_player_locked) {
		if (_active_hero->health <= 0) {
			swapPlayers();
			_player_locked = true;

			if (_sub_hero == &_hero_one) {
				_hero_one.active = false;
			}
			else
			{
				_hero_two.active = false;
			}
		}
	}
	else if (_player_locked)
	{
		if (_active_hero->health <= 0) {
			printf("BOTH HEROES HAVE DIED\n");
		}
	}

	if (_active_hero->absorb > 0) {
		charge += _active_hero->absorb;

		if (_player_locked) {
			if (charge > _MAX_CHARGE) {
				sacrifice += (charge - _MAX_CHARGE);
				charge = _MAX_CHARGE;

				if (_active_hero == &_hero_one) {
					_hero_two.health = sacrifice;
				}
				else
				{
					_hero_one.health = sacrifice;
				}
			}
			else
			{
				update_charge = true;
			}
		}
		else
		{
			if (charge > _MAX_CHARGE) {
				charge = _MAX_CHARGE;
			}
			else
			{
				update_charge = true;
			}
		}

		_active_hero->absorb = 0;
	}

	if (sacrifice >= _MAX_SACRIFICE) {
		sacrifice = 0;
		_sub_hero->health = _MAX_HEALTH;
		_sub_hero->active = true;
		_player_locked = false;
	}

	if (firing_charge) {
		if (_active_hero->charge_ammo <= 0) {
			firing_charge = false;
		}
	}
}

void Player::updatePositions()
{
	if (_switching) {
		return;
	}

	if (_moving_h || _moving_v) {
		_sub_hero->x = _move_buffer[_buffer_current][0];
		_sub_hero->y = _move_buffer[_buffer_current][1];

		_move_buffer[_buffer_next][0] = _active_hero->x;
		_move_buffer[_buffer_next][1] = _active_hero->y;

		_buffer_current++;
		_buffer_next++;

		if (_buffer_next == _MOVE_BUFFER_SIZE) {
			_buffer_next = 0;
		}

		if (_buffer_current == _MOVE_BUFFER_SIZE) {
			_buffer_current = 0;
		}
		//printf("x %i, y %i\n", _sub_hero->x, _sub_hero->y);
	}
}

//shooting with active player
void Player::shootMain()
{
	if (!firing_charge) {
		_active_hero->shootMainBullet();
		_active_hero->shootMissile();
	}
	
	if (!_player_locked) {
		_sub_hero->shootSecondaryBullet();
	}
}

void Player::shootCharge()
{
	if (!firing_charge) {
		firing_charge = true;
		_active_hero->charge_ammo = charge;
		charge = 0;
		update_charge = true;

		//_active_hero->shootChargeWeapon();
	}
}

//get active hero coordinates
int Player::getPositionX()
{
	return _active_hero->x;
}

int Player::getPositionY()
{
	return _active_hero->y;
}