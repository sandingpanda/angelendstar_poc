#include "GameRect.h"

bool GameRect::intersects(GameRect* $rect1, GameRect* $rect2)
{	
	SDL_Rect $sdl_rect1, $sdl_rect2;

	$sdl_rect1.w = $rect1->w;
	$sdl_rect1.h = $rect1->h;
	$sdl_rect1.x = $rect1->x;
	$sdl_rect1.y = $rect1->y;

	$sdl_rect2.w = $rect2->w;
	$sdl_rect2.h = $rect2->h;
	$sdl_rect2.x = $rect2->x;
	$sdl_rect2.y = $rect2->y;

	if (SDL_HasIntersection(&$sdl_rect1, &$sdl_rect2) == SDL_TRUE) {
		return true;
	}

	return false;
}