#include "Game.h"

Game::Game()
{
	if (system.initSystem(_DEFAULT_WIDTH, _DEFAULT_HEIGHT)) {

		//initialize graphics
		initGraphics();
		
		//assign system object dependencies
		texture_list.setGraphics(&graphics);
		sprite_list1.setTextureList(&texture_list);

		//init font/text system
		initFont();
		
		//check for controllers
		if (input_interface.openControllers()) {
			_use_controllers = true;
		}
		//initialize input protocols
		input_interface.player1_protocol = &player1_protocol;

		//initialize title screen
		initTitleScreen();

		//start main game loop
		mainLoop();
	}
	else
	{
		printf("->SDLSystem: SDLSystem failed to initialize! \n");
	}
}

Game::~Game() { }

//main program loop
void Game::mainLoop()
{
	_next_time = SDL_GetTicks();

	while (!_quit) {
		//GRAPHICS CLEAR
		//graphics.clearRender();

		while (SDL_PollEvent(&_loop_event)) {

			//READ INPUT
			if (_use_controllers) {
				input_interface.readEvent(&_loop_event);
			}
			input_interface.readSDLKeyboard();

			//CHECK IF QUIT
			if (_loop_event.type == SDL_QUIT) {
				_quit = true;
			}
		}

		//CHECK TIME LAPSE TO UPDATE GRAPHICS/PHYSICS
		if (SDL_GetTicks() >= (_next_time + _tick_timer)) {

			if (_state == GameState::TITLE_SCREEN) {
				titleLoop();
				titleControl();
			}
			else
			{
				playerOneControl();
				gameplayLoop();
			}

			graphics.updateRender();

			//reset lapse timer
			_next_time = SDL_GetTicks();
		}
	}

	quitProcedures();
}

void Game::titleLoop()
{
	graphics.renderTextureFixed(title_screen.background->sprite_texture, title_screen.background->setFrame(0), 0, 0);

	text_list.allTextDraw();
}

void Game::gameplayLoop()
{
	//entities think
	entity_list.allEntitiesThink();

	//physics for entities
	physics_engine.moveAllEntities();

	//draw map
	game_map.drawMap();

	//draw entities
	entity_list.allEntitiesDraw();
	text_list.allTextDraw();

	//update player variables
	player.updateStatus();
	player.updatePositions();

	//update graphics and camera
	updateScroll();
	graphics.centerCamera(_scroll_center_x, _scroll_center_y);
	graphics.updateCamera();
	
	if (entity_list.update_score) {
		updateHUD(7, entity_list.score);
		entity_list.update_score = false;
	}

	if (player.update_health) {
		updateHUD(1, player.health_1);
		updateHUD(3, player.health_2);
		player.update_health = false;
	}

	if (player.update_charge) {
		updateHUD(5, player.charge);
		player.update_charge = false;
	}
}


void Game::updateHUD(int $field, int $value)
{
	std::string $value_str = std::to_string($value);
	_hud[$field].updateField($value_str);
}

void Game::updateScroll()
{
	_scroll_rect.x += physics_engine.scroll_speed_x * physics_engine.scroll_dir_x;
	_scroll_rect.y += physics_engine.scroll_speed_y * physics_engine.scroll_dir_y;
	_scroll_center_x += physics_engine.scroll_speed_x * physics_engine.scroll_dir_x;
	_scroll_center_y += physics_engine.scroll_speed_y * physics_engine.scroll_dir_y;

	int $room_x = _scroll_rect.x / (Room::WIDTH * Tile::HEIGHT);
	int $room_y = _scroll_rect.y / (Room::HEIGHT* Tile::HEIGHT);

	Room $current_room = game_map.room_grid[$room_y][$room_x];
	if ($current_room.scroll_flag == ScrollFlag::STOP_SCROLL) {
		physics_engine.scroll_speed_x = 0;
		physics_engine.scroll_speed_y = 0;
	}
}

//player one control protcol response
void Game::playerOneControl()
{
	//MOVE UP
	if (player1_protocol.move_up) {
		player.moveUp();
	}
	if (player1_protocol.move_down) {
		player.moveDown();
	}
	if (!player1_protocol.move_up && !player1_protocol.move_down) {
		player.stopMoveVertical();
	}

	//MOVE LEFT
	if (player1_protocol.move_left) {
		player.moveLeft();
	}
	//MOVE RIGHT
	if (player1_protocol.move_right) {
		player.moveRight();
	}
	//STOP MOVING
	if (!player1_protocol.move_left && !player1_protocol.move_right) {
		player.stopMoveHorizontal();
	}

	if (player1_protocol.shoot) {
		player.shootMain();
	}

	if (player1_protocol.special_2) {
		player.shootCharge();
	}

	//SWAPPING PLAYERS
	if (player1_protocol.jump == true) {
		if (_switch_down) {
			return;
		}
		_switch_down = true;

		player.swapPlayers();
	}

	if (player1_protocol.jump == false) {
		_switch_down = false;
	}
}

