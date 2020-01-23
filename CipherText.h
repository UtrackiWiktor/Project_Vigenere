#pragma once
#include "Text.h"

class CipherText :
	public Text
{
public:
	CipherText();
	CipherText(const std::string &file_name) : Text(file_name) {};
	~CipherText();
	 
	void push_front(char &&x);

	std::string return_class_name();
	friend std::ostream& operator<<(std::ostream &os, const Text &obj);
	//friend void encrypt_txt(PlainText &plain_txt, CipherText &cipher, KeySequence &key, Vigenere_table &vig_tab);

};

