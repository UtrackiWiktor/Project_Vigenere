#pragma once
#include "SuffixArray.h"
#include "Text.h"
#include "CipherText.h"

//reduces the suffix array to patterns only grouped alphabetically
std::pair<int*, int> prepare_suffix_array_for_pattern_search(SuffixArray *suffix_array, const Text &text);

//analyzes gaps between repeating portions of text and returns 4 most probable keys. 0 if not found
int* find_key_length(const int* suffix_array, const int &size, CipherText &cipher);