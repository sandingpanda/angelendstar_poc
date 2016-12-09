#include "Screen.h"

void Screen::setTextList(TextList* $text_list)
{
	if ($text_list != NULL) {
		text_list = $text_list;
	}
	else
	{
		printf("Screen.setTextList-> ERROR: INVALID TEXTLIST");
	}
}

void Screen::initScreen() {}

void Screen::closeScreen() {}