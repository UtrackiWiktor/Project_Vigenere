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

int main(int argc, char **argv)
{
	Vigenere_table vigenere_table;
	vigenere_table.fill_the_table();
	vigenere_table.print_table();


	std::string plain_txt_file = "test_file_plain.txt";
	std::string key_file = "key_file.txt";
	std::string letters_freq_file = "eng_letters_frequency.txt";

	PlainText plain(plain_txt_file);
	std::cout << std::endl << plain << std::endl;

	KeySequence key(key_file);
	key.generate_key_sequence(plain);
	//std::cout << key << std::endl << key.return_key_sequence() << std::endl;

	CipherText cipher;
	 
	encrypt_plain_text(plain, cipher, key, vigenere_table);
	cipher.calc_length();
	std::cout << std::endl << cipher << std::endl;
	cipher.print_to_file("cipher_out.txt");

	PlainText deciphered;
	decrypt_cipher(deciphered, cipher, key);

	//std::cout << deciphered << std::endl;

	SuffixArray suff_array; //cipher
	int *suff_cpy = suff_array.build_suffix_array(cipher.return_text());
	suff_array.set_size(cipher.return_length());
	//print_suffix_array_with_strings(suff_cpy, cipher);

	std::pair<int*, int> prep_suff_and_size = prepare_suffix_array_for_pattern_search(&suff_array, cipher);
	print_suffix_array_with_strings(prep_suff_and_size.first, prep_suff_and_size.second, cipher);


	std::cout << std::endl;

	find_key_length(prep_suff_and_size, cipher);

	int chosen_key_length = 0;
	std::cout << "\nWhat key length do you think is the most probable?\n";
	std::cin >> chosen_key_length;

	frequency_analysis(chosen_key_length, cipher, vigenere_table, letters_freq_file);

	std::cout << "\nWhat do you think the key is?\n";
	std::string chosen_key;
	std::cin >> chosen_key;
	KeySequence chosen_key_sequence;
	chosen_key_sequence.change_key(chosen_key);
	chosen_key_sequence.generate_key_sequence(cipher);

	decrypt_cipher(deciphered, cipher, chosen_key_sequence);
	std::cout << deciphered;

	delete(suff_cpy);

	system("PAUSE");
	return 0;
}