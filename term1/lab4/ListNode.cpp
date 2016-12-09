
#include "ListNode.h"
#pragma warning (disable : 4996)

ListNode::ListNode()
{
	data = NULL;
	prev = NULL;
	next = NULL;
}


ListNode::ListNode(char *_data)
{
	prev = NULL;
	next = NULL;
	if (_data != NULL)
	{
		data = new char[strlen(_data) + 1];
		strcpy(data,_data);
	} else
		data = NULL;
}



ListNode::~ListNode(void)
{
	delete []data;
}


#pragma warning (default : 4996)