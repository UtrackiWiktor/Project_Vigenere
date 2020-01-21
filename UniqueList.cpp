#include "UniqueList.h"
#include <iostream>
#include <iomanip>

void add_unique(int val, Node **pHead)
{
	if (!*pHead)
		(*pHead) = new Node{ val, 1 };

	auto temp = *pHead;

	while (temp)
	{
		if (temp->divisor == val)
		{
			temp->count++;
			return;
		}

		if(temp->pNext)
			temp = temp->pNext;
		else break;
	}

	temp->pNext = new Node{ val, 1 };

	return;
}

void display_divisors(Node *pHead)
{
	if (!pHead)
	{
		std::cout << "\nList empty!\n";
		return;
	}
	auto temp = pHead;
	while (temp)
	{
		std::cout << "Divisor: " << std::setw(3) << temp->divisor << " counted: " << std::setw(3) << temp->count << std::endl;
		temp = temp->pNext;
	}
}