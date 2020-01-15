#pragma once
#include <algorithm> 
#include <string>

class SuffixArray
{
	// Structure to store information of a suffix 
	struct suffix
	{
		int index;
		std::string suff;
	};

	//suffix array
	int *suff_array, 
		size;

	// A comparison function used by sort() to compare two suffixes 
	
public:
	SuffixArray();
	~SuffixArray();

	friend bool comp(const SuffixArray::suffix &a, const SuffixArray::suffix &b);
	
	// This is the main function that takes a string 'txt' of size n as an 
	// argument, builds and return the suffix array for the given string 
	int* build_suffix_array(std::string txt);

	void print_suffix_array();

	void set_size(const int &_size);

};

