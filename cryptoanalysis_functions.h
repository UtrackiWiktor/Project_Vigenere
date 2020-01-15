#pragma once
#include "SuffixArray.h"
#include "Text.h"

int* prepare_suffix_array_for_pattern_search(const SuffixArray *suffix_array, const Text &text);
