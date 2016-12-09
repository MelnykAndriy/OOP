/************************************************************************
 *file: cArray.cpp
 *purpose: implements methods of class cArray
 *author: Melnyk Andriy
 *written: 21/01/2014
 *last modified: 17/02/2014
 *************************************************************************/

#include "cArray.h"

cArray::cArray(void) {
	arr = (int*) calloc(GROWBY,sizeof(int));
	HEAP_OVERFLOW(arr);
	arrSize = GROWBY;
	arrCount = 0;
}

cArray::cArray(int size) {
	INNCORECT_SIZE(size)
	arr = (int*) calloc(size,sizeof(int));
	HEAP_OVERFLOW(arr);
	arrSize = size;
	arrCount = 0;
}

cArray::cArray(int size,int initVal) {
	INNCORECT_SIZE(size);
	arr = (int *) calloc(size,sizeof(int));
	HEAP_OVERFLOW(arr);
	arrSize = size;
	arrCount = size;
	for(int i = 0; i < size; i++) 
		arr[i] = initVal;
}

cArray::cArray(int firstElem, ...) {
	int arg, size = GROWBY, i = 1;
	arr = (int *) malloc(sizeof(int)*size);
	HEAP_OVERFLOW(arr);
	arr[0] = firstElem;
	va_list restElems;
	va_start(restElems,firstElem);
	while ((arg = va_arg(restElems,int)) != 0) {
		if (size == i + 1) {
			arr = (int *) realloc(arr,(size+=GROWBY)*sizeof(int));
			HEAP_OVERFLOW(arr);
		}
		arr[i++] = arg;		
	}
	arrSize = arrCount = i;
	va_end(restElems);
	FreeExtra();
}

cArray::~cArray(void)
{
	free(arr);
}

void cArray::RemoveAll() {
	arr = (int *) realloc(arr,sizeof(int));
	arrSize = arrCount = 0;
}

void cArray::Add(int elm) {
	if (arrCount != arrSize) {
		arr[arrCount++] = elm;
		return;
	}
	int* tmp = (int *) realloc(arr,sizeof(int)*(arrSize + GROWBY));
	HEAP_OVERFLOW(tmp);
	arrSize += GROWBY;
	arr = tmp;
	arr[arrCount++] = elm;
	return;
}

void cArray::Append(cArray *apArr) {
	int newCount = apArr->GetCount() + arrCount;
	{
		int test1 = (newCount%GROWBY)?(GROWBY):(0);
		int test2 = (newCount/GROWBY)*GROWBY;
		int newSize = (newCount%GROWBY)?(GROWBY):(0) + (newCount/GROWBY)*GROWBY; 
		printf("");
	}
	CP_AP(arrCount,apArr);
}

void cArray::Copy(cArray *cpArr) {
	int newCount = cpArr->GetCount();
	CP_AP(0,cpArr);
}

void cArray::SetSize(int nNewSize) {
	INNCORECT_SIZE(nNewSize);
	int * tmp = (int *) realloc(arr,sizeof(int)*nNewSize);
	HEAP_OVERFLOW(tmp);
	arrSize = (arrCount > nNewSize)?(arrCount = nNewSize):(nNewSize);
	arr = tmp;
}

void cArray::InsertAt(int n, int indx) {
	OUT_OF_RANGE(indx);
	if (arrCount == arrSize) {
		int* tmp = (int *) realloc(arr,sizeof(int)*(arrSize + GROWBY));   
		HEAP_OVERFLOW(tmp);
		arrSize += GROWBY;
		arr = tmp;
	}

	for (int i = arrCount; i > indx   ; i--)
		arr[i] = arr[i-1];
	arr[indx] = n; 
	arrCount++;
	return;
}

void cArray::RemoveAt(int indx) {
	OUT_OF_RANGE(indx);
	for (int i = indx; i != arrCount - 1; i++) 
		arr[i] = arr[i+1];
	arrCount--;
	return;
}

int& cArray::operator[] (int i) {
	OUT_OF_RANGE(i);
	return arr[i];
}