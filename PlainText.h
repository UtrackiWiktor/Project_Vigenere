#pragma once
#include "Text.h"
#include "CipherText.h"


class PlainText :
	public Text
{
public:
	PlainText();
	PlainText(const std::string &file_name) : Text(file_name) {};
	~PlainText();

	void push_front(char &&x);
	int return_length();
	void mod_at(int &pos, char val); 

	friend std::ostream& operator<<(std::ostream &os, const Text &obj);
	//friend void encrypt_txt(PlainText &plain_txt, CipherText &cipher, KeySequence &key, Vigenere_table &vig_tab);

};

