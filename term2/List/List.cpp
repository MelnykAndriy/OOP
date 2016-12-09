/************************************************************************
*file: List.cpp
*purpose: implements methods of class List
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 02/02/2014
*************************************************************************/

//#include "List.h"

//template <typename T> List<T>& List<T>::operator=(List<T> &copy) {
//	delete head;
//	LIST_COPY(copy);
//	__size = copy.size();
//	return *this;
//}
//
//template <typename T> List<T>& List<T>::operator+=(List<T> &appLst) {
//	List<T>* appListCopy = new List<T>(appLst);
//	ListNode* last = head;
//
//	if (last) {
//		if (last->next) 
//			while ((last = last->next)->next) ;
//		last->next = appListCopy->head;
//	} else {
//		head = appListCopy->head;
//		this->first = appList->first;
//	}
//	appListCopy->head = NULL;
//	this->last = appList->last;
//	__size += appLst.size();
//	delete appListCopy;
//	return *this;
//}
//
//template <typename T> List<T>& List<T>::operator+=(T& appVal) {
//	ListNode* appValNode = new ListNode(T);
//	ListNode* iter = head;
//
//	if (iter) {
//		if (iter->next)
//			while ((iter = iter->next)->next) ;
//		iter->next = appValNode;
//	} else 
//		head = appValNode;
//	last++;
//	__size++;
//	return *this;
//}
//
//template <typename T>  void List<T>::clear() {	
//		delete head;
//		__size = 0;
//		last->ptr = first->ptr = head = new ListNode();
//}
//
//template <typename T> T List<T>::pop_front() {
//	ListNode* del = head;
//	if (del) {
//		T retData = del->data;
//		head = head->next;
//		del->next = NULL;
//		delete del;
//		__size--;
//		return retData;
//	}
//	throw EmptyLst("There is nothing to pop.");
//}
//
//template <typename T> void List<T>::push_front(const T& val) {
//	PUSH2LST(val);
//}
//
//template <typename T> void List<T>::push_front(T&& val) {
//	PUSH2LST(move(val));
//}
//
//template <typename T> void List<T>::remove(const T& val) {
//	iterator iter = begin();
//	if (*iter == val) {
//		first->ptr = head = head->next;
//		(*iter)->next = NULL:
//		delete *iter;
//		return;
//	}
//
//	while (*(iter + 1) != val && iter + 1 != end() &&  )
//		iter++;
//	
//	if ( val == *(iter + 1) )  {
//		if (*last == iter + 1) *last = iter;
//		ListNode* del;
//		del = (*iter)->next;
//		(*iter)->next = (*iter)->next->next;
//		del->next = NULL;
//		delete del;
//	}
//}
//
//template <typename T> void List<T>::splice(iterator _Where, List<T> &_Right) { 
//	if ( find(*_Where) != end() ) {
//		_Right.push_front(*_Where);
//		remove(*_Where);
//	} 
//}
//
//template <typename T> typename List<T>::iterator List<T>::find(const T & val) {
//	List<T>::iterator iter;						
//	for ( iter = this->begin() ; iter != this->end() ; iter++) {
//		if (*iter == val) break;				
//	}
//	return iter;	
//}
//
//template <typename T> void List<T>::Print() {
//	cout << "List :" << endl;
//	for (iterator iter = begin(); iter != end(); iter++) {
//		cout << *iter;
//	}
//}
//
//template <typename T> void List<T>::LoadFromCsv(const char* csv) {
//	if (csv == NULL) return;
//
//	T buf;
//	ifstream f;
//	f.open(csv);
//	while ( f.good() ) {
//		f >> buf;
//		this->push_front(buf);
//	}
//	f.close();
//}
//
//template <typename T> bool List<T>::isMy(iterator _where) {
//	iterator iter = begin();
//	while (iter.ptr) {
//		iter.ptr = iter.ptr->next;
//		if (iter.ptr == _where.ptr) return true;
//	}
//	return false;
//}

