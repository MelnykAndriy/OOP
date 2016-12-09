/************************************************************************
*file: testCArray.cpp
*purpose: tests interface of class cArray
*author: Melnyk Andriy
*written: 21/01/2014
*last modified: 17/02/2014
*************************************************************************/

#include "cArray.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#define PRINT_CARRAY(arr)  \
	if (arr.GetCount()) {	\
		int _Count_ = (arr).GetCount();\
		printf("CArray : " #arr "\n"); \
		 for(int i = 0; i < _Count_; i++) \
			printf("%d  ",(arr)[i]); \
		 printf("\n");	\
	} else printf("CArray " #arr " is empty. \n");
        
#define BOOL_STR(b) (b)?("true"):("false")
using namespace std;

int main() {
#pragma warning (disable : 4244)
	srand(time(NULL));
#pragma warning (default : 4244)
	try {
		printf("8/10 : %d",8/10);
		cArray carr1 = cArray(7,5);
		cArray carr2 = cArray();
		printf("CArray test\n\n");

		PRINT_CARRAY(carr1);
		PRINT_CARRAY(carr2);

		//printf("\nTesting of IsEmpty\n");
		printf("carr1.IsEmpty() => %s\n",BOOL_STR(carr1.IsEmpty()));
		printf("carr2.IsEmpty() => %s\n",BOOL_STR(carr2.IsEmpty()));

		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr2.GetSize() => %d\n",carr2.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());
		printf("carr2.GetCount() => %d\n",carr2.GetCount());
		printf("carr1.GetUpperBound() => %d\n",carr1.GetUpperBound());
		printf("carr2.GetUpperBound() => %d\n",carr2.GetUpperBound());

		printf("carr1.SetSize(5)\n");
		carr1.SetSize(5);
		PRINT_CARRAY(carr1);
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());

		printf("carr1.RemoveAll()\n");
		carr1.RemoveAll();
		PRINT_CARRAY(carr1);
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());
		printf("carr1.IsEmpty() => %s\n",BOOL_STR(carr1.IsEmpty()));

		for (int i = 0; i < 9; i++) {
			carr1.Add(i);
		}
		printf("\n\nAfter filling carr1\n");
		PRINT_CARRAY(carr1);
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());

		for (int i = 0; i < 6 ; i++) {
			carr2.Add(rand()%50);
		}
		printf("\n\nAfter filling carr2\n");
		PRINT_CARRAY(carr2);
		printf("carr2.GetSize() => %d\n",carr2.GetSize());
		printf("carr2.GetCount() => %d\n",carr2.GetCount());

		printf("\ncarr1.FreeExtra()\n");
		carr1.FreeExtra();
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());
		
		printf("\ncarr2.FreeExtra()\n");
		carr2.FreeExtra();
		printf("carr2.GetSize() => %d\n",carr2.GetSize());
		printf("carr2.GetCount() => %d\n",carr2.GetCount());

		printf("\ncarr2.GetAt(3) => %d\n",carr2.GetAt(3));
		printf("carr1.SetAt(-3,3)\n");
		carr1.SetAt(-3,3);
		printf("carr1.SetAt(88,8)\n");
		carr1.SetAt(88,8);
		PRINT_CARRAY(carr1);

		printf("carr1[5] = carr2[5] = -1\n");
		carr1[5] = carr2[5] = -1;

		PRINT_CARRAY(carr1);
		PRINT_CARRAY(carr2);

		printf("\ncarr2.InsertAt(44,4)\n");
		carr2.InsertAt(44,4);
		printf("carr2.InsertAt(33,3)\n");
		carr2.InsertAt(33,3);
		PRINT_CARRAY(carr2);
		printf("carr2.GetSize() => %d\n",carr2.GetSize());
		printf("carr2.GetCount() => %d\n",carr2.GetCount());

		printf("\ncarr1.RemoveAt(0)\n");
		carr1.RemoveAt(0);
		printf("\ncarr1.RemoveAt(2)\n");
		carr1.RemoveAt(2);
		PRINT_CARRAY(carr1);
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());

		printf("\ncarr1.Append(&carr2)\n");
		carr1.Append(&carr2);
		PRINT_CARRAY(carr1);
		printf("carr1.GetSize() => %d\n",carr1.GetSize());
		printf("carr1.GetCount() => %d\n",carr1.GetCount());

		printf("\ncarr1.Copy(&carr2)\n");
		carr1.Copy(&carr2);
		PRINT_CARRAY(carr1);
		printf("carr2.GetSize() => %d\n",carr1.GetSize());
		printf("carr2.GetCount() => %d\n",carr1.GetCount());
		printf("Life is good! \n");

	} catch (cArray::ArrayOutOfRange exc) {
		printf("Array index out of range in function %s with index = %d \n",exc.getFunc(),exc.indx);
	} catch (cArray::HeapOverflow exc) {
		printf("Heap overflow in function %s \n",exc.getFunc());
	} catch (cArray::IncorrectSize exc) {
		printf("Incorrect array size (%d) in func %s \n",exc.size,exc.getFunc());
	}
			
	return 0;
}