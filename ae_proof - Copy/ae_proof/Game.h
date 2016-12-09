#ifndef AE_GAME
#define AE_GAME

//SDL INCLUDES
#include <SDL.h>

//SYSTEM CLASSES
#include "SDLSystem.h"
#include "Graphics.h"
#include "AudioPlayer.h"
#include "TextureList.h"
#include "SpriteList.h"
#include "InputInterface.h"
#include "InputProtocol.h"
#include "PhysicsEngine.h"
#include "FontLoader.h"
#include "TextList.h"
#include "TextField.h"
#include "SFXLibrary.h"

//OBJECT CLASSES
#include "TitleScreen.h"
#include "EntityList.h"
#include "Player.h"

#include "EnemyWalker.h"
#include "EnemyJet.h"
#include "EnemyBoss.h"

enum class GameState { TITLE_SCREEN, MAIN_MENU, GAMEPLAY, OPTIONS};

class Game {
public:
	Game();
	~Game();

	//components
	SDLSystem system;
	Graphics graphics;
	TextureList texture_list;
	FontLoader font_loader;
	AudioPlayer audio_player;

	//sprite list(s)
	SpriteList sprite_list1;

	//entity list
	EntityList entity_list;

	//text objects
	TextList text_list;

	//player/controller interface and protocols
	InputInterface input_interface;
	InputProtocol player1_protocol;

	//physics engine
	PhysicsEngine physics_engine;

	//basic map
	Map game_map;

	//player
	Player player;

	//title screen
	TitleScreen title_screen;

private:
	//DEFAULT SYSTEM VALUES
	const int _DEFAULT_LAPSE_TIME = 17;

	//DEFAULT VALUES FOR USER OPTIONS
	const int _DEFAULT_WIDTH = 960;
	const int _DEFAULT_HEIGHT = 540;

	//DEFAULT FONT
	char* _DEFAULT_FONT = "./Audiowide-Regular.ttf";

	//tag values
	bool _quit = false;
	bool _use_controllers = false;
	
	bool _game_start = false;

	//event objects
	int _tick_timer = _DEFAULT_LAPSE_TIME;
	SDL_Event _loop_event;
	Uint32 _next_time = 0;

	GameState _state = GameState::TITLE_SCREEN;

	bool _switch_down = false;

	//scroll values
	GameRect _scroll_rect;
	int _scroll_center_x = 0;
	int _scroll_center_y = 0;

	//hud textfields
	TextField _hud[8];
	int counter;

	//internal system functions
	void mainLoop();
	void titleLoop();
	void gameplayLoop();
	void updateHUD(int $field = 1, int $value = 0);
	void updateScroll();

	void quitProcedures();

	//primary initialization functions
	void initGraphics();
	void initFont();
	void initTitleScreen();
	void initGameplay();

	//gameplay initialization functions
	void initPlayer();
	void initMap();
	void initPhysics();
	void initHUD();
	void initScroll();
	void initAudio();
	void buildMap(Map* $map, SpriteList* $sprite_list);

	//main input
	void titleControl();
	void playerOneControl();
};

#endif