void Game::titleControl()
{
	if (player1_protocol.confirm) {
		title_screen.closeScreen();
		initGameplay();
		_state = GameState::GAMEPLAY;
	}
}

//initialization functions
void Game::initGraphics()
{
	graphics.initRenderer(system.getRenderer());
	graphics.initCamera(_DEFAULT_WIDTH, _DEFAULT_HEIGHT);
	graphics.lockScrollHorizontal(true);
	graphics.lockScrollVertical(true);
}

void Game::initTitleScreen()
{
	title_screen.background = sprite_list1.setSprite("./logo.bmp", "title_logo", 960, 540);

	title_screen.setTextList(&text_list);
	title_screen.initScreen();
}

//gameplay initializations
void Game::initGameplay()
{
	entity_list.setGraphics(&graphics);

	initPlayer();
	initMap();
	initPhysics();
	initHUD();
	initScroll();
	initAudio();
}

void Game::initPlayer()
{
	player.initialize(&entity_list, &sprite_list1);
}

void Game::initMap()
{
	uint32_t $cam_left = 0;
	uint32_t $cam_right = _DEFAULT_WIDTH * Map::WIDTH;
	uint32_t $cam_top = 0;
	uint32_t $cam_bottom = _DEFAULT_HEIGHT * Map::HEIGHT;

	graphics.setCameraBoundaries($cam_top, $cam_bottom, $cam_left, $cam_right);

	game_map.graphics = &graphics;
	buildMap(&game_map, &sprite_list1);
	game_map.buildHitData();

	game_map.background = sprite_list1.setSprite("./background.bmp", "map_background", _DEFAULT_WIDTH, _DEFAULT_HEIGHT);

	for (int $i = 0; $i < Map::WIDTH; $i++) {
		for (int $j = 0; $j < Map::HEIGHT; $j++) {
			for (int $k = 0; $k < Room::WIDTH; $k++) {
				Formation $formation = game_map.room_grid[$j][$i].formation_line[$k];

				if ($formation.active) {
					for (int $n = 0; $n < Formation::MAX_ENEMIES; $n++) {
						if ($formation.enemies[$n] == "ENEMY_WALKER") {
							EnemyWalker* $walker = new EnemyWalker();

							$walker->sprite = sprite_list1.setSprite(EnemyWalker::SPRITE_PATH, "enemy_walker", EnemyWalker::SPRITE_WIDTH, EnemyWalker::SPRITE_HEIGHT);
							$walker->x = $i * (Room::WIDTH * Tile::WIDTH) + ($n * Tile::WIDTH);
							$walker->y = 128;

							entity_list.addEntity($walker);

							$walker->sprite_list = &sprite_list1;
							$walker->entity_list = &entity_list;

							$walker->initWalker();
						}

						if ($formation.enemies[$n] == "ENEMY_JET") {
							EnemyJet* $walker = new EnemyJet();

							$walker->sprite = sprite_list1.setSprite(EnemyJet::SPRITE_PATH, "enemy_jet", EnemyJet::SPRITE_WIDTH, EnemyJet::SPRITE_HEIGHT);
							$walker->x = $i * (Room::WIDTH * Tile::WIDTH) + ($n * Tile::WIDTH);
							$walker->y = 128;

							entity_list.addEntity($walker);

							$walker->sprite_list = &sprite_list1;
							$walker->entity_list = &entity_list;

							$walker->initJet();
						}
					}
				}
			}
			
		}
	}

	EnemyBoss* $boss = new EnemyBoss();

	$boss->sprite = sprite_list1.setSprite(EnemyBoss::SPRITE_PATH, "enemy_boss", EnemyBoss::SPRITE_WIDTH, EnemyBoss::SPRITE_HEIGHT);
	$boss->x = Map::WIDTH * (Room::WIDTH * Tile::WIDTH) - ((Room::WIDTH * Tile::WIDTH) / 2);
	$boss->y = 128;

	entity_list.addEntity($boss);

	$boss->sprite_list = &sprite_list1;
	$boss->entity_list = &entity_list;

	$boss->initBoss();
}

void Game::initPhysics()
{
	physics_engine.current_map = &game_map;
	physics_engine.setEntityList(&entity_list);
}

