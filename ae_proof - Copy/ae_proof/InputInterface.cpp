#include "InputInterface.h"

InputInterface::InputInterface()
{
	for (uint32_t $n = 0; $n < _num_controllers; $n++) {
		SDL_GameControllerClose(_controller_list[$n]);
		_controller_list[$n] = NULL;
	}

}

InputInterface::~InputInterface()
{
	//closeControllers();
}

//open/close controllers
bool InputInterface::openControllers()
{
	uint32_t $num_controllers = SDL_NumJoysticks();

	if ($num_controllers > _MAX_CONTROLLERS) {
		$num_controllers = _MAX_CONTROLLERS;
	}

	for (uint32_t $i = 0; $i < $num_controllers; $i++) {
		if (SDL_IsGameController($i)) {
			_controller_list[$i] = SDL_GameControllerOpen($i);
			_num_controllers++;
		}
	}

	if (_num_controllers == 0) {
		return false;
	}

	return true;
}

void InputInterface::closeControllers()
{
	for (uint32_t $n = 0; $n < _num_controllers; $n++) {
		SDL_GameControllerClose(_controller_list[$n]);
		_controller_list[$n] = NULL;
	}
}

//on SDL_Event send
void InputInterface::readEvent(SDL_Event* $event)
{
	for (uint32_t $n = 0; $n < _num_controllers; $n++) {

	}

	/*
	if ($event->type == SDL_JOYBUTTONDOWN)
	{
		if ($event->jbutton.button == 0) {
			$protocol[2] = true;
		}
	}

	if ($event->type == SDL_JOYBUTTONUP)
	{
		if ($event->jbutton.button == 0) {
			$protocol[2] = false;
		}
	}

	if ($event->type == SDL_JOYHATMOTION)
	{
		if ($event->jhat.value == 0) {
			$protocol[0] = false;
			$protocol[1] = false;
		}

		if ($event->jhat.value == SDL_HAT_LEFT) {
			$protocol[0] = true;
		}
		if ($event->jhat.value == SDL_HAT_RIGHT) {
			$protocol[1] = true;
		}
	}
	*/
}

//read keyboard states
void InputInterface::readSDLKeyboard()
{
	const Uint8* $currentKeyStates = SDL_GetKeyboardState(NULL);

	//PLAYER 1 MOVEMENTS
	player1_protocol->move_up = ($currentKeyStates[player1_protocol->key_move_up] ? true : false);
	player1_protocol->move_down = ($currentKeyStates[player1_protocol->key_move_down] ? true : false);
	player1_protocol->move_left = ($currentKeyStates[player1_protocol->key_move_left] ? true : false);
	player1_protocol->move_right = ($currentKeyStates[player1_protocol->key_move_right] ? true : false);

	player1_protocol->confirm = ($currentKeyStates[player1_protocol->key_confirm] ? true : false);
	player1_protocol->cancel = ($currentKeyStates[player1_protocol->key_cancel] ? true : false);

	player1_protocol->shoot = ($currentKeyStates[player1_protocol->key_shoot] ? true : false);
	player1_protocol->jump = ($currentKeyStates[player1_protocol->key_jump] ? true : false);

	player1_protocol->special_1 = ($currentKeyStates[player1_protocol->key_special1] ? true : false);
	player1_protocol->special_2 = ($currentKeyStates[player1_protocol->key_special2] ? true : false);
}