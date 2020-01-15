#include "cryptoanalysis_functions.h"
#include "SinglyLinkedList.h"

int * prepare_suffix_array_for_pattern_search(const SuffixArray * suffix_array, const Text & text)
{
	//new array to be returned containig only patterns
	int *new_array = nullptr;

	//characters that controls if we are still in the same letter.
	char ctrl_group_char,
		ctrl_current_char;

	//place to put newly found patterns
	SinglyLinkedList *list;
	

	delete(&list);
	return new_array;
}
