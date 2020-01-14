#pragma once
#include <string>
#include <iostream>
//#include "Vigenere_table.h"
//#include "PlainText.h"
//#include "CipherText.h"
//#include "KeySequence.h"


class Text
{
	friend class KeySequence;
protected:
	std::string text;
	int length;

public:
	Text();
	Text(const std::string &_filename);
	~Text();

	void print_to_screen();
	void print_to_file(std::string file_name);
	char operator[](int x);
	void calc_length();

	friend std::ostream& operator<<(std::ostream &os, const Text &obj);

	//void truncate();
};

