#include <cstdlib>
#include <iostream>
#include <string>
#include "encryption_functions.h"
#include "decryption_functions.h"
#include "debug_functions.h"
#include "Vigenere_table.h"
#include "Text.h"
#include "PlainText.h"
#include "CipherText.h"
#include "KeySequence.h"
#include "SuffixArray.h"

int main()
{
	Vigenere_table vigenere_table;
	vigenere_table.fill_the_table();
	vigenere_table.print_table();


	std::string plain_txt_file = "test_file_plain.txt";
	std::string key_file = "key_file.txt";

	PlainText plain(plain_txt_file);
	std::cout << std::endl << plain << std::endl;

	KeySequence key(key_file);
	key.generate_key_sequence(plain);
	std::cout << key << std::endl << key.return_key_sequence() << std::endl;

	CipherText cipher;
	 
	encrypt_plain_text(plain, cipher, key, vigenere_table);
	cipher.calc_length();
	std::cout << cipher << std::endl;

	PlainText deciphered;
	decrypt_cipher(deciphered, cipher, key);

	std::cout << deciphered << std::endl;

	SuffixArray suff_array; //cipher
	int *suff_cpy = suff_array.build_suffix_array(cipher.return_text());
	suff_array.set_size(cipher.return_length());
	print_suffix_array_with_strings(suff_cpy, cipher);

	SuffixArray suff_plain; //plain
	int *suff_arr_plain_cpy = suff_plain.build_suffix_array(plain.return_text());
	suff_plain.set_size(plain.return_length());
	print_suffix_array_with_strings(suff_arr_plain_cpy, plain);

	delete(suff_cpy);
	system("PAUSE");
	return 0;
}