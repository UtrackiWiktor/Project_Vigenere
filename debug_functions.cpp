#include "debug_functions.h"

void print_suffix_array_with_strings(const int * suff_array, const Text & text)
{
	std::cout << "\nSuffix array:\n";

	int size = text.return_length();

	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(std::to_string(size).length() + 1) << suff_array[i] << ": \"" << text.substr(suff_array[i], size - suff_array[i]) << "\"\n";
	}
}

void print_suffix_array_with_strings(const int * suff_array, const int & size, const Text &text)
{
	std::cout << "\nSuffix array:\n";

	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(std::to_string(size).length() + 1) << suff_array[i] << ": \"" << text.substr(suff_array[i], text.return_length() - suff_array[i]) << "\"\n";
	}
}


void print_int_array(const int * arr, const int &size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << std::endl;
	}
}
