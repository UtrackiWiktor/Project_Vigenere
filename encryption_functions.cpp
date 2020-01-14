#include "encryption_functions.h"
#include "Vigenere_table.h"
#include <cstdlib>
#include <string>

std::string encrypt_txt(std::string &plain_text, std::string key, Vigenere_table &vig_tab)
{
	int plain_txt_length = plain_text.length(), 
		key_length = key.length();
	std::string cipher_text;

	if (plain_txt_length > key_length)
	{
		//make key into proper sequence
		int x = plain_txt_length / key_length;
		std::string *temp = new std::string(key);

		//filling integer difference
		for (int i = 0; i < x; i++)
		{
			key += *temp;
		}

		//filling the fractional rest
		if (plain_txt_length - key.length() != 0)
		{
			int diff = plain_txt_length - key.length();
			key += (*temp).substr(0, diff);

			///debug
			std::cout << "\nTest key sequence - length: seq, plain: " << key.length() << ", " << plain_txt_length;
		}
		delete(temp);
	}
	//encrypt
	
	for (int i = 0; i < plain_txt_length; i++)
	{
		/* Can be used instead of whole key sequence
			int j = 0;
			j = j == key_length? 0 : j;
		*/
		cipher_text += vig_tab[std::make_pair(plain_text[i], key[i])];
	}

	return cipher_text;
}

void encrypt_plain_text(PlainText &plain_txt, CipherText &cipher, KeySequence &key, Vigenere_table &vig_tab)
{
	for (int i = 0; i < plain_txt.return_length(); i++)
	{
		//if A-Z
		if (plain_txt[i] >= 65 && plain_txt[i] <= 90)
			cipher.push_front(vig_tab[std::make_pair(plain_txt[i], key[i])]);
		else
			cipher.push_front(plain_txt[i]);
	}
} 