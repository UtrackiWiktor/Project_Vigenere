#pragma once
#include "SuffixArray.h"
#include "CipherText.h"
#include <iomanip>


void print_suffix_array_with_strings(const int *suff_array, const Text &text);

void print_suffix_array_with_strings(const int *suff_array, const int &size, const Text &text);

void print_int_array(const int * arr, const int &size);