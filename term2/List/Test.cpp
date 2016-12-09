/************************************************************************
*file: Test.cpp
*purpose: testing intarface of classes Bus,Iterator,List
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 09/03/2014
*************************************************************************/

#include "List.h"
#include "Depo.h"
#include <new>
#include <ctime>
#define STANDART_TYPE_TEST

#define TEST_CHANGE(what)	cout << #what <<endl; \
							what;

#define TEST_RESULT(what)	cout << #what " -> " << what << endl;

void NewHandler() {
	cerr << "Heap exhausted. Game over!" << endl;
	exit(EXIT_FAILURE);
}


int main() {
	set_new_handler(&NewHandler);
#pragma warning (disable : 4244) 
	srand(time(NULL));
#pragma warning (default : 4244)

#ifdef STANDART_TYPE_TEST

	List<int> testLst1;
	List<double> testLst2(5,1.01521);
	
	TEST_RESULT(testLst1.size());
	TEST_RESULT(testLst2.size());

	TEST_RESULT(testLst1.empty());
	TEST_RESULT(testLst2.empty());

	TEST_CHANGE(testLst1.Print());
	TEST_CHANGE(testLst2.Print());

	TEST_CHANGE(testLst1.push_front(12));
	TEST_CHANGE(testLst1.push_front(-5));
	TEST_CHANGE(testLst1.push_front(777));
	TEST_CHANGE(testLst1.Print());

	TEST_CHANGE(testLst2.clear());
	TEST_RESULT(testLst2.size());
	TEST_RESULT(testLst2.empty());

	TEST_CHANGE(for (int i = 0 ; i < 7 ; i++) 
					testLst2.push_front(rand()/1000.0);)
	TEST_CHANGE(testLst2.Print());

	for (int i = 0; i  < 2 ; i++ ) 
		TEST_RESULT(testLst2.pop_front());
	TEST_CHANGE(testLst2.Print());

	TEST_CHANGE(List<int>::iterator iter = testLst1.find(-5));
	TEST_RESULT(*iter);
	TEST_CHANGE(iter = testLst1.find(777));
	TEST_RESULT(*iter);
	TEST_CHANGE(*iter = 99);
	TEST_CHANGE(testLst1.Print());

	TEST_CHANGE(List<double> doubLst;
				for (int j = 0; j<5 ; j++)
					doubLst.push_front(rand()/1000.0););

	TEST_CHANGE(doubLst.Print());

	int j = 0;
	for (List<double>::iterator it = doubLst.begin() ; it != doubLst.end() ; j++ ) {
		if ( j % 2 == 0) {
			List<double>::iterator delIt = it;
			it++;
			doubLst.splice(delIt,testLst2);
			continue;
		}
		it++;
	}
	TEST_CHANGE(testLst2.Print());
	TEST_CHANGE(doubLst.Print());

	TEST_CHANGE(testLst1.remove(12));
	TEST_CHANGE(testLst1.remove(777));
	TEST_CHANGE(testLst1.Print());
	TEST_RESULT(testLst1.size());
	
	int n = 90;
	TEST_CHANGE(testLst1 += n);
	TEST_CHANGE(testLst1.Print());
	TEST_CHANGE(doubLst.Print());
	TEST_CHANGE(testLst2 += doubLst);
	TEST_CHANGE(doubLst.Print());

	List<int> testLst3;
	TEST_CHANGE(testLst3.LoadFromCsv("integers.csv"));
	TEST_CHANGE(testLst3.Print());

#else
	TEST_CHANGE(Depo firstDepo("buses.csv"));
	TEST_CHANGE(firstDepo.PrintInDepo());

	TEST_CHANGE(firstDepo.ChangeDriver(string("Petro"),string("Semen")));
	TEST_CHANGE(firstDepo.ChangeDriver(string("Yuri"),string("Vova")));
	TEST_CHANGE(firstDepo.PrintInDepo());


	TEST_CHANGE(firstDepo.AddBusToDepo(Bus("Nigel","DANCER","777")));
	TEST_CHANGE(firstDepo.AddBusToDepo(Bus("Dirol","MINT_ROGUE","1")));
	TEST_CHANGE(firstDepo.PrintInDepo());

	TEST_RESULT(firstDepo.GoOnRoute(string("777")));
	TEST_RESULT(firstDepo.GoOnRoute(string("56")));
	TEST_RESULT(firstDepo.GoOnRoute(string("78")));
	TEST_RESULT(firstDepo.GoOnRoute(string("1")));
	TEST_CHANGE(firstDepo.PrintInDepo());
	TEST_CHANGE(firstDepo.PrintOnRoute());

	TEST_RESULT(firstDepo.BackToDepo(string("1")));
	TEST_RESULT(firstDepo.BackToDepo(string("777")));
	TEST_CHANGE(firstDepo.PrintInDepo());
	TEST_CHANGE(firstDepo.PrintOnRoute());

#endif

	cout << "Life is good!!!" << endl;
	return 0;
}

	