/************************************************************************
*file: testCTranslate.cpp
*purpose: tests intarface of class cTranslate
*author: Melnyk Andriy
*written: 25/01/2014
*last modified: 25/01/2014
*************************************************************************/
#include "cTranslate.h"
#include <fstream>

#define TEST(what) cout << #what << endl; \
				   what;

bool cTranslate::handlerIsDef = false;
int main() {
	char* csv = "dictionary.csv";
	char* sml = "sml.csv";
	vector<cTranslate> dictionary;
	try {
		FillTransVector(dictionary,csv);
	} catch (exception* exc) {
		cerr << exc->what() << endl;
		delete exc;
	}

	ofstream f;
	f.open("testOutput.txt");
	cout.rdbuf(f.rdbuf());


	cout << "After filling " << endl;
	TEST(ListAll(dictionary))
	cout << endl;

	TEST(DelByIta(dictionary,"volpe"))
	TEST(DelByIta(dictionary,"pronto"))
	ListAll(dictionary);
	cout << endl;

	TEST(DelByEng(dictionary,"moon"))
	TEST(DelByEng(dictionary,"jump"))
	ListAll(dictionary);
	cout << endl;
	

	TEST(TranslateIta(dictionary,"pigro"))
	TEST(TranslateIta(dictionary,"indolente"))
	ListAll(dictionary);
	cout << endl;

	TEST(TranslateEng(dictionary,"dog"))
	TEST(TranslateEng(dictionary,"brown"))
	ListAll(dictionary);
	cout << endl;

	TEST(SortByEng(dictionary))
	ListAll(dictionary);
	cout << endl;
	TEST(SortByIta(dictionary))
	ListAll(dictionary);
	cout << endl;

	cout << "Life is Good!" << endl;
	return 1;
}
