#include "SinglyLinkedList.h"



SinglyLinkedList::SinglyLinkedList()
{
	pHead = nullptr;
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


int SinglyLinkedList::operator[](const int &x) const
{
	if (!pHead)
		return 0;
	
	if (x == 0)
		return pHead->val;

	int index = 0;
	auto temp = pHead;

	while (temp->pNext)
	{
		temp = temp->pNext;
		index++;
		if (x == index)
			return temp->val;
	}
	return 0;
}