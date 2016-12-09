#ifndef AE_TEXT_FIELD
#define AE_TEXT_FIELD

#include "TextList.h"

class TextField
{
public:
	TextField();
	~TextField();

	int x = 0;
	int y = 0;

	TextList* text_list;

	void initField(std::string $string);
	void updateField(std::string $string);

private:
	TextObject* _text_object;
	std::string _field_string;
};

#endif