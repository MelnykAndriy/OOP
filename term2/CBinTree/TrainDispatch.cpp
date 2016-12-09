/************************************************************************
*file: testCTranslate.cpp
*purpose: tests intarface of class cTranslate
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 12/02/2014
*************************************************************************/

#include "BinTree.h"

#define TEST(what) cout << #what << endl; \
				   what;


void NewHandler() {
	cout << "Heap exhausted. Game over!"<< endl;
	exit(EXIT_FAILURE);
}

int main() {
	char * csvFile = "TrainsInfo.csv";
	set_new_handler(NewHandler);
	
	BinTree trains;
	try {
		trains.InitFromCsv(csvFile);
	} catch(exception& exc) {
		cerr << exc.what() << endl;
	}

	TEST(trains.PrintTree());

	TEST(trains.AddTrain(TreeNode(12,"Hmelnyk","23:44")));
	TEST(trains.AddTrain(TreeNode(12,"Hmelnyk","23:44")));
	TEST(trains.PrintTree());
	
	TEST(trains.PrintTrainInfo(148));
	TEST(trains.PrintTrainInfo(15));

	TEST(trains.PrintDestPaths("Moscow"));
	TEST(trains.PrintDestPaths("New York"));

	TEST(trains.DelByNumb(152));
	TEST(trains.PrintTree());
	TEST(trains.DelByNumb(12));
	TEST(trains.PrintTree());
	TEST(trains.DelByNumb(1024));
	TEST(trains.PrintTree());
	TEST(trains.DelByNumb(121));
	TEST(trains.PrintTree());
	TEST(trains.DelByNumb(148));
	TEST(trains.PrintTree());
	cout << "Size : " << trains.GetSize() << endl;

 	cout << "Life is good!!!\n";
	return 0;
}


