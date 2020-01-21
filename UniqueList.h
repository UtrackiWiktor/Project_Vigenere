#pragma once

struct Node
{
	int divisor;
	int count;

	Node *pNext;
};

void add_unique(int val, Node **pHead);

void display_divisors(Node *pHead);