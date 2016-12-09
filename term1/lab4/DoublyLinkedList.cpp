
#include "DoublyLinkedList.h"

#define DEL_NODE(ptr_to_del)	ListNode* tmp_del = ptr_to_del; \
								ptr_to_del = ptr_to_del->next; \
								tmp_del->prev->next = ptr_to_del; \
								if (ptr_to_del) \
									ptr_to_del->prev = tmp_del->prev; \
								delete tmp_del;

#define PUSH_NODE(ptr_to_pred,node) 	ListNode* insert_nd = new ListNode(node.data); \
										insert_nd->next = ptr_to_pred->next; \
										insert_nd->prev = ptr_to_pred; \
										ptr_to_pred->next = insert_nd; \
										if (insert_nd->next != NULL) \
											insert_nd->next->prev = insert_nd;	

DoublyLinkedList::DoublyLinkedList(void)
{
	head = new ListNode();
}

DoublyLinkedList::~DoublyLinkedList(void)
{
	this->clear();
	delete head;
}

int DoublyLinkedList::size()
{
	ListNode* iter = head->next;
	int size = 0;
	while (iter != NULL)
	{
		iter = iter->next;
		size++;
	}
	return size;
}

bool DoublyLinkedList::empty()
{
	if (NULL == head->prev && NULL == head->next)
		return true;
	return false;
}

ListNode* DoublyLinkedList::nth(int n)
{
	if (empty() == 1 || n < 0 || n >= size())
		return NULL;

	int i;
	ListNode* iter = head;

	for (i = 0; i <= n; i++)
		iter = iter->next;
	return iter;
}

void DoublyLinkedList::clear()
{
	ListNode* iter = head->next;
	ListNode* tmp_del;

	while (iter != NULL)
	{
		tmp_del = iter;
		iter = iter->next;
		delete tmp_del;
	}
	head->next = NULL;
	head->prev = NULL;
}

void DoublyLinkedList::push_front(const ListNode &nd)
{
	PUSH_NODE(head,nd);
}

void DoublyLinkedList::push_back(const ListNode &nd)
{
	if (empty())
	{
		push_front(nd);
		return;
	}
	ListNode* insert_node;
	ListNode* iter = nth( size() - 1);
	insert_node = new ListNode(nd.data);
	iter->next = insert_node;
	insert_node->prev = iter;
}

void DoublyLinkedList::pop_front()
{
	if (empty())
		return;

	DEL_NODE(head->next);
}

void DoublyLinkedList::pop_back()
{
	if (empty())
		return;
	ListNode* tmp_del = nth( size() - 1 );
	tmp_del->prev->next = NULL;
	delete tmp_del;
}

void DoublyLinkedList::insert_ord( const ListNode &nd)
{
	if (empty())
	{
		push_front(nd);
		return;
	}

	ListNode* iter = head->next;

	while(iter != NULL)
	{
		if (strcmp(iter->data,nd.data) > 0)
		{
			iter = iter->prev;
			PUSH_NODE(iter,nd);
			//ListNode* insert_nd = new ListNode(nd.data);
			//insert_nd->prev = iter->prev;
			//insert_nd->next = iter;
			//iter->prev = insert_nd;
			//insert_nd->prev->next = insert_nd;
			return;
		}
		iter = iter->next;
	}
	push_back(nd);
}

void DoublyLinkedList::sort()
{
	if (empty())
		return;

	ListNode* tmp_head = new ListNode();
	ListNode* iter;
	ListNode* tmp_del;

	tmp_head->next = head->next;
	head->next->prev = tmp_head;
	head->next = NULL;

	iter = tmp_head->next;
	while (iter != NULL)
	{
		insert_ord(*iter);
		tmp_del = iter;
		iter = iter->next;
		delete tmp_del;
	}
	delete tmp_head;
}

bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd)
{
	ListNode* iter = head->next;

	while ( iter != NULL)
	{
		if (strcmp(dat,iter->data) == 0)
		{
			PUSH_NODE(iter,nd);			
			return true;
		}
		iter = iter->next;
	}
	return false;
}

DoublyLinkedList& DoublyLinkedList::operator= (const DoublyLinkedList &lst)
{
	this->clear();
	ListNode* iter = lst.head->next;

	while (iter != NULL)
	{
		push_back(*iter);
		iter = iter->next;
	}
	
	return *this;
}

void DoublyLinkedList::merge(DoublyLinkedList &lst)
{
	sort();
	ListNode* iter;
	
	while (lst.empty() != 1)
	{
		iter = lst.nth(0);
		insert_ord(* iter);
		lst.pop_front();
	}
}

void DoublyLinkedList::erase(char *dat)
{
	ListNode *iter = head->next;

	while (iter != NULL)
	{
		if (strcmp(dat,iter->data) == 0)
		{
			DEL_NODE(iter);
			continue;
		}
		iter = iter->next;
	}
}

void DoublyLinkedList::unique()
{
	if (empty())
		return;

	sort();
	ListNode* iter = head->next;
	char *pred = iter->data;

	while (iter->next != NULL)
	{
		iter = iter->next;
		if (strcmp(pred,iter->data) == 0)
		{
			DEL_NODE(iter);
			if (iter == NULL)
				return;
			iter = iter->prev;
		}
		pred = iter->data;
	}
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last)
{
	if ( first < 0 || last >= dl.size() || first > last)
		return;

	ListNode* iter = dl.nth(first);

	for(int i = first; i <= last; i++)
	{
		push_back(*iter);
		DEL_NODE(iter);
	}
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl)
{
	DoublyLinkedList tmp_dlist;
	tmp_dlist = dl;
	splice(where,dl,0,tmp_dlist.size());
}

void DoublyLinkedList::splice(int where,const DoublyLinkedList &dl, int first, int last)
{
	DoublyLinkedList tmp_dlist;
	tmp_dlist = dl;

	if ( first < 0 || last >= tmp_dlist.size() || first > last
		|| where >= size() || where < 0)
		return;

	ListNode* iterFrom = tmp_dlist.nth(first);;
	ListNode* iterTo = nth(where);

	for (int i = first; i <= last; i++)
	{
		PUSH_NODE(iterTo,(*iterFrom));
		iterFrom = iterFrom->next;
		iterTo = iterTo->next;
	}
}

void DoublyLinkedList::print()
{
	if (empty()) 
	{
		printf("List is empty \n");
		return;
	}

	ListNode* iter = head->next;

	puts("");
	while (iter != NULL)
	{
		puts(iter->data);
		iter = iter->next;
	}
	puts("");
}

void DoublyLinkedList::print_bkw()
{
	if (empty()) 
	{
		printf("List is empty \n");
		return;
	}
	ListNode* iter = head->next;
	while(iter->next != NULL)
		iter = iter->next;

	puts("");
	while(iter != head)
	{
		puts(iter->data);
		iter = iter->prev;
	}
	puts("");
}

