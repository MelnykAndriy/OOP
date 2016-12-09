
#pragma once
#include <string.h>

class ListNode
{
	char *data;
	ListNode *prev;
	ListNode *next;
public:
	friend class DoublyLinkedList;
	ListNode(void);
	ListNode(char *_data);
	~ListNode(void);
};

