#include "Graphics.h"

Graphics::Graphics() {}

Graphics::~Graphics()
{
	_renderer = NULL;
}

void Graphics::closeGraphics() { }

//initialization functions
void Graphics::initRenderer(SDL_Renderer* $renderer)
{
	if ($renderer != NULL) {
		_renderer = $renderer;

		initScreen();
		initLayers();

		setDrawColor();
	}
	else
	{
		printf("Graphics.initRenderer-> PASSED SDL_RENDERER IS INVALID! %s\n", SDL_GetError());
	}
}

void Graphics::initScreen() {}

void Graphics::initLayers() {}

void Graphics::initCamera(uint32_t $camera_width, uint32_t $camera_height)
{
	if (($camera_width > 0) && ($camera_height > 0)) {
		_camera_width = $camera_width;
		_camera_height = $camera_height;
	}
	else
	{
		printf("Graphics.initCamera()-> ERROR: CAMERA DIMENSIONS MUST BE MORE THAN 0\n");
		return;
	}

	_camera.x = 0;
	_camera.y = 0;
	_camera.w = _camera_width;
	_camera.h = _camera_height;
	_half_cam_width = _camera_width / 2;
	_half_cam_height = _camera_height / 2;
}

//setter/loading functions
void Graphics::setDrawColor(int $r, int $g, int $b)
{
	_render_r = $r;
	_render_g = $g;
	_render_b = $b;

	SDL_SetRenderDrawColor(_renderer, _render_r, _render_g, _render_b, RENDER_A);
}

SDL_Texture* Graphics::loadTexture(std::string $path)
{
	SDL_Texture* $new_texture = NULL;
	SDL_Surface* $temp_surface = SDL_LoadBMP($path.c_str());

	if ($temp_surface == NULL) {
		printf("Graphics.loadTexture-> ERROR LOADING SURFACE: %s\n", SDL_GetError());
	}
	else
	{
		//SDL_SetColorKey($temp_surface, SDL_TRUE, SDL_MapRGBA($temp_surface->format, KEY_R, KEY_G, KEY_B, 0x00));

		$new_texture = SDL_CreateTextureFromSurface(_renderer, $temp_surface);

		if ($new_texture == NULL) {
			printf("Graphics.loadTexture-> ERROR CONVERTING SURFACE TO TEXTURE: %s\n", SDL_GetError());
		}

		SDL_FreeSurface($temp_surface);
	}
	return $new_texture;
}

//render functions
void Graphics::renderTexture(GameTexture* $game_texture, GameRect* $game_rect, uint32_t $map_x, uint32_t $map_y, int $depth)
{
	SDL_Texture* $texture = $game_texture->getSDLTexture();
	SDL_Rect $source_rect, $render_rect;

	//source rect
	$source_rect.x = $game_rect->x;
	$source_rect.y = $game_rect->y;
	$source_rect.w = $game_rect->w;
	$source_rect.h = $game_rect->h;

	//rendering rect
	$render_rect.w = $source_rect.w;
	$render_rect.h = $source_rect.h;

	//parallax offset by depth value
	if ($depth == 0) {
		$render_rect.x = $map_x - _camera.x;
		$render_rect.y = $map_y - _camera.y;
	}
	else
	{
		$render_rect.x = $map_x - (_camera.x / $depth);
		$render_rect.y = $map_y - (_camera.y / $depth);
	}
	SDL_RenderCopy(_renderer, $texture, &$source_rect, &$render_rect);
}

void Graphics::renderTextureFixed(GameTexture* $game_texture, GameRect* $game_rect, uint32_t $screen_x, uint32_t $screen_y)
{
	SDL_Texture* $texture = $game_texture->getSDLTexture();
	SDL_Rect $source_rect, $render_rect;

	//source rect
	$source_rect.x = $game_rect->x;
	$source_rect.y = $game_rect->y;
	$source_rect.w = $game_rect->w;
	$source_rect.h = $game_rect->h;

	//rendering rect
	$render_rect.x = $screen_x;
	$render_rect.y = $screen_y;
	$render_rect.w = $source_rect.w;
	$render_rect.h = $source_rect.h;

	SDL_RenderCopy(_renderer, $texture, &$source_rect, &$render_rect);
}

void Graphics::renderBasicRect(GameRect* $game_rect, int $r, int $g, int $b)
{
	SDL_Rect $source_rect;
	
	//build source rect
	$source_rect.x = $game_rect->x;
	$source_rect.y = $game_rect->y;
	$source_rect.w = $game_rect->w;
	$source_rect.h = $game_rect->h;

	//offset to camera
	$source_rect.x -= _camera.x;
	$source_rect.y -= _camera.y;

	//change draw color
	setDrawColor($r, $g, $b);
	SDL_RenderFillRect(_renderer, &$source_rect);

	//reset draw color
	setDrawColor();
}

void Graphics::updateRender()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::clearRender()
{
	SDL_RenderClear(_renderer);
}

void Graphics::updateCamera()
{
	if (_lock_scroll_h) {
		if (_cam_move_x < _cam_left)
		{
			_cam_move_x = _cam_left;
		}
		else if (_cam_move_x > _cam_right)
		{
			_cam_move_x = _cam_right;
		}
	}

	if (_lock_scroll_v) {
		if (_cam_move_y < _cam_up)
		{
			_cam_move_y = _cam_up;
		}
		else if (_cam_move_y > _cam_down)
		{
			_cam_move_y = _cam_down;
		}
	}

	_camera.x = _cam_move_x;
	_camera.y = _cam_move_y;
}

//camera functions
void Graphics::centerCamera(uint32_t $map_x, uint32_t $map_y)
{
	_cam_move_x = $map_x - _half_cam_width;
	_cam_move_y = $map_y - _half_cam_height;
}

void Graphics::setCameraBoundaries(uint32_t $up, uint32_t $down, uint32_t $left, uint32_t $right)
{
	_cam_up = $up;
	_cam_down = $down - _camera_height;
	_cam_left = $left;
	_cam_right = $right - _camera_width;
}

void Graphics::lockScrollVertical(bool $lock) { _lock_scroll_v = $lock; }

void Graphics::lockScrollHorizontal(bool $lock) { _lock_scroll_h = $lock; }
