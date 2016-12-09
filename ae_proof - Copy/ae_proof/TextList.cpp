#include "TextList.h"

TextList::TextList() {}

TextList::~TextList()
{
	for (int $n = 0; $n < _MAX_TEXT; $n++) {
		if (_text_list[$n].used > 0) {
			_text_list[$n].texture.free();
		}
	}
}

void TextList::setGraphics(Graphics* $graphics)
{
	if ($graphics != NULL) {
		_graphics = $graphics;
	}
	else
	{
		printf("TextList.setGraphics-> ERROR: INVALID GRAPHICS OBJECT\n");
	}
}

void TextList::setFontLoader(FontLoader* $font_loader)
{
	if ($font_loader != NULL) {
		_font_loader = $font_loader;
	}
	else
	{
		printf("TextList.setFontLoader-> ERROR: INVALID FONTLOADER OBJECT\n");
	}
}

TextObject* TextList::getNewText(std::string $string, uint32_t $screen_x, uint32_t $screen_y)
{
	TextObject* $text_obj = NULL;

	for (int $n = 0; $n < _MAX_TEXT; $n++) {
		if (_text_list[$n].used == 0) {
			_text_list[$n].used++;
			_text_list[$n].texture.setSDLTexture(_font_loader->renderText($string));
			_text_list[$n].getDimensions();
			_text_list[$n].screen_x = $screen_x;
			_text_list[$n].screen_y = $screen_y;

			$text_obj = &_text_list[$n];
			break;
		}
	}

	return $text_obj;
}

void TextList::allTextDraw()
{
	for (int $n = 0; $n < _MAX_TEXT; $n++) {
		if (_text_list[$n].used > 0) {
			_graphics->renderTextureFixed(&_text_list[$n].texture, &_text_list[$n].draw_rect, _text_list[$n].screen_x, _text_list[$n].screen_y);
		}
	}
}

void TextList::freeText(TextObject* $text_obj)
{
	for (int $n = 0; $n < _MAX_TEXT; $n++) {
		if (&_text_list[$n] == $text_obj) {
			$text_obj->used--;

			if ($text_obj->used == 0) {
				_text_list[$n].free();
			}
		}
	}
}