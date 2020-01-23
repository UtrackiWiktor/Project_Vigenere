#include "PlainText.h"



PlainText::PlainText()
{
}


PlainText::~PlainText()
{
}

void PlainText::push_front(char && x)
{
	text += x;
}

int PlainText::return_length()
{
	return text.length();
}

void PlainText::mod_at(int & pos, char val)
{
	text[pos] = val;
}

void PlainText::clear()
{
	text = "";
	length = 0;
}

std::string PlainText::return_class_name()
{
	return std::string("PlainText");
}
 