/************************************************************************
*file: File.h
*purpose: File class declaration
*author: Victoria Buts
*written: 30/04/2014
*last modified: 01/05/2014
*************************************************************************/

#pragma once

#include <vector>

using namespace std;

class File {
public:

		//default constructor
	File() {
		name = keywords = NULL;
		size = keywords_nmb = 0;
	}

	File(const char* filename,int size,const char* keywords) ;
	
	//copy constructor
	File(const File &);

	//destructor
	~File() { 
		delete[] name;
		delete[] keywords;
	}

	void SetDetails(const char *, int);
	void SetKeywords(const char*);
	void AddKeyword(const char *);
	void DelKeyword(const char* ); 

	//overloaded assignment
	File & operator=(const File &);
	
	bool operator<(const File &)const;
	
	int GetSize()const{ 
		return size;
	}

	int getKeywordsNumb() const {
		return keywords_nmb;
	}

	void deleteKeywordGreaterThan(int len);

	void SetSize( int newSize ) {
		if ( newSize < 0 ) throw invalid_argument("Negative size was provided into SetSize.");
		this->size = newSize;
	}

	void Print()const;

private:
	char* name;//file name
	int size;//file length
	char* keywords;//set of keywords
	int keywords_nmb;//keywords number
};
