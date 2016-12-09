#include "InputProtocol.h"

InputProtocol::InputProtocol()
{
	key_move_up = DEFAULT_UP;
	key_move_down = DEFAULT_DOWN;
	key_move_left = DEFAULT_LEFT;
	key_move_right = DEFAULT_RIGHT;

	key_confirm = DEFAULT_CONFIRM;
	key_cancel = DEFAULT_CANCEL;

	key_shoot = DEFAULT_SHOOT;
	key_jump = DEFAULT_JUMP;

	key_special1 = DEFAULT_SPECIAL1;
	key_special2 = DEFAULT_SPECIAL2;
}

InputProtocol::~InputProtocol() {}
