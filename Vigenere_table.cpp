#include "Vigenere_table.h"
#include <cstdlib>
#include <map>
#include <fstream>
#include <iostream>
#include <string>



Vigenere_table::Vigenere_table()
{
}


Vigenere_table::~Vigenere_table()
{
}



void Vigenere_table::fill_the_table(std::string table_file)
{
	std::fstream file(table_file, std::ios::in);
	if (!file.good())
	{
		std::cout << "\nFile not found!\n";
		return;
	}

	//keeps the letter that is current row index 
	//char row_index;

	//keeps the whole first row to be used as columns indexes
	std::string columns;

	//std::string current_row;

	//getting the index row and returning cursor to the beginning of the file
	getline(file, columns);
	//file.seekg(0, std::ios::beg);

	//filling the table
	for (int i = 0; i <= 25; i++)
	{
		for (int j = 0; j <= 25; j++)
		{
			//vigenere_table[current_row[0]].insert(std::make_pair(columns[i], current_row[i]));

			vigenere_table[i][j] = columns[j];
		}
		getline(file, columns);
	}
	


	file.close();
	return;

}

void Vigenere_table::print_table()
{
	for (int i = 0; i <= 25; i++)
	{
		for (int j = 0; j <= 25; j++)
		{
			std::cout << vigenere_table[i][j];
		}
		std::cout << std::endl;
	}
}

char Vigenere_table::operator[](std::pair<char, char> coord)
{
	if (coord.first <= 'Z' && coord.first >= 'A' && coord.second <= 'Z' && coord.second >= 'A')
		return vigenere_table[static_cast<int>(coord.first) - 65][static_cast<int>(coord.second) - 65];
	else
		return 35;
}