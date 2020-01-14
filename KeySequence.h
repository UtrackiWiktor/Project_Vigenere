#pragma once
#include "Text.h"

class KeySequence :
	public Text
{
	std::string key_sequence;

public:
	KeySequence();
	KeySequence(const std::string &file_name) : Text(file_name) {};
	~KeySequence();

	void generate_key_sequence(const Text &plain);
	std::string return_key_sequence();

	char operator[](int x);

	friend std::ostream& operator<<(std::ostream &os, const Text &obj);
	// friend void encrypt_txt(PlainText &plain_txt, CipherText &cipher, KeySequence &key, Vigenere_table &vig_tab);

};

