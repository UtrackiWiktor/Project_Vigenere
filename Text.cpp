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
		/*if (buff >= 48 && buff <= 57)
		{
			text += buff;
			continue;
		}*/
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
	std::fstream output_file(file_name, std::ios::out);
	if (!output_file.good())
		std::cout << "\noutput file error.\n";
	output_file << text;
}

char Text::operator[](const int &x) const
{
	return text[x];
}

void Text::calc_length()
{
	length = text.length();
}

std::string Text::return_text()
{
	return text;
}

std::string Text::return_class_name()
{
	return std::string("Text");
}

std::string Text::substr(const int & beg, const int & count) const
{
	return text.std::string::substr(beg, count);
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
