

#include "Stringlist.h"
#include <iostream>

using namespace std;

#define FORWARD_PRINT(LST) 	for(StringList::POSITION  pos = LST->GetHeadPosition() ; pos != NULL ; pos = LST->GetNext() )	\
							LST->PrintNode( pos );

#define REVERS_PRINT(LST)  for(StringList::POSITION  pos = LST->GetTailPosition() ; pos != NULL ; pos = LST->GetPrev() )	\
							LST->PrintNode( pos );

int main() {
	StringList *testLst = new StringList();

	testLst->AddHead("s1");
	testLst->AddHead("s2");
	testLst->AddHead("s3");
	testLst->AddTail("s4");
	testLst->AddTail("s4");
	testLst->AddTail("s1");

	cout << "next iteration" << endl;
	FORWARD_PRINT(testLst);

	cout << "\nprev iteration\n";
	REVERS_PRINT(testLst);

	cout << "\nafter testLst.Unique()\n";
	testLst->Unique();
	FORWARD_PRINT(testLst);

	cout << "\nafter remove\n";
	testLst->RemoveHead();
	testLst->RemoveTail();
	FORWARD_PRINT(testLst);

	StringList appendLst;
	appendLst.AddTail("s1");
	appendLst.AddTail("s2");
	appendLst.AddTail("s3");
	appendLst.AddTail("s4");

	cout << "\nappendLst : \n";
	FORWARD_PRINT((&appendLst));

	cout << "\nafter AppendExclusively\n";
	testLst->AppendExclusively(&appendLst);
	FORWARD_PRINT(testLst);
	
	StringList spliceLst;
	spliceLst.AddTail("splice1");
	spliceLst.AddTail("splice2");
	spliceLst.AddTail("splice3");
	spliceLst.AddTail("splice4");
	
	cout << "\nafter Splice\n";
	testLst->Splice(testLst->Find("s3"),&spliceLst,spliceLst.Find("splice2"),spliceLst.Find("splice3"));
	FORWARD_PRINT(testLst);

	cout << "Life is good!" << endl;

	delete testLst;
	return 0;
}
