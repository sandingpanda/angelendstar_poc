#include "TextField.h"

TextField::TextField()
{
	_field_string = "";
}
 
TextField::~TextField() {}

void TextField::initField(std::string $string)
{
	if (text_list == NULL) {
		printf("TextField.initField-> ERROR: INVALID TEXTLIST OBJECT\n");
		return;
	}

	_field_string = $string;
	_text_object = text_list->getNewText(_field_string, x, y);
}

void TextField::updateField(std::string $string)
{
	text_list->freeText(_text_object);
	_field_string = $string;
	_text_object = text_list->getNewText(_field_string, x, y);
}