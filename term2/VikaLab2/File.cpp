/************************************************************************
*file: File.cpp
*purpose: implementation of File interface
*author: Victoria Buts
*written: 30/04/2014
*last modified: 01/05/2014
*************************************************************************/

#include "File.h"
#include <iomanip>
#include <iostream>
#include <regex>
#include <vector>

#pragma warning (disable : 4996)

File::File(const File &copy) : keywords_nmb(copy.keywords_nmb),size(copy.size) {
	name = keywords = NULL;
	if ( copy.name ) 
		this->name = strcpy(new char[strlen(copy.name) + 1 ],copy.name);
	if ( copy.keywords ) 
		this->keywords = strcpy(new char[strlen(copy.keywords) + 1],copy.keywords);
}

File::File(const char* filename,int size,const char* keywords)  {
	if (filename == NULL) throw invalid_argument("NULL was provided into constructor as formal filename.");
	if ( keywords == NULL ) throw invalid_argument("NULL was provided into constructor as formal keywords.");
	name = new char[strlen(filename) +1];
	strcpy(name,filename);
	this->size = size;
	this->SetKeywords(keywords);
}
	

void File::SetDetails(const char *filename, int size) {
	if ( filename == NULL ) throw invalid_argument("NULL was provided into SetDetails as formal filename.");
	if ( size < 0 ) throw invalid_argument("Negative size was provided into SetDetails.");
	name = new char[strlen(filename) +1];
	strcpy(name,filename);
	this->size = size;
}

void File::SetKeywords(const char* keywords) {
	if ( keywords == NULL ) throw invalid_argument("NULL was provided into SetKeywords as formal keywords");
	this->keywords = new char[strlen(keywords) +1];
	strcpy(this->keywords,keywords);
	keywords_nmb = 0;
	
	smatch keyword_match;
	string added_keywords(keywords);
	while ( regex_search(added_keywords,keyword_match,regex("[^;]+"))) {
		keywords_nmb++;
		added_keywords = keyword_match.suffix().str();
	}
}

void File::Print() const {
	cout << setw(15) << "name : " << ((name)?(name):("")) << endl;
	cout << setw(15) << "size : " << size << endl;
	cout << setw(15) << "keywords : " << ((keywords)?(keywords):("")) << endl;
	cout << setw(15) << "keywords_nmb : " << keywords_nmb << endl;
}

File & File::operator=(const File &asg) {

	if ( &asg != this ) {
		this->keywords_nmb = asg.keywords_nmb;
		this->size = asg.size;
		delete[] name;
		delete[] keywords;
		name = keywords = NULL;
		if ( asg.name ) 
			this->name = strcpy(new char[strlen(asg.name) + 1 ],asg.name);
		if ( asg.keywords ) 
			this->keywords = strcpy(new char[strlen(asg.keywords) + 1],asg.keywords);
	}

	return *this;
}

void File::AddKeyword(const char *newKeyword)  {
	if ( newKeyword == NULL ) throw invalid_argument("NULL was provided into AddKeyword as formal newKeyword.");
	if ( strcmp(newKeyword,"") == 0 ) throw invalid_argument("Keyword length should be higher than 0.");
	
	string newKeywordsSet("");
	if ( keywords ) {
		newKeywordsSet.append(keywords).append(";");
		delete[] keywords;
	}
	newKeywordsSet.append(newKeyword);
	keywords = strcpy(new char[newKeywordsSet.length() + 1],newKeywordsSet.c_str());
	keywords_nmb++;
}
	
void File::DelKeyword(const char* deletedKeyword) {
	if ( deletedKeyword == NULL ) throw invalid_argument("NULL was provided into DelKeyword as formal deletedKeyword.");
	if ( keywords != NULL ) {
		string newKeywordsSet(keywords);
		size_t whereKeywordStarted = newKeywordsSet.find(deletedKeyword);
		while ( whereKeywordStarted != string::npos ) {
			newKeywordsSet.erase(whereKeywordStarted,strlen(deletedKeyword) +1);
			keywords_nmb--;
			whereKeywordStarted = newKeywordsSet.find(deletedKeyword);
		}
		keywords = strcpy(new char[newKeywordsSet.length() + 1],newKeywordsSet.c_str());
	}
}

void File::deleteKeywordGreaterThan(int len) {
	if ( len <= 0 ) {
		delete[] keywords;
		return;
	}
	smatch keyword_match;
	vector <string> all_old_keywords;
	string old_keywords(keywords);

	while ( regex_search(old_keywords,keyword_match,regex("[^;]+"))) {
		all_old_keywords.push_back(keyword_match.str());
		old_keywords = keyword_match.suffix().str();
	}
	for (auto keyword : all_old_keywords) {
		if ( keyword.length() > len) 
			DelKeyword(keyword.c_str());
	}
}


bool File::operator<(const File &compared) const {
	return this->size < compared.size ;
}

#pragma warning (default : 4996)
