#include "TextObject.h"

TextObject::TextObject() {}

TextObject::~TextObject() {}

void TextObject::getDimensions()
{
	draw_rect.x = 0;
	draw_rect.y = 0;
	draw_rect.w = texture.width;
	draw_rect.h = texture.height;
}

void TextObject::free()
{
	texture.free();
	screen_x = 0;
	screen_y = 0;
}