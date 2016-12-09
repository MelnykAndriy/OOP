
#include "DoublyLinkedList.h"
#include <stdio.h>

int main ()
{
	DoublyLinkedList D_list_test;
	ListNode kukio("Kukio");
	ListNode kukoban("Kukoban");
	ListNode sasha("Sasha");
	ListNode igor("Magdya");
	ListNode andr("Andriy");

	D_list_test.print();
	D_list_test.push_front(kukio);
	D_list_test.print();
	printf("Size = %d \n",D_list_test.size());
	D_list_test.push_back(kukoban);
	D_list_test.print();
	printf("Size = %d \n",D_list_test.size());
	D_list_test.push_back(sasha);
	D_list_test.print();
	printf("Size = %d \n",D_list_test.size());
	D_list_test.push_front(igor);
	D_list_test.insert_ord(andr);
	D_list_test.print();
	D_list_test.push_front(andr);
	D_list_test.push_back(igor);
	D_list_test.print();
	D_list_test.insert_after("Andriy",andr);
	D_list_test.print();
	D_list_test.pop_front();
	D_list_test.pop_back();
	D_list_test.print();
	printf("Size = %d \n",D_list_test.size());
	printf("test empty %d \n\n",D_list_test.empty());

	printf("After sorting \n");
	D_list_test.sort();
	D_list_test.print();

	printf("Backward \n");
	D_list_test.print_bkw();

	printf("Test erase \n");
	D_list_test.erase("Andriy");
	D_list_test.print();

	DoublyLinkedList merge_test;
	ListNode merge1("merge1");
	ListNode merge2("merge2");

	merge_test.push_front(merge1);
	merge_test.push_front(merge2);
	merge_test.push_front(merge2);
	merge_test.push_front(igor);

	printf("Test merge \n");
	printf("Insert list is \n");
	merge_test.print();
	printf("After using merge \n");
	D_list_test.merge(merge_test);
	D_list_test.print();

	printf("After using unique \n");
	D_list_test.unique();
	D_list_test.print();
/// ********************************
	DoublyLinkedList assign_test;
	ListNode assign1("assign1");
	ListNode assign2("assign2");
	ListNode assign3("assign3");
	ListNode assign4("assign4");

	assign_test.push_back(assign1);
	assign_test.push_back(assign2);
	assign_test.push_back(assign3);
	assign_test.push_back(assign4);

	printf("Test assign \n");
	printf("Insert list is (from 1 to 2) \n");
	assign_test.print();
	printf("After using assign \n\n");
	D_list_test.assign(assign_test,1,2);
	printf("assign_test is \n");
	assign_test.print();
	printf("D_list_test is \n");
	D_list_test.print();

/// ********************************
	DoublyLinkedList splice_test;
	ListNode splice1("splice1");
	ListNode splice2("splice2");
	ListNode splice3("splice3");
	ListNode splice4("splice4");

	splice_test.push_back(splice1);
	splice_test.push_back(splice2);
	splice_test.push_back(splice3);
	splice_test.push_back(splice4);

	printf("Test splice \n");
	printf("Insert list is (from 2 to 3) \n");
	splice_test.print();
	printf("After using splice\n\n");
	D_list_test.splice(D_list_test.size()/2,splice_test,2,3);
	D_list_test.print();

	printf("After using clear\n\n");
	D_list_test.clear();
	D_list_test.print();
	printf("Size = %d \n",D_list_test.size());
	printf("test empty %d \n\n",D_list_test.empty());
	return 0;
}
