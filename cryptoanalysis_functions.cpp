#include "cryptoanalysis_functions.h"
#include "SinglyLinkedList.h"
#include <math.h>

std::pair<int *, int> prepare_suffix_array_for_pattern_search(SuffixArray * suffix_array, const Text & text)
{
	//new array to be returned containig only patterns
	int *new_array = nullptr;

	//characters that controls if we are still in the same letter.
	std::string ctrl_group_char,
		ctrl_current_char;

	//place to put newly found patterns
	SinglyLinkedList *list = new SinglyLinkedList;
	
	//flag; 1 if pattern found in current itaration, 0 if not
	bool pattern = false;

	//group index
	int group_index,
		number_of_suffixes_found = 0;

	for (int i = 0; i < text.return_length() - 1;)
	{
		if (!pattern)
		{
			//sets the group ctrl var (takes 2 first letters)
			ctrl_group_char = text[(*suffix_array)[i]];
			ctrl_group_char += text[(*suffix_array)[i] + 1];
			group_index = (*suffix_array)[i];

			//if digit then ommit
			if ((ctrl_group_char[0] >= 48 && ctrl_group_char[0] <= 57) || (ctrl_group_char[1] >= 48 && ctrl_group_char[1] <= 57))
			{
				i++;
				continue;
			}

			i++; //incr for current element
		}
		//setts current character
		ctrl_current_char = text[(*suffix_array)[i]];
		ctrl_current_char += text[(*suffix_array)[i] + 1];

		//if digit then ommit
		if ((ctrl_current_char[0] >= 48 && ctrl_current_char[0] <= 57) || (ctrl_current_char[1] >= 47 && ctrl_current_char[1] <= 57))
		{
			i++;
			continue;
		}

		//if current elem is part of pattern set pattern flag and add suffix to list
		if (ctrl_group_char == ctrl_current_char && ((*suffix_array)[i] - group_index != 1 && (*suffix_array)[i] - group_index != -1))
		{
			pattern = true;
			list->add_node((*suffix_array)[i]);
			number_of_suffixes_found++;
			i++;
		}
		else
		{
			//if it's end of pattern, add ctrl_group suffix to list
			if (pattern)
			{
				list->add_node(group_index);
				number_of_suffixes_found++;
				pattern = false;
				//i++;
			}
		}
	}

	//protection against patterns in last-but-one pair which would not be normally included
	if (pattern)
	{
		list->add_node(group_index);
		number_of_suffixes_found++;
		pattern = false;
		//i++;
	}

	//now list contains suffixes with patterns. 
	//putting it into new_array:
	new_array = new int[number_of_suffixes_found];

	for (int i = 0; i < number_of_suffixes_found; i++)
	{
		new_array[i] = (*list)[i]; 
	}

	delete(list);
	return std::make_pair(new_array, number_of_suffixes_found);
}

int * find_key_length(const int * suffix_array, const int &size, CipherText & cipher)
{
	int *keys = new int[4];



	return keys;
}

void frequency_analysis(const int & key_length, CipherText & cipher, Vigenere_table &vigenere_table)
{
	std::string *subtexts = new std::string[key_length];

	//divides string into n strings
	//i is no of substring
	for (int i = 0; i < key_length; i++)
	{
		//j is no of pos in new ciphertext substr
		for(double j = 0; j <= ceil((cipher.return_length() - 1 - i) / 3) ; j++)
		{
			subtexts[i] += cipher[i + j * key_length];
		}
	}

	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	double **letter_frequencies = new double*[key_length];
	for (int i = 0; i < key_length; i++)
		letter_frequencies[i] = new double[alphabet.length()];


	//counting frequencies of letters in substrings
	for (int i = 0; i < key_length; i++)
	{
		for (int j = 0; j < alphabet.length(); j++)
		{
			//if(static_cast<double>(std::count(subtexts[i].begin(), subtexts[i].end(), alphabet[j])) / (cipher.return_length() / 3))
			//	std::cout << "txt " << i << ", letter: " << alphabet[j] << ": " << static_cast<double>(std::count(subtexts[i].begin(), subtexts[i].end(), alphabet[j])) / (cipher.return_length()/3) << std::endl;
			letter_frequencies[i][j] = static_cast<double>(std::count(subtexts[i].begin(), subtexts[i].end(), alphabet[j])) / cipher.return_length();
			if (letter_frequencies[i][j] != 0)
				std::cout << "txt " << i << ", letter: " << alphabet[j] << " frequency: " << letter_frequencies[i][j] << std::endl;
		}
		std::cout << "- - - - - - - \n";
	}

	//pass vigenere table to the funcion!!
	predict_key(letter_frequencies, key_length, subtexts, vigenere_table, alphabet);


	//delete dynamic vars!


	////////////////////////////////// <------- INDEX OF COINCIDENCE
	
	//double *ioc = new double[key_length]{0};
	////double ioc[3]{ 0 };
	//for (int i = 0; i < key_length; i++)
	//{
	//	for (int j = 0; j < alphabet.length(); j++)
	//	{
	//		//std::cout << "\n ioc[" << i << "] = " << static_cast<double>((letter_frequencies[i][j] * (letter_frequencies[i][j] - 1))) / (cipher.return_length() * (cipher.return_length() - 1)) << std::endl;
	//		(ioc)[i] += abs(static_cast<double>((letter_frequencies[i][j] * (letter_frequencies[i][j] - 1))) / (cipher.return_length() * (cipher.return_length() - 1)));
	//	}
	//}

	////std::cout.precision(5);
	////print ioc
	//for (int i = 0; i < key_length; i++)
	//{
	//	std::cout << "\nText " << i << ": IoC = " << (ioc)[i] << std::endl;
	//}
}

void predict_key(double * frequency_ciphertext[], const int & key_length, std::string * subtexts, Vigenere_table & vigenere_table, std::string &alphabet)
{
	//array of arrays of 4 most probable key letters in desc order
	//each instance of parent array for one letter of the key
	char** probable_key_letters = new char*[key_length];
	for (int i = 0; i < key_length; i++)
	{
		probable_key_letters[i] = new char[4];
	}

	//array for sorting freqs
	std::pair<int, double> *temp = new std::pair<int, double>[alphabet.length()];

	//sorting freqs
	for (int i = 0; i < key_length; i++)
	{
		//fill temp
		for (int j = 0; j < alphabet.length(); j++)
		{
			temp[i].first = i;
			temp[i].second = (*frequency_ciphertext)[i];
		}

		//sorting small array of current substr
		sort_frequency_array(temp, alphabet.length());

		for (int j = 0; j < 4; j++)
		{
			probable_key_letters[i][j];
		}
	}

	//delete dynamic vars!!!

}

void sort_frequency_array(std::pair<int, double> *array, const int &alphabet_length)
{
	std::pair<int, double> temp;

	for (int i = 0; i < alphabet_length - 1; i++)
	{
		for (int j = 0; j < alphabet_length - 1; j++)
		{
			if (array[j].second < array[j + 1].second)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}
