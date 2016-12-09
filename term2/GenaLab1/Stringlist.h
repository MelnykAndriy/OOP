/************************************************************************
*file: Stringlist.h
*purpose: StringList class declaration
*author: Genadiy Turchaninov
*written: 01/05/2014
*last modified: 01/05/2014
*************************************************************************/

#pragma once
#include <string.h>
#include <iostream>

using namespace std;

struct ListNode{
	ListNode() { 
		next = prev =  NULL;
		str = NULL;	
	}

	ListNode(const char* str) { 
		next = prev =  NULL;
#pragma warning (disable : 4996)
		this->str = (str)?(strcpy(new char[strlen(str) + 1],str)) : (NULL);
#pragma warning (default : 4996)
	}

	~ListNode(){
		delete str; 
		delete next;
	}

	friend ostream& operator<<(ostream& os,const ListNode& nd) {
		cout << nd.str;
		return os;
	}

	char *str;
	ListNode* next;
	ListNode* prev;
};

class StringList{
#define REMOVE(from,moveTo,reverse)	if (head == tail) { \
										size = 0; \
										delete head; \
										head = tail = NULL; \
										return; } \
									from = from->moveTo; \
									from->reverse->moveTo = NULL; \
									delete from->reverse; \
									from->reverse = NULL; \
									size--;

	public:	
		typedef const ListNode* POSITION;
		static const int npos;

		//Constructs an empty list for ListNode objects.
		StringList() : pos(NULL),tail(NULL),head(NULL),size(0) { }

		StringList(const StringList&);

		~StringList(void){
			delete head;
		}

		//Head/Tail Access
		const ListNode* GetHead() {
			return head;
		}

		const ListNode* GetTail() {
			return tail;
		}
		//Operations 
		//Adds an element to the head of the list (makes a new head).
		void AddHead(const char *);
		//Adds all the elements in another list to the head of the list (makes a new head).
		void AddHead(const StringList *);
		//Adds an element to the tail of the list (makes a new tail).
		void AddTail(const char *);
		//Adds all the elements in another list to the tail of the list (makes a new tail).
		void AddTail(const StringList *);
		//Removes all the elements from this list. 
		void RemoveAll() {
			delete head;
			tail = head = NULL;
			size = 0;
		}

		//Removes the element from the head of the list.
		void RemoveHead();
		//Removes the element from the tail of the list.
		void RemoveTail();

		void AppendExclusively(const StringList *);

		void AddTailExclusively(const char *);

		void Splice(POSITION where, StringList *sl, POSITION first, POSITION last);

		//removes all duplicate elements
		void Unique();

	//Iteration 
		//Gets the next element for iterating.
		POSITION GetNext() {
			if ( pos ) return pos = pos->next;
			return pos;
		}

		//Gets the previous element for iterating.
		POSITION GetPrev() {
			if ( pos ) pos = pos->prev;
			return pos;
		}

	//Retrieval/Modification
		POSITION GetHeadPosition() {
			return pos = head;
		}

		POSITION GetTailPosition() {
			return pos = tail;
		}


		//Gets the element at a given position.
		const char* GetAt(int )const;

		//Removes an element from this list as specified by position.
		void RemoveAt(int );

		//Sets the element at a given position.
		void SetAt(char *, int );

	//Insertion 
		//Inserts a new element after a given position.
		void InsertAfter(const char *, int);

		//Inserts a new element before a given position.
		void InsertBefore(const char *, int);

	//Searching 
		//Gets the position of an element specified by string value.
		const ListNode* Find(const char *) const ; 

		//Gets the position of an element specified by a zero-based index.
		int FindIndex(const char *) const;	// return npos if element not found
		
	//Status 
		//Returns the number of elements in this list.
		int GetSize() const {
			return size;
		}
		
		//Tests for the empty list condition (no elements).
		bool IsEmpty() const {
			return head == NULL;
		}

		void PrintNode( const ListNode *p) {
			if ( p == NULL ) return;
			cout << *p << endl;
		}

	private:
		int getIndx(POSITION pos) const ;

		ListNode* head;
		ListNode* tail;
		ListNode* pos;
		size_t size;

};