/************************************************************************
 *file: list.h
 *synopsis: prototypes of functions
 *author: Melnyk Andriy
 *written: 23/10/2013
 *last modified: 24/10/2013
 ************************************************************************/

#pragma once

#include <stdio.h>
#include <malloc.h>


typedef struct  tag_CNode 
{
	int id;

	tag_CNode *prev;
	tag_CNode *next;
} CNode;

int empty(const CNode *head);
// return value 1 -> if list empty 
//              0 -> if list not empty

CNode *get_node (const CNode *head, int id );

void append2list (CNode *head, const CNode *pn);

void del_node (CNode *head, int id);

void clear(CNode *head);

void ins_node (CNode *head, const CNode *pn, int id);

void reverse(CNode *head);

void print_list(const CNode *head );

CNode* merge_unique(const CNode *head1, const CNode *head2);

void unique(CNode *head);
