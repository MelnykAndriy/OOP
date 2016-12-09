/************************************************************************
*file: TreeNode.h
*purpose: StringList interface implementation
*author: Genadiy Turchaninov
*written: 01/05/2014
*last modified: 01/05/2014
*************************************************************************/

#include "StringList.h" 

#pragma warning (disable : 4996)
#pragma warning (disable : 4018)

const int StringList::npos = -1;

#define LstCpy if (lst == NULL )	\
					return;	\
				size++;\
				StringList* tmp = new StringList(*lst); \
				if (head == NULL) { \
					head = tmp -> head; \
					return;		}

StringList::StringList(const StringList& sl){
	head = tail = NULL;	
	ListNode * iter = sl.head;
	while (iter != NULL){
		AddTail(iter->str);
		iter = iter->next;
	}
	pos = head;
}

void StringList::AddHead(const char * str) {
	if (str == NULL) {
		return;
	}
	size++;
	if (head == NULL) {
		head = new ListNode;
		head -> str = new char[strlen(str)+1];
		strcpy(head -> str, str);		
		tail = head;
		return;
	}
	
	ListNode* tmp;
	tmp = new ListNode;
	tmp -> str = new char[strlen(str)+1];
	strcpy(tmp -> str,str);
	tmp -> next = head;
	head -> prev = tmp;
	head = tmp;
	
}

void StringList::AddHead(const StringList * lst) {
	LstCpy;

	tmp->tail->next = head;
	head->prev = tmp->tail;
	head = tmp->head;
}

void StringList::AddTail(const char * str) {
	if (str == NULL) {
		return;
	}
	size++;
	if (tail == NULL) {
		tail = new ListNode;
		tail -> str = strcpy(new char[strlen(str)+1], str);		
		head = tail;
		return;
	}

	ListNode* tmp;

	tmp = new ListNode;
	tmp -> str = strcpy(new char[strlen(str)+1],str);
	tmp -> prev = tail;
	tail -> next = tmp;
	tail = tmp;
}

void StringList::AddTail(const StringList * lst){
	LstCpy;
	
	tail->next = tmp->head;
	tmp->head->prev = tail;
	tail = tmp->tail;
	tmp->head = NULL;
	delete tmp;
}

void StringList::RemoveHead() {
	REMOVE(head,next,prev);
}


void StringList::RemoveTail() {
	REMOVE(tail,prev,next);
}

void StringList::AppendExclusively(const StringList *sl){
	if ( sl == NULL ) return;
	ListNode* iter = sl->head;

	while ( iter ) {
		this->AddTailExclusively(iter->str);
		iter = iter->next;
	}
}

int StringList::getIndx(POSITION pos) const {
	int indx = 0;
	for ( ListNode* iter = head; iter ; indx++, iter = iter->next ) 
		if ( iter == pos ) {
			return indx;
		}
	return -1;
}


void StringList::Splice(POSITION where, StringList *sl, POSITION first, POSITION last) {
	if ( first == NULL || where == NULL || last == NULL || last == NULL )
		return;
	int whereIndex = getIndx(where);
	int firstIndex = sl->getIndx(first);
	int lastIndex = sl->getIndx(last);
	if ( whereIndex == -1 || firstIndex == -1 || lastIndex == -1 || firstIndex > lastIndex )
		return;

	for ( int i = lastIndex; i >= firstIndex; i--) {
		this->InsertAfter(sl->GetAt(i),whereIndex);
		sl->RemoveAt(i);
	}
	
}


void StringList::AddTailExclusively(const char *str) {
	if ( str == NULL ) return;
	ListNode* iter = head;
	
	while ( iter ) {
		if ( strcmp(str,iter->str) == 0) return;
		iter = iter->next;
	}
	this->AddTail(str);
}

void StringList::Unique() {
	ListNode* tmpHead = head;
	ListNode* iter = head; 
	head = tail = NULL;

	for (  ; iter ; iter = iter->next )
		this->AddTailExclusively(iter->str);
	
	pos = head;
	delete tmpHead;	
}

const char* StringList::GetAt( int indx ) const {
	if ( indx < 0 || indx > size - 1 )  throw logic_error("Index out of range");
	int curIndx = 0;
	
	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( curIndx++ == indx ) {
			return iter->str;
		}
	return NULL;
}

void StringList::RemoveAt( int indx ) {
	if ( indx < 0 || indx > size - 1 )  throw logic_error("Index out of range");
	if ( indx == 0 ) return this->RemoveHead();
	if ( indx == size - 1) return this->RemoveTail();

	int curIndx = 0;
	
	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( curIndx++ == indx ) {
			iter->prev->next = iter->next;
			iter->next->prev = iter->prev;
			iter->next = iter->prev = NULL;
			delete iter;
			return;
		}			
}

void StringList::SetAt(char* str ,int indx ) {
	if ( str == NULL ) return;
	if ( indx < 0 || indx > size - 1 )  throw logic_error("Index out of range");

	int curIndx = 0;
	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( curIndx++ == indx ) {
			delete iter->str;
			iter->str = (str)?(strcpy(new char[strlen(str) + 1],str)) : (NULL);
			return;
		}
}

void StringList::InsertAfter(const char *str,int indx) {
	if ( str == NULL ) return;
	if ( indx < 0 || indx > size - 1 )  throw logic_error("Index out of range");
	if ( indx == size -1 ) 
		return this->AddTail(str);
	
	int curIndx = 0;
	ListNode* addedNode = new ListNode(str);

	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( curIndx++ == indx ) {
			addedNode->prev = iter;
			addedNode->next = iter->next;
			iter->next = addedNode;
			addedNode->next->prev = addedNode;
			return;
		}
}


void StringList::InsertBefore(const char *str,int indx) {
	if ( str == NULL ) return;
	if ( indx < 0 || indx > size - 1 )  throw logic_error("Index out of range");
	if ( indx == size -1 ) 
		return this->AddHead(str);

	int curIndx = 0;
	ListNode* addedNode = new ListNode(str);

	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( curIndx++ == indx ) {
			addedNode->prev = iter->prev;
			addedNode->next = iter;
			iter->prev = addedNode;
			addedNode->prev->next = addedNode;
			return;
		}
}

const ListNode* StringList::Find(const char* str)  const {
	if ( str == NULL ) return NULL;
	for ( ListNode* iter = head; iter ; iter = iter->next ) 
		if ( strcmp(str,iter->str) == 0 )
			return iter;
	return NULL;
}

int  StringList::FindIndex(const char* str) const  {
	if ( str == NULL ) return NULL;
	int curIndex = 0;
	for ( ListNode* iter = head; iter ; curIndex++ , iter = iter->next ) 
		if ( strcmp(str,iter->str) == 0 )
			return curIndex;
	return npos;
}

#pragma warning (default : 4018)		
#pragma warning (default : 4996)
	