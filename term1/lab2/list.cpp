/************************************************************************
 *file: stringtest.cpp
 *synopsis: definition of functions
 *author: Melnyk Andriy
 *written: 29/10/2013
 *last modified: 29/10/2013
 ************************************************************************/

#include "list.h"

int empty(const CNode *head)
// return value 1 -> if list empty 
//              0 -> if list not empty
//              -1 -> if head = NULL or 
{
	if  (head == NULL) return -1;
	if ( head == head->next && head == head->prev)
		return 1;
	return 0;
}

CNode *get_node (const CNode *head, int id )
{
	if (head == NULL) return NULL;
	
	CNode* iter;
	iter = head->next;
	while (iter != head)
	{
		if (id == iter->id)
			return iter;
		iter = iter->next;
	}

	return NULL;
}

void append2list (CNode *head, const CNode *pn)
{
	if ( head == NULL || pn == NULL) return;

	CNode* add = (CNode *) malloc (sizeof(CNode));
	add->id = pn->id;
	
	CNode* iter = head;
		
	while (iter->next != head)
		iter = iter->next;
	iter->next = add;
	add->prev = iter;
	add->next = head;
	head->prev = add;

}

void del_node (CNode *head, int id)
{
	if (head == NULL) return;

	CNode* iter;
	CNode* tmp_del;
	iter = head->next;
	while (iter != head)
	{
		if (id == iter->id)
		{
			iter->next->prev = iter->prev;
			iter->prev->next = iter->next;
			tmp_del = iter;
			iter = iter->next;
			free(tmp_del);
		} else
			iter = iter->next;
	}
}

void clear(CNode *head)
{
	if (head == NULL) return;
	
	CNode* iter;
	CNode* tmp_del;
	iter = head->next;
	while (iter != head)
	{
		tmp_del = iter;
		iter = iter->next;
		free(tmp_del);
	}
	head ->next = head;
	head ->prev = head;
}

void ins_node (CNode *head, const CNode *pn, int id)
{
	if ( head == NULL || pn == NULL) return;

	CNode* iter = head;

	iter = head->next;
	while (iter != head)
	{
		if (id == iter->id)
		{
			CNode* add = (CNode *) malloc (sizeof(CNode));
			add->id = pn->id;

			add->next = iter;
			add->prev = iter->prev;
			iter->prev->next = add;
			iter->prev= add;
		}
		iter = iter->next;
	}
}

void reverse(CNode *head)
{
	if (head == NULL) return;

	CNode* iter;
	CNode* tmp;

	iter = head->next;
	while (iter != head)
	{
		tmp = iter->next;
		iter->next = iter->prev;
		iter->prev = tmp;
		iter = tmp;
	}
	tmp = head->next;
	head->next = head->prev;
	head->prev = tmp;
}

void print_list(const CNode *head )
{
	if (head == NULL) return;

	CNode* iter;
	iter = head->next;
	while (iter != head)
	{
		printf("%d ",iter->id);
		iter = iter->next;
	}
	printf("\n");
}

// assisted function
void add_all_not_included (CNode *new_head,const CNode *head1, const CNode *head2)
// adds to the list to which indicates 'new_head'
// All elements List1->head1 are not included in the list2->head2
{
	if (head1 == NULL) return;
	CNode* iter;
	CNode* add_el;
	
	iter = head1->next;

	while (iter != head1)
	{
		if (get_node(head2,iter->id) == NULL)
		{
			add_el = (CNode *) malloc (sizeof(CNode));
			add_el->id = iter->id;
			append2list (new_head,add_el);
		}
		iter = iter->next;
	}
}
//

CNode* merge_unique(const CNode *head1, const CNode *head2)
{
	CNode* new_head = (CNode*) malloc (sizeof(CNode));
	new_head ->next = new_head;
	new_head ->prev = new_head;
	
	add_all_not_included(new_head,head1,head2);
	add_all_not_included(new_head,head2,head1);

	return new_head;
}

void unique(CNode *head)
{
	if (head == NULL) return;

	CNode* iter;
	CNode* tmp_del;
	iter = head->next;
	while (iter->next != head)
	{
		if (iter->id == iter->next->id)
		{
			iter->next->prev = iter->prev;
			iter->prev->next = iter->next;
			tmp_del = iter;
			iter = iter->next;
			free(tmp_del);
		} else 
			iter = iter->next;
	}
}
