#include "FontLoader.h"

FontLoader::FontLoader() {}

FontLoader::~FontLoader() {}

void FontLoader::closeFont()
{
	if (_loaded_font != NULL)
	{
		TTF_CloseFont(_loaded_font);
		_loaded_font = NULL;
	}
}

void FontLoader::setRenderer(SDL_Renderer* $renderer)
{
	if ($renderer != NULL) {
		_renderer = $renderer;
	}
	else
	{
		printf("FontLoader.setRenderer-> ERROR: INVALID RENDERER");
	}
}

void FontLoader::loadFont(char* $filename)
{
	if (!TTF_WasInit()) {
		if (TTF_Init() != -1) {
			SDL_Color $base_color;
			$base_color.r = _DEFAULT_R;
			$base_color.g = _DEFAULT_G;
			$base_color.b = _DEFAULT_B;
			$base_color.a = 0xFF;

			_loaded_font = TTF_OpenFont($filename, _DEFAULT_SIZE);

			_default_color = $base_color;
		}
		else
		{
			printf("FontLoader.loadFont-> ERROR: TTF LIBRARY FAILED TO INITIALIZE, %s\n", TTF_GetError());
		}
	}
}

SDL_Texture* FontLoader::renderText(std::string $string)
{
	char const *$c_str = $string.c_str();

	SDL_Texture* $texture = NULL;

	SDL_Color $temp_color;
	$temp_color.a = 0x99;
	$temp_color.r = 0x00;
	$temp_color.g = 0x00;
	$temp_color.b = 0x00;

	SDL_Surface* $temp_surf = TTF_RenderText_Solid(_loaded_font, $c_str, _default_color);
	//SDL_Surface* $temp_surf = TTF_RenderText_Shaded(_loaded_font, $c_str, _default_color, $temp_color);
	//SDL_Surface* $temp_surf = TTF_RenderText_Blended(_loaded_font, $c_str, _default_color);

	if ($temp_surf != NULL) {
		$texture = SDL_CreateTextureFromSurface(_renderer, $temp_surf);
	}
	else
	{
		printf("FontLoader.renderText-> ERROR: FONT SURFACE INVALID %s\n", SDL_GetError());
	}

	SDL_FreeSurface($temp_surf);

	return $texture;
}
