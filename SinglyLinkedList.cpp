#include "SinglyLinkedList.h"



SinglyLinkedList::SinglyLinkedList()
{
}


SinglyLinkedList::~SinglyLinkedList()
{
	delete(pHead);
}

void SinglyLinkedList::add_node(const int & value)
{
	if (!pHead)
	{
		pHead = new Node{ value, nullptr };
		return;
	}

	auto temp = pHead;

	while (temp->pNext)
		temp = temp->pNext;

	temp->pNext = new Node{ value, nullptr };
}

int SinglyLinkedList::count_nodes()
{
	if (!pHead)
		return 0;

	auto temp = pHead;
	int c = 1;

	while (temp->pNext)
	{
		temp = temp->pNext;
		c++;
	}

	return c;
}
