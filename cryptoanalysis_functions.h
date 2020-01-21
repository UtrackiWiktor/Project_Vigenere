#pragma once
#include "SuffixArray.h"
#include "Text.h"
#include "CipherText.h"
#include "Vigenere_table.h"
#include "UniqueList.h"

//reduces the suffix array to patterns only grouped alphabetically
std::pair<int*, int> prepare_suffix_array_for_pattern_search(SuffixArray *suffix_array, const Text &text);

//analyzes gaps between repeating portions of text and returns 4 most probable keys. 0 if not found.
//key lengths are divisors of gaps
void find_key_length(std::pair<int*, int> &prep_suffix_array, CipherText &cipher);

/* n strings must be created, n beeing length of key
	then IoC is found for each letter
	key is guessed.
	>>>>!!!must take freq_letters.txt as parameter!!!<<<<
*/
void frequency_analysis(const int &key_length, CipherText &cipher, Vigenere_table &vigenere_table, std::string &letter_freq_eng_filename);

//predicts possible keys
//@param frequency_ciphertext
//@param key_lengths
//@param subtexts table of strings containing substrings from ciphertext
//@param vigenere_table Vigenere table
void predict_key(double* frequency_ciphertext[], const int &key_length, std::string *subtexts, Vigenere_table &vigenere_table, std::string &alphabet, std::string &letters_freq_eng_filename);

//bubble sort. Not efficient but quick to write... maybe will change it
void sort_frequency_array(std::pair<int, double> &array, const int &alphabet_length);

//returns key letter given plain and cipher txts letters
char find_key_letter(char &letter_of_ciphertext, char &plain_text_letter, Vigenere_table &vigenere_table);

//Finds divisors of a number and puts them into unquie list counting occs
void find_divisors(int number, Node **pHead);

//1st Kasiski method
void kasiski_method(std::pair<int*, int> &prep_suffix_array, const CipherText &cipher);

double return_frequency_of_a_letter(char &letter, std::pair<char, double> &letter_freq_lang);

void shift_coset_left_once(std::string &coset);

void print_chi_squared_method_results(double **chi_squared_val, const int &key_length);
