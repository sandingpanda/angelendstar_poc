#ifndef AE_GAME_RECT
#define AE_GAME_RECT

#include <stdio.h>
#include <SDL.h>

class GameRect {
public:
	int x, y = 0;
	int w, h = 0;

	static bool intersects(GameRect* $rect1, GameRect* $rect2);
};


#endif