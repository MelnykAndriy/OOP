/************************************************************************
*file: cArray.h
*purpose: define class cArray
*author: Melnyk Andriy
*written: 21/01/2014
*last modified: 21/01/2014
*************************************************************************/

#pragma once
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>

class cArray {
#define GROWBY 10
#define OUT_OF_RANGE(i) if (i < 0 || i > arrCount -1) throw ArrayOutOfRange(__FUNCTION__,i); 
#define INNCORECT_SIZE(size) if ( size < 0) throw IncorrectSize(__FUNCTION__,size);
#define HEAP_OVERFLOW(tmp) if (tmp == NULL) throw HeapOverflow(__FUNCTION__);
#define CP_AP(from,what) \
					int newSize = (newCount/GROWBY)*GROWBY;	\
					newSize += (newCount%GROWBY)?(GROWBY):(0); \
					if (arrSize < newCount) { \
							int * tmp = (int *) realloc(arr,sizeof(int)*newSize); \
							HEAP_OVERFLOW(tmp); \
							arrSize = newSize; \
							arr = tmp; } \
					for(int i = from ; i < newCount; i++) { \
						arr[i] = (*what)[i - from]; \
					} \
					arrCount = newCount;
public:
	class Exception {
		private:
			char* funcName;
		public:
			inline char* getFunc() const { return funcName; }
			Exception(char * funcName) : funcName(funcName){}
	};
	class ArrayOutOfRange : public Exception {
		public:	
			int indx;
			ArrayOutOfRange(char* str,int i) : Exception(str),indx(i) {};
	};
	class IncorrectSize : public Exception {
		public:
			int size;
			IncorrectSize(char * str,int sz) : Exception(str),size(sz) {} 
	};
	class HeapOverflow : public Exception {
		public:
			HeapOverflow(char * str) : Exception(str) {};
	};

	cArray(void);
	cArray(int size);
	cArray(int firstElem, ...);
	cArray(int size,int initVal);
	~cArray(void);

	//Gets the number of elements in this array.
	inline int GetSize() const {
		return arrSize;
	}

	//Gets the number of elements in this array.
	inline int GetCount() const {
		return arrCount;
	}

	//Returns the largest valid index.
	inline int GetUpperBound() const {
		return arrCount - 1;
	}

	//Determines whether the array is empty.
	inline bool IsEmpty() const {
		return arrCount == 0;
	}

	//Establishes the size of an empty or existing array; allocates memory if necessary.
	void SetSize(int nNewSize);

	//Frees all unused memory above the current upper bound.
	//This function has no effect on the upper bound of the array.
	inline void FreeExtra() {
		arrSize = arrCount;
		arr = (int *) realloc(arr,arrCount*sizeof(int));
	}

	//Removes all the elements from this array.
	void RemoveAll();

	//Element Access
	//Returns the value at a given index.
	inline int GetAt(int indx) const {
		OUT_OF_RANGE(indx);
		return arr[indx];
	}

	//Sets the value for a given index; array not allowed to grow.
	inline void SetAt(int n, int indx) {
		OUT_OF_RANGE(indx);
		arr[indx] = n;
	}

	//Growing the Array
	//Adds an element to the end of the array; grows the array if necessary.
	void Add(int);

	//Appends another array to the array; grows the array if necessary
	void Append(cArray *);

	//Copies another array to the array; grows the array if necessary.
	void Copy(cArray *);

//Insertion/Removal
	//Inserts an element at a specified index.
	void InsertAt(int n, int indx);

	//Removes an element at a specific index.
	void RemoveAt(int );

	//Operators
	//Sets or gets the element at the specified index.
	int& operator[] (int);

private:
	int arrSize;
	int arrCount;
	int *arr;
};