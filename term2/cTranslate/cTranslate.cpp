/************************************************************************
*file: cTranslate.cpp
*purpose: implements methods of class cTranslate
*author: Melnyk Andriy
*written: 25/01/2014
*last modified: 25/01/2014
*************************************************************************/

#include "cTranslate.h"
#include <fstream>
#pragma warning (disable : 4996)

using namespace std;

cTranslate::cTranslate(char* _eng,char* _ita) {
	if (_eng && _ita) {
		eng = new char[strlen(_eng) + 1];
		ita = new char[strlen(_ita) + 1];
		strcpy(eng,_eng);
		strcpy(ita,_ita);
	} else {
		eng = NULL;
		ita = NULL;
	}

	if (!handlerIsDef) 
		set_new_handler(MemoryHandler);
}

cTranslate::cTranslate() {
	ita = NULL;
	eng = NULL;
	if (!handlerIsDef) 
		set_new_handler(MemoryHandler);
}

cTranslate::~cTranslate(void) {
	delete[] eng;
	delete[] ita;
}

cTranslate& cTranslate::operator=(const cTranslate &pair) {
	CP_PAIR(pair)
	return *this;
}

void cTranslate::MakePair(char *eng, char *ita) {
	if (eng && ita) {
		delete[] this->eng;
		delete[] this->ita;
		strcpy(this->eng = new char[strlen(eng) + 1],eng);
		strcpy(this->ita = new char[strlen(ita) + 1],ita);
	}
}

int strcompare(const char* str1,const char* str2) {
	return (str1 && str2)?(strcmp(str1,str2)):((str1 && !str2)?(1):((!str1 && str2)?(-1):(0)));
}

bool LesserIta(cTranslate x,cTranslate y) {
	return strcompare(x.ita,y.ita) < 0;
}

bool GreaterIta(cTranslate x,cTranslate y) {
	return strcompare(x.ita,y.ita) > 0;
}

ostream& operator<<(ostream& to,const cTranslate& obj) {
	if (obj.eng) { 
		return to << "eng :  " << obj.eng << endl
		   << "ita :  " << obj.ita << endl;
	} 
	return to << "Nothing to print." << endl;
}

void MemoryHandler() { 
	perror("Operator new failed!\n");
	exit(EXIT_FAILURE);
}

void ListAll(const vector<cTranslate> &container) {
	if (!container.empty()) {
		const int size = container.size();
		for(int i = 0; i < size; i++) {
			cout << "Pair numb :" << i  << endl;
			container[i].Print();
		}
	}
}

#define DEL_BY(word,accessor,container) 	if (!container.empty() && word) { \
												vector<cTranslate>::iterator iter = container.begin(); \
												while( iter != container.end()){ \
													if (strcompare(word,(*iter).accessor()) == 0) \
														if (iter != container.begin()) \
															container.erase((--iter)+1); \
														else { \
															container.erase(iter); \
															iter = container.begin(); \
															continue; \
														} iter++; } }

void DelByEng(vector<cTranslate> &container, const char *eng) {
	DEL_BY(eng,GetEng,container);
}

void DelByIta(vector<cTranslate> &container, const char *ita) {
	DEL_BY(ita,GetIta,container);
}

void SortByEng(vector<cTranslate> &container) {
	sort(container.begin(),container.end());
}

void SortByIta(vector<cTranslate> &container) {
	sort(container.begin(),container.end(),&LesserIta);
}

#define TRANSLATE(word,from,to) 	if (!container.empty() && word) { \
										const int size = container.size(); \
										for(int i = 0; i < size;i++) \
											if (strcompare(word,container[i].Get##from()) == 0) { \
												cout << #from " word : " << word << endl; \
												cout << "\t-> " << container[i].Get##to()<< endl; }}

void TranslateEng(const vector<cTranslate> &container, const char *eng) {
	TRANSLATE(eng,Eng,Ita);
}

void TranslateIta(const vector<cTranslate> &container, const char *ita) {
	TRANSLATE(ita,Ita,Eng);
}

#define REWIND(zero,Try) 	tmp[Try] = NULL; \
							if (Try == 0) throw new UnexpectedCharacter(line,pos,csv); \
							zero = 0;

#define PUSH_CTRANSLATE() 	v.push_back(cTranslate(eng,ita)); \
							tmp = eng;	\

#define FINISH()	delete[] eng; \
					delete[] ita; \
					f.close();

void FillTransVector(vector<cTranslate> &v,const char* csv) {
	if (csv == NULL) return;

	ifstream f;
	short allocByte = 16;
	char* eng = new char[allocByte];
	char* ita = new char[allocByte];

	try { 
		short line = 1 , i = 0 , pos = 0;
		char ch , *tmp = eng;
		f.open(csv);
		while ( f.good() ) {
			f.get(ch);
			pos++;	
			switch (ch) {
				case ';' :
					REWIND(i,i);
					if (tmp == eng) {
						tmp = ita;
						continue;
					}
					PUSH_CTRANSLATE();
					continue;
				case '\n' :
					REWIND(pos = i ,i);
					line++;
					PUSH_CTRANSLATE();
					continue;
				default :
					if (isspace(ch)) continue; 
					if (!isalpha(ch)) throw new UnexpectedCharacter(line,pos,csv);
			}

			if (i == allocByte - 1) {
				allocByte <<= 1;
				eng = strcpy(new char[allocByte],eng);
				ita = strcpy(new char[allocByte],ita);
			}

			tmp[i] = ch;
			i++;
		
			if ( f.fail() && ! f.eof() ) throw new FillingFailed(csv);
		}
		REWIND(i,i - 1);
		PUSH_CTRANSLATE();
	} catch (exception* exc) {
		FINISH();
		throw exc;
	}
	FINISH();
}

vector<cTranslate> FillTransVector(const char* csv) {
	vector<cTranslate> retVector;
	FillTransVector(retVector,csv);
	return retVector;
}

#pragma warning (default : 4996)

//void Qsort(vector<cTranslate>container,vector<cTranslate>::iterator left,vector<cTranslate>::iterator right) {
//	vector<cTranslate>::iterator elm = left + (right-left)/2;
//	vector<cTranslate>::iterator i = left,j = right;
//		while (i < j) { 
//			while (*i < *elm) i++;
//			while (*j > *elm) j--;
//			if (i <= j) {
//				cTranslate tmp = *i;
//				*i = *j;
//				*j = tmp;
//				i++;
//				j--;
//			}
//		}
//		if (left < j) Qsort(container,left,j);
//		if (i < right) Qsort(container,i,right);
//}