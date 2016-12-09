/************************************************************************
 *file: stringtest.cpp
 *synopsis: test-drive
 *author: Melnyk Andriy
 *written: 23/10/2013
 *last modified: 24/10/2013
 ************************************************************************/

#include "list.h"

CNode* head = (CNode*) malloc (sizeof(CNode));
CNode* pn = (CNode*) malloc (sizeof(CNode));

void main ()
{
	head ->next = head;
	head ->prev = head;
	printf("Testing list functions \n\n");

	printf("Test empty. Return value : 1 -> if list empty \n");
    printf("                         : 0 -> if list not empty \n");
	printf("                         :-1 -> if head = NULL \n");
	printf("Result  %d \n\n",empty(head));

	printf("Test append2list. Return value - void\n");
	for (int i =0; i <=5; i++)
	{
		pn->id =i;
		append2list(head,pn);
	}
	free(pn);
	printf("Input : *pn (id = 0-5 prev = ? next = ?) \n");
	printf("Modified list -> ");
	print_list(head); printf("\n");

	printf("Test get_node. Return value - CNode* \n");
	printf("Input : id = 3 \n");
	pn = get_node(head,3);
	if (pn != NULL) printf("Returned node id is %d \n\n",pn->id);

	printf("Test del_node. Return value -void\n");
	printf("Input : id = 3 \n");
	del_node(head,3);
	printf("Modified list -> ");
	print_list(head); printf("\n");

	printf("Test ins_node. Return value void\n");
	printf("Input : *pn (id = 99 prev = ? next = ?) id = 4 \n");
	pn = (CNode*) malloc (sizeof(CNode));
	pn->id = 99;
	ins_node(head,pn,4);
	printf("Modified list -> ");
	print_list(head); printf("\n");

	printf("Test reverse. Return value void\n");
	reverse(head);
	printf("Modified list -> ");
	print_list(head); printf("\n");

	printf("Test merge_unique. Return value CNoe*->(new-list) \n");
	CNode* tmp_head = (CNode*) malloc (sizeof(CNode));
	tmp_head ->next = tmp_head;
	tmp_head ->prev = tmp_head;
	for (int i = 4;  i <=7; i++)
	{
		pn->id =i;
		append2list(tmp_head,pn);
	}
	printf("Input :Head to List1 ->");
	print_list(head);
	printf("Input :Head to List2 ->");
	print_list(tmp_head);
	printf("New List -> ");
	print_list(merge_unique(head,tmp_head)); printf("\n");
	clear(tmp_head);

	printf("Test unique. Return value void \n");
	for (int i = 4;  i <=6; i++)
	{
		pn->id =i;
		for (int j = 1; j<=3; j++)
			append2list(tmp_head,pn);
	}
	free(pn);
	printf("Input :Head to List ->");
	print_list(tmp_head);
	unique(tmp_head);
	printf("Modified list -> ");
	print_list(tmp_head); printf("\n");
	clear(tmp_head);
	free(tmp_head);

	printf("Test clear. Return value void \n");
	clear(head);
	printf("The list is empty? empty (head) \n");
	printf("Result -> %d \n\n",empty(head));
	free(head);
}
