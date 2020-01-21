#include "cryptoanalysis_functions.h"
#include "SinglyLinkedList.h"
#include "UniqueList.h"
#include <math.h>
#include <fstream>
#include <iomanip>

//no of letters to be checked
#define _NUMBER_OF_PROB_LETTERS 16

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
		if ((ctrl_current_char[0] >= 48 && ctrl_current_char[0] <= 57) || (ctrl_current_char[1] >= 48 && ctrl_current_char[1] <= 57))
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

void find_key_length(std::pair<int*, int> &prep_suffix_array, CipherText & cipher)
{
	kasiski_method(prep_suffix_array, cipher);

	return;
}

void frequency_analysis(const int & key_length, CipherText & cipher, Vigenere_table &vigenere_table, std::string &letter_freq_eng_filename)
{


	std::string *subtexts = new std::string[key_length];

	//opening frequency file and saving content into array
	std::fstream file(letter_freq_eng_filename, std::ios::in);
	if (!file.good())
	{
		std::cerr << "\nCould not find letters frequency file!\n";
		return;
	}

	char plain_txt_letter;
	double freq;
	int index = 0;
	std::pair<char, double> letter_freq_lang[26];

	//takes frequencies from a file and puts it into the array
	while (file >> plain_txt_letter && file >> freq)
	{
		letter_freq_lang[index].first = plain_txt_letter;
		letter_freq_lang[index].second = (freq /= 100);
		index++;
	}

	//// -->	CHI SQUARED METHOD	  <-- ////

	//divides string into n cosets
	//i is number of substring
	for (int i = 0; i < key_length; i++)
	{
		//j is no of pos in new ciphertext substr
		for(double j = 0; j <= ceil((cipher.return_length() - 1 - i) / key_length) ; j++)
		{
			subtexts[i] += cipher[i + j * key_length];
		}
	}

	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	double **letter_frequencies = new double*[key_length];
	for (int i = 0; i < key_length; i++)
		letter_frequencies[i] = new double[alphabet.length()];

	//2d array for chi values
	double **chi_squared_val = new double*[key_length];

	for (int i = 0; i < key_length; i++)
		chi_squared_val[i] = new double[26]{ 0 };

	//loop for each coset
	for (int i = 0; i < key_length; i++)
	{
		//counting frequencies of letters in substrings. 
		for (int shift = 0; shift < 26; shift++)
		{
			//std::cout << "coset: " << subtexts[i] << std::endl;
			for (size_t j = 0; j < alphabet.length(); j++)
			{
				//calc frequency
				letter_frequencies[i][j] = static_cast<double>(std::count(subtexts[i].begin(), subtexts[i].end(), alphabet[j])) / subtexts[i].length();
				//adding to chi value		
				//sum:(fi - Fi) / Fi
				chi_squared_val[i][shift] += pow((letter_frequencies[i][j] - return_frequency_of_a_letter(alphabet[j], *letter_freq_lang)), 2) / return_frequency_of_a_letter(alphabet[j], *letter_freq_lang); // -freq_of that letter in eng squared over freq in eng
				//std::cout << "i = " << i << ", shift = " << shift << ", chi_squared_value = " << chi_squared_val[i][shift] << std::endl;
			}
			shift_coset_left_once(subtexts[i]);
			
		}
	}
	print_chi_squared_method_results(chi_squared_val, key_length);

	//delete dynamic vars!
	delete []subtexts;
	for (int i = 0; i < key_length; i++)
		delete(letter_frequencies[i]);
	delete(letter_frequencies);
}

void sort_frequency_array(std::pair<int, double> &array, const int &alphabet_length)
{
	std::pair<int, double> temp;

	for (int i = 0; i < alphabet_length - 1; i++)
	{
		for (int j = 0; j < alphabet_length - 1; j++)
		{
			if ((&array)[j].second < (&array)[j + 1].second)
			{
				temp = (&array)[j];
				(&array)[j] = (&array)[j + 1];
				(&array)[j + 1] = temp;
			}
		}
	}
}

char find_key_letter(char & letter_of_ciphertext, char & plain_text_letter, Vigenere_table & vigenere_table)
{
	char temp;
	//for each letter in alphabet chks if x coord is equal to plain txt letter and if it is returns x coord
	for (int i = 0; i < 26; i++)
	{
		temp = vigenere_table[std::make_pair(plain_text_letter, 'A' + i)];
		if (vigenere_table[std::make_pair(plain_text_letter, 'A' + i)] == letter_of_ciphertext)
			return 'A' + i;
	}

	return '#';
}

void find_divisors(int number, Node **pHead)
{
	for (int i = 2; i <= number; i++)
	{
		if (number % i == 0)
			add_unique(i, pHead);
		if (i == 20)
			return;
	}
}

void kasiski_method(std::pair<int*, int> &prep_suffix_array, const CipherText &cipher)
{
	std::string ctrl_group_char,
		ctrl_current_char;

	//place to put divisors found
	Node *list = nullptr;

	//flag; 1 if pattern found in current itaration, 0 if not
	bool pattern = false;

	//group index
	int group_index;

	for (int i = 0; i < prep_suffix_array.second - 1;)
	{
		if (!pattern)
		{
			//sets the group ctrl var (takes 2 first letters)
			ctrl_group_char = cipher[prep_suffix_array.first[i]];
			ctrl_group_char += cipher[prep_suffix_array.first[i] + 1];
			group_index = prep_suffix_array.first[i];
			i++; //incr for current element
		}

		//setts current character
		ctrl_current_char = cipher[prep_suffix_array.first[i]];
		ctrl_current_char += cipher[prep_suffix_array.first[i] + 1];

		//if current elem is part of pattern set pattern flag and find divisors
		if (ctrl_group_char == ctrl_current_char)
		{
			pattern = true;
			find_divisors(abs(prep_suffix_array.first[i] - group_index), &list);
			i++;
		}
		else
		{
			//when it's end of the pattern, remove pattern flag
			pattern = false;
		}
	}

	std::cout << "\nKasiski method key length search results:\n";
	display_divisors(list);
}

double return_frequency_of_a_letter(char &letter, std::pair<char, double> &letter_freq_lang)
{
	for (int i = 0; i < 26; i++)
	{
		if ((&letter_freq_lang)[i].first == letter)
			return (&letter_freq_lang)[i].second;
	}

	return -1.0;
}

void shift_coset_left_once(std::string &coset)
{
	for (int i = 0; i < coset.length(); i++)
	{
		coset[i] = coset[i] - 1 < 'A' ? coset[i] + 25 : coset[i] - 1;
	}
}

void print_chi_squared_method_results(double **chi_squared_val, const int &key_length)
{
	std::string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::cout << "\nResults of chi squared method analysis:\n\n";
	std::cout << "Letter" << " |  Each collumn is one coset of the ciphertext\n";
	std::cout << "----------------------------------------------------------\n";
	for (int i = 0; i < 26; i++)
	{
		std::cout << "   " << alph[i] << "   |";
		for (int j = 0; j < key_length; j++)
		{
			std::cout << std::setprecision(5) << std::setw(9) << chi_squared_val[j][i];
		}
		std::cout << std::endl;
	}
}
