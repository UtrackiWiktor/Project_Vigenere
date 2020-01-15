#include "cryptoanalysis_functions.h"
#include "SinglyLinkedList.h"

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
		if ((ctrl_current_char[0] >= 48 && ctrl_current_char[0] <= 57) || (ctrl_current_char[1] >= 47 && ctrl_current_char[1] <= 57))
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

int * find_key_length(const int * suffix_array, const int &size, CipherText & cipher)
{
	int *keys = new int[4];



	return keys;
}
