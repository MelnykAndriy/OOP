/************************************************************************
*file: cTranslate.h
*purpose: definition of class cTranslate
*author: Melnyk Andriy
*written: 25/01/2014
*last modified: 22/01/2014
*************************************************************************/

#pragma once

#include <string.h>
#include <new>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

#pragma warning (disable : 4996)

using namespace std;

int strcompare(const char* str1,const char* str2);

class cTranslate {
#define CP_PAIR(from)	eng = (from.eng)?(strcpy(new char[strlen(from.eng) + 1],from.eng)):(NULL); \
						ita = (from.ita)?(strcpy(new char[strlen(from.ita) + 1],from.ita)):(NULL);
public:
	cTranslate();

	cTranslate(char* _eng,char* _ita);

	cTranslate(const cTranslate &pair) {
		CP_PAIR(pair);
	}

	~cTranslate(void);

	//overloaded assignment
    cTranslate & operator=(const cTranslate &);

	inline bool operator<(const cTranslate &pair) {
		return strcompare(this->eng,pair.eng) < 0;
	}

	inline bool operator>(const cTranslate &pair) {
		return strcompare(this->eng,pair.eng) > 0;
	}

	void MakePair(char *eng, char *ita);

	inline void Print() const {
		cout << *this;
	}


	friend bool LesserIta(cTranslate x,cTranslate y);

	friend bool GreaterIta(cTranslate x,cTranslate y);

	friend ostream& operator<<(ostream& to,const cTranslate& obj);
	
	inline const char* GetEng() const{
		return eng;
	}

	inline const char * GetIta() const {
		return ita;
	}
private:
	char *eng;//English word
	char *ita;//Italian word
	static bool handlerIsDef;
};

class UnexpectedCharacter : public  exception {
private:
	string msg;
public:
	UnexpectedCharacter(short l,short p,const string f) 
	{
		char* buf = new char[33];
		msg = string("File : ").append(f).append("\nUnexpected character.\n").append("\t on line : ")
					    .append(_itoa(l,buf,10));
		msg.append(", position : ").append(_itoa(p,buf,10)).append("\n");
		delete[] buf;
	}

	virtual const char* what() const throw() {
		return msg.c_str();
	}
};

class FillingFailed : public exception {
private:
	string msg;
public:
	FillingFailed(const char* f) : msg(string("File : ").append(f).append("\nFilling from the file failed.")) {	}
		
	virtual const char* what() const throw() {
		return msg.c_str();
	}
};

#pragma warning (default : 4996)

bool LessIta(cTranslate x,cTranslate y);

bool GreaterIta(cTranslate x,cTranslate y);

void MemoryHandler();

vector<cTranslate> FillTransVecor(const char* csv);

void FillTransVector(vector<cTranslate> &v,const char* csv);

void ListAll(const vector<cTranslate> &);

void DelByEng(vector<cTranslate> &, const char *en);

void DelByIta(vector<cTranslate> &, const char *it);

void SortByEng(vector<cTranslate> &);

void SortByIta(vector<cTranslate> &);

void TranslateEng(const vector<cTranslate> &, const char *en);

void TranslateIta(const vector<cTranslate> &, const char *ita);
