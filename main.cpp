#include <cstdlib>
#include <iostream>
#include <string>
#include "encryption_functions.h"
#include "decryption_functions.h"
#include "cryptoanalysis_functions.h"
#include "debug_functions.h"
#include "Vigenere_table.h"
#include "Text.h"
#include "PlainText.h"
#include "CipherText.h"
#include "KeySequence.h"
#include "SuffixArray.h"
#include "input_switches_handling.h"

int main(int argc, char **argv)
{
	std::string plain_txt_file = "";
	std::string key_file = "";
	std::string cipher_input_file;
	std::string cipher_output = "";
	std::string decryption_output = "";

	//file is constant and not meant to be changed
	std::string letters_freq_file = "eng_letters_frequency.txt";

	if (!input_switches(argc, argv, plain_txt_file, key_file, cipher_input_file, cipher_output, decryption_output))
		return 0;


	Vigenere_table vigenere_table;
	vigenere_table.fill_the_table();
	vigenere_table.print_table();

	if (plain_txt_file != "" && key_file != "")
	{
		PlainText plain(plain_txt_file);
		std::cout << std::endl << plain << std::endl;

		KeySequence key(key_file);
		key.generate_key_sequence(plain);
		//std::cout << key << std::endl << key.return_key_sequence() << std::endl;
		CipherText cipher;

		encrypt_plain_text(plain, cipher, key, vigenere_table);
		cipher.calc_length();
		std::cout << std::endl << cipher << std::endl;
		
		if(cipher_output != "")
			cipher.print_to_file(cipher_output);

		//PlainText deciphered;
		//decrypt_cipher(deciphered, cipher, key);
	}
	else if(cipher_input_file != "")
	{
		CipherText cipher_in(cipher_input_file);
		cipher_in.calc_length();

		SuffixArray suff_array; //cipher
		int *suff_cpy = suff_array.build_suffix_array(cipher_in.return_text());
		suff_array.set_size(cipher_in.return_length());
		//print_suffix_array_with_strings(suff_cpy, cipher);

		std::pair<int*, int> prep_suff_and_size = prepare_suffix_array_for_pattern_search(&suff_array, cipher_in);
		if(prep_suff_and_size.second < 35)
			print_suffix_array_with_strings(prep_suff_and_size.first, prep_suff_and_size.second, cipher_in);


		std::cout << std::endl;

		find_key_length(prep_suff_and_size, cipher_in);

		int chosen_key_length = 0;
		std::cout << "\nWhat key length do you think is the most probable?\n";
		std::cin >> chosen_key_length;

		frequency_analysis(chosen_key_length, cipher_in, vigenere_table, letters_freq_file);

		std::cout << "\nWhat do you think the key is?\n";
		std::string chosen_key;
		std::cin >> chosen_key;

		KeySequence chosen_key_sequence;
		chosen_key_sequence.change_key(chosen_key);
		chosen_key_sequence.generate_key_sequence(cipher_in);

		PlainText deciphered;

		decrypt_cipher(deciphered, cipher_in, chosen_key_sequence);
		std::cout << deciphered;

		if (decryption_output != "")
		{
			std::fstream file_co(decryption_output, std::ios::out | std::ios::trunc);
			if (!file_co.good())
			{
				std::cout << "\nOutput file not found! Name: \n" << cipher_output << std::endl;
				return 0;
			}
			file_co << deciphered << std::endl << "Key: " << chosen_key_sequence;
		}


		delete[] suff_cpy;
	}
	else
	{
		std::cout << "Incorrect file names\n";
	}

	system("PAUSE");
	return 0;
}