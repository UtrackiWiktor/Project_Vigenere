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

int CipherText::return_length()
{
	return text.length();
}