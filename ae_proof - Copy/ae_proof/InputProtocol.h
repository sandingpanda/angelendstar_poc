#ifndef AE_INPUT_PROTOCOL
#define	AE_INPUT_PROTOCOL

#include <SDL.h>

class InputProtocol {
public:
	InputProtocol();
	~InputProtocol();

	//triggers
	bool move_up, move_down, move_left, move_right = false;
	bool confirm, cancel = false;
	bool shoot, jump = false;
	bool special_1, special_2 = false;

	//key configuration
	SDL_Scancode key_move_up, key_move_down, key_move_left, key_move_right;
	SDL_Scancode key_confirm, key_cancel;
	SDL_Scancode key_shoot, key_jump;
	SDL_Scancode key_special1, key_special2;

	//controller configuration

	//default key configuration codes
	static const SDL_Scancode DEFAULT_UP = SDL_SCANCODE_UP;
	static const SDL_Scancode DEFAULT_DOWN = SDL_SCANCODE_DOWN;
	static const SDL_Scancode DEFAULT_LEFT = SDL_SCANCODE_LEFT;
	static const SDL_Scancode DEFAULT_RIGHT = SDL_SCANCODE_RIGHT;

	static const SDL_Scancode DEFAULT_CONFIRM = SDL_SCANCODE_RETURN;
	static const SDL_Scancode DEFAULT_CANCEL = SDL_SCANCODE_ESCAPE;

	static const SDL_Scancode DEFAULT_SHOOT = SDL_SCANCODE_SPACE;
	static const SDL_Scancode DEFAULT_JUMP = SDL_SCANCODE_LCTRL;

	static const SDL_Scancode DEFAULT_SPECIAL1 = SDL_SCANCODE_Z;
	static const SDL_Scancode DEFAULT_SPECIAL2 = SDL_SCANCODE_X;

private:

};

#endif