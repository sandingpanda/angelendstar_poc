#include "Screen.h"
#include "TextList.h"

class TitleScreen : public Screen {
public:
	TextObject* start_text;

	void initScreen();
	void closeScreen();
};