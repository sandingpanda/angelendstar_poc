#ifndef AE_INPUT_INTERFACE
#define AE_INPUT_INTERFACE

//C++
#include <stdint.h>
//SDL
#include <SDL.h>
//system
#include "InputProtocol.h"

class InputInterface {
public:
	InputInterface();
	~InputInterface();

	//controller open/close
	bool openControllers();
	void closeControllers();

	//player input protocols
	InputProtocol* player1_protocol, player2_protocol;

	//on lapse read functions
	void readEvent(SDL_Event* $event);
	void readSDLKeyboard();

private:
	static const uint32_t _MAX_CONTROLLERS = 16;

	uint32_t _num_controllers = 0;

	SDL_GameController* _controller_list[_MAX_CONTROLLERS];

};

#endif