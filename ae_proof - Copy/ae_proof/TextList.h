#ifndef AE_TEXT_LIST
#define AE_TEXT_LIST

//C++
#include <stdint.h>

//SYSTEM
#include "Graphics.h"
#include "FontLoader.h"
#include "TextObject.h"

class TextList {
public:
	TextList();
	~TextList();

	void setGraphics(Graphics* $graphics);
	void setFontLoader(FontLoader* $font_loader);

	TextObject* getNewText(std::string $string, uint32_t $screen_x = 0, uint32_t $screen_y = 0);

	void freeText(TextObject* $text);

	void allTextDraw();

private:
	static const uint32_t _MAX_TEXT = 128;

	Graphics* _graphics;
	FontLoader* _font_loader;

	TextObject _text_list[_MAX_TEXT];
};

#endif