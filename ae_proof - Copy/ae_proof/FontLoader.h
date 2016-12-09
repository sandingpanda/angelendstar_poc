#ifndef AE_FONT_LOADER
#define AE_FONT_LOADER

//C++
#include <string>
#include <stdio.h>
#include <cmath>
#include <SDL_ttf.h>

class FontLoader {
public:
	FontLoader();
	~FontLoader();
	
	//dependency loader
	void setRenderer(SDL_Renderer* $renderer);

	//font load
	void loadFont(char* $filename);

	//render text in font
	SDL_Texture* renderText(std::string $string);
	
	//free font 
	void closeFont();

private:
	static const int _DEFAULT_R = 0x00;
	static const int _DEFAULT_G = 0xCC;
	static const int _DEFAULT_B = 0x00;
	static const int _DEFAULT_SIZE = 16;

	TTF_Font* _loaded_font;
	SDL_Color _default_color;

	SDL_Renderer* _renderer;
};

#endif