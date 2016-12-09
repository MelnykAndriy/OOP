/************************************************************************
*file: FileVectorIface.cpp
*purpose: implementation of additional File interface 
*author: Victoria Buts
*written: 30/04/2014
*last modified: 01/05/2014
*************************************************************************/

#include "FileVectorIface.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <regex>
#include <list>

using namespace std;

list<File>* loadFilesFromCsvToVecor(const string filename) {
	string line;
	ifstream filestream(filename);
	list<File>* retVector = new list<File>();
	
	while ( filestream.good() ) {
		getline(filestream,line,'\n');
		string addedFileName;
		string addedFileSize;
		string addedKeywords;

		smatch component;
		if ( regex_search(line,component,regex("[^;]+")) ) {
			addedFileName = component.str();
			line = component.suffix().str();
		}
		if ( regex_search(line,component,regex("[^;]+")) ) {
			addedFileSize = component.str();
			addedKeywords = component.suffix().str();
		}
		if ( addedKeywords.length() > 1) addedKeywords = addedKeywords.substr(1);
		retVector->push_back(File(addedFileName.c_str(),atoi(addedFileSize.c_str()),addedKeywords.c_str()));				
	}
	
	return retVector;
}

void ListAll( const std::list<File> &container) {
	cout << "All files in container" << endl;
	for (list<File>::const_iterator iter = container.begin() ; iter != container.end() ; iter++) {
		iter->Print();
	}
}

void AddKeyword(list <File> &container, char *keyword) {
	if ( keyword == NULL ) throw invalid_argument("NULL was provided into AddKeyword as formal keyword.");
	for (list<File>::iterator iter = container.begin() ; iter != container.end(); iter++)
		iter->AddKeyword(keyword);
}

void DelKeyword(list <File> &container, char *kwrd) {
	if ( kwrd == NULL ) throw invalid_argument("NULL was provided into DelKeyword as formal deletedKeyword.");
	for (list<File>::iterator iter = container.begin() ; iter != container.end(); iter++)
		iter->DelKeyword(kwrd);
}

void DelKeywordByLen(list <File> &container, int len) {
	for (list<File>::iterator iter = container.begin() ; iter != container.end(); iter++)
		iter->deleteKeywordGreaterThan(len);
}

void SortBySize(list <File> &container) {
	container.sort();
}

void SortByKeywordsNumber(list <File> &container) {
	container.sort([] (const File& f1,const File& f2)->bool { return f1.getKeywordsNumb() < f2.getKeywordsNumb(); });
	//sort( container.begin() , container.end() , 
	//	[] (const File& f1,const File& f2)->bool { return f1.getKeywordsNumb() < f2.getKeywordsNumb(); }); 
}