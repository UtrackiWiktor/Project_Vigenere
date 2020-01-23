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

std::string CipherText::return_class_name()
{
	return std::string("CipherText");
}

int Text::return_length() const
{
	return text.length();
}