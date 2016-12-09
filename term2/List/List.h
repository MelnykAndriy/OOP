/************************************************************************
*file: List.h
*purpose: definition of template class List
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 09/03/2014
*************************************************************************/

#pragma once
#include "Iterator.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

template <class T> class List {

#define LIST_COPY(from)	if (from.head->next) { \
							head = new ListNode(*from.head); \
							ListNode* prev = head;	\
							ListNode* iter = from.head->next;	\
							while (iter) {  \
								prev->next = new ListNode(iter->data);	\
								prev = prev->next;	\
								iter = iter->next;	}	\
							last->ptr = prev;	\
						} else last->ptr = head = new ListNode(); \
						first->ptr = head; \

#define PUSH2LST(what) 	ListNode* addNode = new ListNode(what); \
						addNode->next = head;	\
						head = first->ptr = addNode;	\
						__size++;

#define INIT_CONSTRUCTOR(ref)	List(const int& sz,T ref init = T())	\
										: __size(0),first(new iterator),last(new iterator) {	\
									head = new ListNode();		\
									first->ptr = last->ptr = head;	\
									for (int i = 0; i < sz ; i++) {		\
										PUSH2LST(init)	}}

	struct ListNode {
		T data;
		ListNode* next;
		ListNode(){
			next = NULL;
		}

		friend ostream& operator<<(ostream& stream,ListNode& nd) {
			cout << nd.data;
			return stream;
		}

		ListNode& operator=(const T& data) {
			this->data = data;
			return *this;
		}

		inline operator T() const {
			return this->data;
		}

		ListNode(T dat) {
			data = dat;
			next = NULL;
		}

		~ListNode() {
			delete next;
		}
	public:

		void Print(){
			cout << data;
		}
	};

public:
	class EmptyLst : public exception {
			string msg;
		public:
			virtual const char* what () const throw() {
				return (msg.length())?(msg.c_str()):("List is empty!");
			}
			EmptyLst(string msg = string("")) : msg(msg) {}
	};

	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	
//constructors / destructors
	List()  : __size(0),first(new iterator),last(new iterator) {
		head = new ListNode();
		first->ptr = last->ptr = head;
	}

	INIT_CONSTRUCTOR(&&);
	INIT_CONSTRUCTOR(&);

	List(const List&);
	~List();

//methods
	List& operator=(const List&);
	List& operator+=(const List&);
	List& operator+=( const T&);

	inline iterator begin() const {	//Returns an iterator addressing the first element
		return  *first ;
	}

	inline iterator end() const {		//Returns an iterator that addresses the location
		return iterator(last->ptr);		//succeeding the last element
	}

	void LoadFromCsv(const char *csv); // initializes list from csv-file
									
	void clear();					//Erases all the elements of a list.

	inline bool empty() {				//Tests if a list is empty.
		return head->next == NULL;
	}

	iterator find(const T & val);	//Returns an iterator to the
									// first element in a list that
									//match a specified value.

	T pop_front();	//Deletes the element at the beginning of a list.
	void push_front( const T& val);	//Adds an element to the beginning
											//of a list.

	void push_front(T&& val);

	void remove(const T& val);			//Erases first element in a list that
										//match a specified value.

	inline int size() const {						//Returns the number of elements in a list.
		return __size;
	}

	void splice(iterator _Where, List<T> &_Right);	//Removes element from the
													//target list and inserts it in first
													// position of the argument list.
	void Print() const;		//Dumps list into the screen
private:
	bool isMy(iterator iter);
	node_type *head;
	iterator *first, *last;
	int __size;
};

template <typename T> List<T>::~List() {
	delete head;
	delete first;
	delete last;
}

template <typename T> List<T>::List(const List<T> &copy) : __size(copy.size()),first(new iterator),last(new iterator) {
	LIST_COPY(copy);
}

template <typename T> List<T>& List<T>::operator=(const List<T> &copy) {
	delete head;
	LIST_COPY(copy);
	__size = copy.size();
	return *this;
}

template <typename T> List<T>& List<T>::operator+=(const List<T> &appLst) {
	iterator iter = begin();

	if ( iter == end() ) {
		delete head;
		LIST_COPY(appLst);
		__size = appLst.size();
		return *this;
	}
	for (	;	;iter++) {
		if ( iter + 1 == end() ) {
			List<T>* appListCopy = new List<T>(appLst);
			delete iter.ptr->next;
			iter.ptr->next = appListCopy->head;
			last = appListCopy->last;
			appListCopy->head = NULL;
			appListCopy->last = appListCopy->first = NULL;
			__size += appListCopy->__size;
			delete appListCopy;
			return *this;
		}	
	}
}

template <typename T> List<T>& List<T>::operator+=(const T& appVal) {
	iterator iter = begin();

	if (iter == end() ) {
		push_front(appVal);
		return *this;
	}
	for (	;	;iter++) {
		if ( iter + 1 == end() ) {
			ListNode* appValNode = new ListNode(appVal);
			appValNode->next = iter.ptr->next;
			iter.ptr->next = appValNode;
			break;
		}	
	}
	__size++;
	return *this;
}

template <typename T>  void List<T>::clear() {	
		delete head;
		__size = 0;
		last->ptr = first->ptr = head = new ListNode();
}

template <typename T> T List<T>::pop_front() {
	ListNode* del = head;
	if (del->next != NULL ) {
		T retData = del->data;
		first->ptr = head = head->next;
		del->next = NULL;
		delete del;
		__size--;
		return retData;
	}
	throw EmptyLst("There is nothing to pop.");
}

template <typename T> void List<T>::push_front(const T& val) {
	PUSH2LST(val);
}

template <typename T> void List<T>::push_front(T&& val) {
	PUSH2LST(move(val));
}

template <typename T> void List<T>::remove(const T& val) {
	iterator iter = begin();
	if (*iter == val) {
		pop_front();
		return;
	}

	while (iter + 1 != end() && *(iter + 1) != val)
		iter++;
	
	if ( iter + 1 != end() )  {
		if (*last == iter + 1) *last = iter;
		ListNode* del;
		del = (*iter).next;
		(*iter).next = (*iter).next->next;
		del->next = NULL;
		__size--;
		delete del;
	}
}

template <typename T> void List<T>::splice(iterator _Where, List<T> &_Right) { 
	if (isMy(_Where)) {
		iterator it = begin();
		if (it == _Where) return _Right.push_front(pop_front());
		while ( it + 1 != _Where) it++;  
		_Right.push_front(*_Where);
		(*it).next = (*_Where).next;
		(*_Where).next = NULL;
		delete _Where.ptr;
		_Where.ptr = NULL;
	} 
}

template <typename T> typename List<T>::iterator List<T>::find(const T & val) {
	List<T>::iterator iter;						
	for ( iter = this->begin() ; iter != this->end() ; iter++) {
		if (*iter == val) break;				
	}
	return iter;	
}

template <typename T> void List<T>::Print() const {
	cout << "List :" << endl;
	for (iterator iter = begin(); iter != end(); iter++) {
		cout << *iter << "  ";
	} 
	cout << endl;
}

template <typename T> void List<T>::LoadFromCsv(const char* csv) {
	if (csv == NULL) return;

	T buf;
	ifstream f;
	f.open(csv);
	while ( f.good() ) {
		f >> buf;
		this->push_front(buf);
	}
	f.close();
}

template <typename T> bool List<T>::isMy(iterator _where) {
	iterator iter = begin();
	while (iter.ptr) {
		if (iter.ptr == _where.ptr) return true;
		iter.ptr = iter.ptr->next;
	}
	return false;
}