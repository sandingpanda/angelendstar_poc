#ifndef AE_GRAPHICS
#define AE_GRAPHICS

//C++
#include <string>
#include <stdint.h>
#include <SDL.h>

//SYSTEM
#include "GameTexture.h"
#include "GameRect.h"

class Graphics {
public:
	Graphics();
	~Graphics();

	//initializer/shutdown functions
	void initRenderer(SDL_Renderer* $renderer);
	void initCamera(uint32_t $camera_width, uint32_t $camera_height);
	void setDrawColor(int $r = RENDER_R, int $g = RENDER_G, int $b = RENDER_B);
	void closeGraphics();

	//invidiual object functions
	SDL_Texture* loadTexture(std::string $path);
	void renderTexture(GameTexture* $texture, GameRect* $source_rect, uint32_t $map_x, uint32_t $map_y, int $depth = 0);
	void renderTextureFixed(GameTexture* $texture, GameRect* $source_rect, uint32_t $screen_x, uint32_t $screen_y);
	void renderBasicRect(GameRect* $game_rect, int $r = RECT_R, int $g = RECT_G, int $b = RECT_B);
	
	//graphics update functions
	void updateRender();
	void clearRender();
	void updateCamera();
	void centerCamera(uint32_t $map_x, uint32_t $map_y);

	//camera functions
	void lockScrollVertical(bool $lock = false);
	void lockScrollHorizontal(bool $lock = false);
	void setCameraBoundaries(uint32_t $up, uint32_t $down, uint32_t $left, uint32_t $right);

private:
	//default render colors
	static const int RENDER_R = 0x00;
	static const int RENDER_G = 0x00;
	static const int RENDER_B = 0x00;
	static const int RENDER_A = 0xFF;

	//default BasicRect colors
	static const int RECT_R = 0xFF;
	static const int RECT_G = 0xFF;
	static const int RECT_B = 0xFF;

	//default texture KEY colors
	static const int KEY_R = 0x00;
	static const int KEY_G = 0x00;
	static const int KEY_B = 0x00;

	//internal variables
	SDL_Renderer* _renderer;
	SDL_Rect _camera;

	//internal initializations
	void initScreen();
	void initLayers();

	//screen render set colors
	int _render_r = 0;
	int _render_g = 0;
	int _render_b = 0;
	int _render_a = 0;
	
	//camera variables
	uint32_t _camera_width;
	uint32_t _camera_height;
	uint32_t _half_cam_width;
	uint32_t _half_cam_height;

	int _cam_move_x = 0;
	int _cam_move_y = 0;
	bool _lock_scroll_v= false;
	bool _lock_scroll_h = false;
	int _cam_up = 0;
	int _cam_down = 0;
	int _cam_left = 0;
	int _cam_right = 0;
};

#endif