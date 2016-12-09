#ifndef AE_ENTITY
#define AE_ENTITY

//SYSTEM
#include "GameRect.h"
#include "Sprite.h"
#include "SFXLibrary.h"

/*==ENTITY ENUMERATIONS==*/
enum class MoveDirection { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };
enum class MoveState { WALKING, JUMPING };
enum class EntityType { HERO, ENEMY, BULLET };
enum class Polarity { POSITIVE, NEGATIVE };

/*==ENTITY CLASS==*/
class Entity {
public:
	//NO EXPLICIT CONSTRUCTOR; DEPENDENT ON DESCENDANT CLASSES
	void reset();

	//LIST VARIABLES
	bool active;
	char name[25];
	EntityType type;

	//LOCATION VARIABLES
	uint32_t x;
	uint32_t y;
	int dir_x, dir_y;
	uint32_t room_x, room_y;
	uint32_t tile_x, tile_y;

	//PHYSICS VARIABLES
	bool gravity = true;
	int x_speed;
	int y_speed;

	bool falling = false;
	bool jumping = false;
	bool collide = true;

	bool scrolling = false;

	int walk_speed = 0;
	int jump_speed = 0;
	int fall_speed = 0;

	//BOUNDING BOX VARIABLES
	GameRect bound_rect;

	//MAP VARIABLES
	uint32_t half_width, half_height;
	uint32_t ul, ur, dl, dr;

	bool wall_left, wall_right, wall_up, wall_down;

	//THINK VARIABLES
	virtual void think(Entity* $self);
	int time_to_think = 0;

	//GRAPHICS VARIABLES
	Sprite* sprite;
	uint32_t current_frame = 0;
	GameRect draw_rect;
	bool show_bounds = false;

	int sprite_x = 0;
	int sprite_y = 0;
	float scale = 1.0;
	double rotation = 0.0;

	//HEALTH VALUES
	int health = 0;
	int absorb = 0;
	bool damageable = true;
	Polarity polarity = Polarity::POSITIVE;
	Polarity hit_polarity = Polarity::POSITIVE;

	//SCORE VALUES
	int score_value = 0;

	//DEPENDENCY VARIABLES
	Entity* parent;
	bool dead = false;

	//GENERIC MOVEMENT FUNCTIONS
	void moveEntity(MoveDirection $move_dir);
	void jumpEntity();
	void stopHorizontalMove();
	void stopVerticalMove();
	void stopJumpEntity();

	//GENERIC FUNCTIONS
	void initBounds(uint32_t $bound_w, uint32_t $bound_h);
	virtual void die();

	static const char* SPRITE_PATH;

protected:
	const int _WALK_SPEED = 0;
	const int _JUMP_SPEED = 0;

	//bounding box constants
	const uint32_t _BOUND_WIDTH = 0;
	const uint32_t _BOUND_HEIGHT = 0;
};

#endif