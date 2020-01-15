#include "CipherText.h"



CipherText::CipherText()
{
}


CipherText::~CipherText()
{
}

void CipherText::push_front(char && x)
{
	text += x;
 }

int Text::return_length() const
{
	return text.length();
}