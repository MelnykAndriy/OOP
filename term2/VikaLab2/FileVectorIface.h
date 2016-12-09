/************************************************************************
*file: FileVectorIface.h
*purpose: declaration of additional File interface 
*author: Victoria Buts
*written: 30/04/2014
*last modified: 01/05/2014
*************************************************************************/

#pragma once

#include <list>
#include "File.h"
#include <string>

list<File>* loadFilesFromCsvToVecor(const string);

void ListAll( const std::list<File> &);

void AddKeyword(std::list <File> &, char *);
//Добавить в файлы ключевое слово

void DelKeyword(std::list <File> &, char *kwrd);

//Удалить из файлов ключевое слово kwrd.

void DelKeywordByLen(std::list <File> &, int len);
//Удалить из файлов ключевые слова, длины больше len.

void SortBySize(std::list <File> &);
//Отсортировать элементы контейнера в лексикографическом порядке имен файлов.

void SortByKeywordsNumber(std::list <File> &);
//Отсортировать элементы контенера в порядке неубывания числа ключевых слов.