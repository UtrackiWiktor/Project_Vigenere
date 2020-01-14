#include "KeySequence.h"



KeySequence::KeySequence()
{
}


KeySequence::~KeySequence()
{
}

void KeySequence::generate_key_sequence(const Text &plain)
{
	int plain_txt_length = plain.text.length();
	int key_length = text.length();

	if (plain_txt_length > key_length)
	{
		//make key into proper sequence
		int x = plain_txt_length / key_length;
		std::string *temp = new std::string(text);

		//filling integer difference
		for (int i = 0; i < x; i++)
		{
			key_sequence += *temp;
		}

		//filling the fractional rest
		if (plain_txt_length - key_sequence.length() != 0)
		{
			int diff = plain_txt_length - key_sequence.length();
			key_sequence += (*temp).substr(0, diff);

			///debug
			std::cout << "\nTest key sequence - length: seq, plain: " << key_sequence.length() << ", " << plain_txt_length;
		}
		delete(temp);
	}
}

std::string KeySequence::return_key_sequence()
{
	return key_sequence;
}

char KeySequence::operator[](int x)
{
	return key_sequence[x];
} 