void Game::initFont()
{
	font_loader.setRenderer(system.getRenderer());
	font_loader.loadFont(_DEFAULT_FONT);
	
	text_list.setFontLoader(&font_loader);
	text_list.setGraphics(&graphics);
}

void Game::initAudio()
{
	SFXLibrary::AUDIO_PLAYER = &audio_player;
	SFXLibrary::loadSamples();

	int $song_index = audio_player.loadMusicFile("./audio/greenwood_edit.wav");

	if ($song_index != -1) {
		audio_player.playMusic($song_index);
	}

	
}

void Game::initHUD()
{
	for (int $n = 0; $n < 8; $n++) {
		_hud[$n].text_list = &text_list;
	}

	//health counters
	_hud[0].x = 32;
	_hud[0].y = 32;
	_hud[0].initField("HEALTH 1");

	_hud[1].x = 32;
	_hud[1].y = 64;
	_hud[1].initField("100");

	_hud[2].x = 128;
	_hud[2].y = 32;
	_hud[2].initField("HEALTH 2");

	_hud[3].x = 128;
	_hud[3].y = 64;
	_hud[3].initField("100");

	//weapon charge counter
	_hud[4].x = 256;
	_hud[4].y = 32;
	_hud[4].initField("CHARGE");

	_hud[5].x = 256;
	_hud[5].y = 64;
	_hud[5].initField("0");

	//score counter
	_hud[6].x = 768;
	_hud[6].y = 32;
	_hud[6].initField("SCORE");

	_hud[7].x = 768;
	_hud[7].y = 64;
	_hud[7].initField("0");
}

void Game::initScroll()
{
	_scroll_rect.w = _DEFAULT_WIDTH;
	_scroll_rect.h = _DEFAULT_HEIGHT;
	
	for (int $i = 0; $i < Map::HEIGHT; $i++) {
		for (int $j = 0; $j < Map::WIDTH; $j++) {
			if (game_map.room_grid[$i][$j].scroll_flag == ScrollFlag::START_SCROLL) {
				Room $room = game_map.room_grid[$i][$j];
				physics_engine.scroll_dir_x = $room.scroll_dir_x;
				physics_engine.scroll_dir_y = $room.scroll_dir_y;
				physics_engine.scroll_speed_x = $room.scroll_speed_x;
				physics_engine.scroll_speed_y = $room.scroll_speed_y;

				_scroll_rect.x = $j * Room::WIDTH * Tile::WIDTH;
				_scroll_rect.y = $i * Room::HEIGHT * Tile::HEIGHT;
				break;
			}
		}
	}

	_scroll_center_x = _scroll_rect.x + (_DEFAULT_WIDTH / 2);
	_scroll_center_y = _scroll_rect.y + (_DEFAULT_HEIGHT / 2);
}

//called on SDL quit event
void Game::quitProcedures()
{
	font_loader.closeFont();
	input_interface.closeControllers();
	graphics.closeGraphics();
}

