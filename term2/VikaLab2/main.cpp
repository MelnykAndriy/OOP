/************************************************************************
*file: main.cpp
*purpose: test cases
*author: Victoria Buts
*written: 30/04/2014
*last modified: 01/05/2014
*************************************************************************/

#include <iostream>
#include "File.h"
#include "FileVectorIface.h"
#include <string>

using namespace std;

int main () { 
	list<File>* fileContainer;
	
	fileContainer = loadFilesFromCsvToVecor("files.csv");
	ListAll(*fileContainer);
	
	AddKeyword(*fileContainer,"do");
	AddKeyword(*fileContainer,"return");
	cout << endl << endl << "after AddKeyword" << endl;
	ListAll(*fileContainer);

	SortBySize(*fileContainer);
	cout << endl << endl << "after SortBySize" << endl;
	ListAll(*fileContainer);
	
	DelKeyword(*fileContainer,"if");
	DelKeyword(*fileContainer,"for");
	DelKeyword(*fileContainer,"native");
	DelKeyword(*fileContainer,"static");
	DelKeyword(*fileContainer,"class");
	DelKeyword(*fileContainer,"funcall");
	cout << endl << endl << "after DelKeyword" << endl;
	ListAll(*fileContainer);

	SortByKeywordsNumber(*fileContainer);
	cout << endl << endl << "after SortByKeywordsNumber" << endl;
	ListAll(*fileContainer);

	DelKeywordByLen(*fileContainer,4);
	cout << endl << endl << "after DelKeywordByLen" << endl;
	ListAll(*fileContainer);

	delete fileContainer;
	return 0;
}