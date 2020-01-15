#include "SuffixArray.h"
#include <iostream>
#include <algorithm>


SuffixArray::SuffixArray()
{
}


SuffixArray::~SuffixArray()
{
}

bool comp(const SuffixArray::suffix &a, const SuffixArray::suffix &b)
{
	return a.suff < b.suff ? true : false;
}

// This is the main function that takes a string 'txt' of size n as an 
// argument, builds and return the suffix array for the given string 
int* SuffixArray::build_suffix_array(std::string txt)
{
	// A structure to store suffixes and their indexes
	int txt_length = txt.length();
	
	//suffix suffixes[txt_length];
	suffix *suffixes = new suffix[txt_length];
	
	// Store suffixes and their indexes in an array of structures. 
	// The structure is needed to sort the suffixes alphabatically 
	// and maintain their old indexes while sorting 
	for (int i = 0; i < txt_length; i++)
	{
		suffixes[i].index = i;
		suffixes[i].suff = txt.substr(i, txt_length - i);
	}

	// Sort the suffixes using the comparison function 
	// defined above. 
	std::sort(suffixes, suffixes + txt_length, &comp);

	// Store indexes of all sorted suffixes in the suffix array 
	suff_array = new int[txt_length];

	for (int i = 0; i < txt_length; i++)
		suff_array[i] = suffixes[i].index;
	 

	// Return the suffix array 
	return  suff_array;
}

void SuffixArray::print_suffix_array()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << suff_array[i] << "\n";
	}
}


void SuffixArray::set_size(const int & _size)
{
	size = _size;
}
