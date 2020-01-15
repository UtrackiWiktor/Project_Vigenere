#pragma once
class SinglyLinkedList
{
	struct Node{
		int val;

		Node *pNext;
	};

	Node *pHead;

public:
	SinglyLinkedList();
	~SinglyLinkedList();

	void add_node(const int &value);
	int count_nodes();
	int operator[](const int &x) const;
};