//THIS IS FOR TESTING, NOT THE TRUE 'buildMap'
void Game::buildMap(Map* $map, SpriteList* $sprite_list)
{
	//BUILD MAP
	Tile walk;
	Tile wall;

	BackgroundTile bg_tile;
	BackgroundTile bg_blank;

	Room room1, room2, room3, room4, room_boss;

	Formation formation_1;
	formation_1.active = true;
	formation_1.enemies[0] = "ENEMY_WALKER";
	formation_1.enemies[3] = "ENEMY_JET";
	formation_1.enemies[7] = "ENEMY_WALKER";

	std::array<Formation, Room::WIDTH> formation_line;
	formation_line[6] = formation_1;

	walk.walk_value = Tile::WALK;
	wall.walk_value = Tile::WALL;
	wall.sprite = $sprite_list->setSprite("./tile_block.bmp", "ae_testbed_tiles", 60, 60);
	wall.name = "WALL TILE";
	walk.name = "WALKING TILE";

	bg_tile.sprite = $sprite_list->setSprite("./tile_background.bmp", "ae_testbed_bg", 120, 120);

	std::array< std::array<Tile, Room::WIDTH>, Room::HEIGHT> $tile_grid;
	std::array< std::array<Tile, Room::WIDTH>, Room::HEIGHT> $tile_grid2;
	std::array< std::array<Tile, Room::WIDTH>, Room::HEIGHT> $tile_grid3;
	std::array< std::array<Tile, Room::WIDTH>, Room::HEIGHT> $tile_grid4;

	std::array< std::array<BackgroundTile, Map::BG_WIDTH>, Map::BG_HEIGHT> $bg_grid;

	$tile_grid[0] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };
	$tile_grid[1] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[2] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[3] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[4] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[5] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[6] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[7] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid[8] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };

	room1.tile_grid = $tile_grid;
	room1.room_name = "FIRST ROOM";
	room1.scroll_flag = ScrollFlag::START_SCROLL;
	room1.scroll_dir_x = 1;
	room1.scroll_dir_y = 0;
	room1.scroll_speed_x = 2;
	room1.scroll_speed_y = 0;

	room_boss.tile_grid = $tile_grid;
	room_boss.room_name = "BOSS ROOM";
	room_boss.scroll_flag = ScrollFlag::STOP_SCROLL;

	$tile_grid2[0] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };
	$tile_grid2[1] = { walk, walk, walk, walk, walk, walk, wall, wall, wall, wall, wall, walk, walk, walk, walk, walk };
	$tile_grid2[2] = { walk, walk, walk, walk, walk, walk, walk, walk, wall, wall, wall, walk, walk, walk, walk, walk };
	$tile_grid2[3] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, wall, walk, walk, walk, walk, walk };
	$tile_grid2[4] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid2[5] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid2[6] = { walk, walk, wall, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid2[7] = { walk, wall, wall, wall, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid2[8] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };

	room2.tile_grid = $tile_grid2;
	room2.formation_line = formation_line;

	$tile_grid3[0] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };
	$tile_grid3[1] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid3[2] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid3[3] = { walk, walk, walk, walk, walk, walk, wall, wall, wall, wall, walk, walk, walk, walk, walk, walk };
	$tile_grid3[4] = { walk, walk, walk, walk, wall, wall, wall, wall, wall, wall, wall, walk, walk, walk, walk, walk };
	$tile_grid3[5] = { walk, walk, walk, walk, walk, wall, wall, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid3[6] = { walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk, walk };
	$tile_grid3[7] = { walk, walk, walk, walk, walk, walk, walk, walk, wall, wall, walk, walk, walk, walk, walk, walk };
	$tile_grid3[8] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };

	room3.tile_grid = $tile_grid3;
	room3.formation_line = formation_line;

	$tile_grid4[0] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };
	$tile_grid4[1] = { walk, walk, walk, walk, wall, wall, walk, walk, walk, walk, walk, walk, walk, walk, wall, walk };
	$tile_grid4[2] = { walk, walk, walk, walk, wall, wall, walk, walk, walk, walk, walk, walk, walk, walk, wall, walk };
	$tile_grid4[3] = { walk, walk, walk, walk, walk, wall, walk, walk, walk, walk, walk, walk, walk, walk, wall, walk };
	$tile_grid4[4] = { walk, walk, wall, walk, walk, wall, walk, walk, walk, walk, wall, walk, walk, walk, wall, walk };
	$tile_grid4[5] = { walk, walk, wall, walk, walk, walk, walk, walk, walk, walk, wall, walk, walk, walk, walk, walk };
	$tile_grid4[6] = { walk, wall, wall, walk, walk, walk, walk, walk, walk, walk, wall, walk, walk, walk, walk, walk };
	$tile_grid4[7] = { walk, wall, wall, walk, walk, walk, walk, walk, wall, wall, wall, walk, walk, walk, walk, walk };
	$tile_grid4[8] = { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall };

	room4.tile_grid = $tile_grid4;
	room4.formation_line = formation_line;

	$bg_grid[0] = { bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };
	$bg_grid[1] = { bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };
	$bg_grid[2] = { bg_blank, bg_tile, bg_tile, bg_blank, bg_tile, bg_tile, bg_blank, bg_blank, bg_tile, bg_tile, bg_blank, bg_blank, bg_tile, bg_tile, bg_blank, bg_blank };
	$bg_grid[3] = { bg_blank, bg_tile, bg_tile, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_tile, bg_tile, bg_blank, bg_blank };
	$bg_grid[4] = { bg_blank, bg_tile, bg_tile, bg_blank, bg_tile, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_tile, bg_blank, bg_blank };
	$bg_grid[5] = { bg_blank, bg_tile, bg_tile, bg_tile, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };
	$bg_grid[6] = { bg_blank, bg_tile, bg_tile, bg_tile, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };
	$bg_grid[7] = { bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };
	$bg_grid[8] = { bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank, bg_blank };

	$map->background_grid = $bg_grid;

	std::array< std::array<Room, Map::WIDTH>, Map::HEIGHT> $room_grid;

	$room_grid[0] = { room1, room2, room1, room3, room4, room_boss };

	$map->room_grid = $room_grid;
}