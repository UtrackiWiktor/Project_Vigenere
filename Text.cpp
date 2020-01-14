#include "Text.h"
#include <fstream>
#include <iostream>

Text::Text() 
{
}

Text::Text(const std::string & _file_name)
{
	std::fstream file(_file_name, std::ios::in);
	char buff;

	while (file >> buff)
	{
		//if A-Z
		if (buff >= 65 && buff <= 90)
		{
			text += buff;
			continue;
		}
		//if a-z
		if (buff >= 97 && buff <= 122)
		{
			buff -= 32;
			text += buff;
			continue;
		}
		//if 0-9
		if (buff >= 48 && buff <= 57)
		{
			text += buff;
			continue;
		}
		//else discard
	}
	file.close();

	length = text.length();
}

Text::~Text()
{
}

void Text::print_to_screen()
{
	std::cout << text << std::endl;
}

void Text::print_to_file(std::string file_name)
{
}

char Text::operator[](int x)
{
	return text[x];
}

void Text::calc_length()
{
	length = text.length();
}

std::ostream& operator<<(std::ostream &os, const Text &obj)
{
	os << obj.text;
	return os;
}

//void Text::truncate()
//{
//	text.clear();
//	length = 0;
//}