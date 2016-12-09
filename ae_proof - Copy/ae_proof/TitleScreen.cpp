#include "TitleScreen.h"

void TitleScreen::initScreen()
{
	start_text = text_list->getNewText("PRESS ENTER", 410, 490);
}

void TitleScreen::closeScreen()
{
	text_list->freeText(start_text);
}