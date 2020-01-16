#pragma once
#include "SuffixArray.h"
#include "Text.h"
#include "CipherText.h"
#include "Vigenere_table.h"

//reduces the suffix array to patterns only grouped alphabetically
std::pair<int*, int> prepare_suffix_array_for_pattern_search(SuffixArray *suffix_array, const Text &text);

//analyzes gaps between repeating portions of text and returns 4 most probable keys. 0 if not found.
//key lengths are divisors of gaps
int* find_key_length(const int* suffix_array, const int &size, CipherText &cipher);

/* n strings must be created, n beeing length of key
	then IoC is found for each letter
	key is guessed.
*/
void frequency_analysis(const int &key_length, CipherText &cipher, Vigenere_table &vigenere_table);

//predicts possible keys
//@param frequency_ciphertext
//@param key_lengths
//@param subtexts table of strings containing substrings from ciphertext
//@param vigenere_table Vigenere table
void predict_key(double* frequency_ciphertext[], const int &key_length, std::string *subtexts, Vigenere_table &vigenere_table, std::string &alphabet);

//bubble sort. Not efficient but quick to write... maybe will change it
void sort_frequency_array(std::pair<int, double> *array, const int &alphabet_length);
