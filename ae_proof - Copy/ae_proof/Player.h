#ifndef AE_PLAYER
#define AE_PLAYER

//C++
#include <vector>
#include <string>
#include <stdint.h>

//SYSTEM
#include "EntityList.h"
#include "SpriteList.h"
#include "HeroOne.h"
#include "HeroTwo.h"

class Player {
public:
	Player();
	~Player();

	int health_1, health_2 = 0;
	int charge, sacrifice = 0;

	bool update_health = false;
	bool update_charge = false;
	bool firing_charge = false;

	void initialize(EntityList* $entity_list, SpriteList* $sprite_list);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown(); 

	void stopMoveHorizontal();
	void stopMoveVertical();
	void stopJump();

	void shootMain();
	void shootCharge();

	void swapPlayers();
	
	void updateStatus();
	void updatePositions();
	int getPositionX();
	int getPositionY();

	//TESTING
	void moveJump();

private:
	static const int _MOVE_BUFFER_SIZE = 18;

	const int _MAX_CHARGE = 100;
	const int _MAX_HEALTH = 100;
	const int _MAX_SACRIFICE = 200;
	const int _MAX_RECOVERY = 105;

	HeroOne _hero_one;
	HeroTwo _hero_two;

	HeroBase* _active_hero;
	HeroBase* _sub_hero;

	int _move_buffer[_MOVE_BUFFER_SIZE][2];
	int _buffer_current = 0;
	int _buffer_next = 0;
	bool _moving_h = false;
	bool _moving_v = false;

	bool _switching = false;
	bool _two_active = false;
	bool _player_locked = false;
	bool _recovering = false;
	int _recovery_time = 0;

	EntityList* _entity_list;
	SpriteList* _sprite_list;

	void initBuffer();
	void addToBuffer();
};

#endif