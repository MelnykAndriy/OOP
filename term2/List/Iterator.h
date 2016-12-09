/************************************************************************
*file: Iterator.h
*purpose: template class used to traverse through the List container
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 03/03/2014
*************************************************************************/

#pragma once
#include "List.h"
#include <stdlib.h>
#include <exception>
#include <string>

class IterAtEnd : public std::exception {
	std::string msg;
public:
	virtual const char* what() const throw() {
		return msg.c_str();
	}
	IterAtEnd(std::string&& m = std::string("Iterator has already reached the end.") ) : msg(m) { }
};

template <typename T> class _iterator {
	template <typename T2> friend class List;
private:
	T* ptr;
public:


	_iterator() { ptr = NULL; }
	_iterator(T* _ptr) { ptr = _ptr; }
	~_iterator() {}
	//typedef T value_type;
	typedef _iterator<T> it_type;
	T& operator *();
	void operator++();
	void operator--();
	int  operator-(const it_type &_iter) const;
	it_type operator+(int numb) const;

	it_type &operator=(const it_type &_iter) {
		this->ptr = _iter.ptr;
		return *this;
	}


	//dummy operator to keep compiler quiet
	void operator++(int);

	bool operator==(const it_type &_iter) const;
	bool operator!=(const it_type &_iter) const;
	bool empty() { return ptr == NULL;}
};

template <typename T> typename _iterator<T>::it_type _iterator<T>::operator+(int numb) const {
	int i = 0;
	_iterator<T>::it_type retIter = *this;
	while (retIter.ptr->next != NULL && i++ != numb)
		retIter++;
	return retIter;
}

template <typename T> T& _iterator<T>::operator *() {
	if (ptr && ptr->next) return *ptr;
	throw IterAtEnd("List iterator not dereferencable.");
}

template <typename T> void _iterator<T>::operator++() {
	(ptr)?(ptr = ptr->next):(throw IterAtEnd());
}

template <typename T> void _iterator<T>::operator++(int) {
	(ptr)?(ptr = ptr->next):(throw IterAtEnd());
}
template <typename T> bool _iterator<T>::operator ==(const it_type &_iter) const {
	return (ptr == _iter.ptr);
}

template <typename T> bool _iterator<T>::operator!=(const it_type &_iter) const {
	return !(*this == _iter);
}
