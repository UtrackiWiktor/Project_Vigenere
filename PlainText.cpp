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
 