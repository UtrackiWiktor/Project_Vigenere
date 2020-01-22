#include "input_switches_handling.h"
#include <iostream>
#include <string>


bool input_switches(int argc, char ** argv, std::string &plaintxt, std::string &key, std::string &cipher, std::string &encrypt_out, std::string &decrypt_out)
{
	if (argc < 2)
	{
		print_usage_message();
		return false;
	}

	int i = 1, opt;

	while (i < argc - 1)
	{
		opt = argv[i][1];
		switch(opt)
		{
		case 'p':
			plaintxt = argv[++i];
			//std::cout << plaintxt << "Plaintxt: " << std::endl;
			i++;
			break;
		case 'k':
			key = argv[++i];
			//std::cout << key << "Key: \n" << std::endl;
			i++;
			break;
		case 'c':
			cipher = argv[++i];
			//std::cout << "Cipher: \n" << std::endl;
			i++;
			break;
		case 'o':
			decrypt_out = argv[++i];
			//std::cout << "Decrypt out: \n" << decrypt_out << std::endl;
			i++;
			break;
		case 'q':
			encrypt_out = argv[++i];
			//std::cout << "encrypt_out\n" << std::endl;
			i++;
			break;

		default:
			//std::cout << "Nnknown option \n" << (char)opt << std::endl;
			i += 2;
			break;
		}
	}
	return true;
}


void print_usage_message()
{
	std::cout << "Usage:\n-p input file with plaintext\n-k input file with key\n-c input file with cipher\n-o output file for decryption\n-q output file for encryption";
	std::cout << "\nCombinations of plaintext, key [, output for encryption] or cipher [, output for decryption] are accepted.\n";
}