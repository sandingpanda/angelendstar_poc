#ifndef AE_SCREEN
#define AE_SCREEN

//C++
#include <stdint.h>

//SYSTEM
#include "SpriteList.h"
#include "TextList.h"

class Screen {
public:
	Sprite* background;

	virtual void initScreen();
	virtual void closeScreen();

	void setTextList(TextList* $text_list);

protected:
	static const std::string background_path;

	TextList* text_list;
};

#endif