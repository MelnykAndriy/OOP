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
//�������� � ����� �������� �����

void DelKeyword(std::list <File> &, char *kwrd);

//������� �� ������ �������� ����� kwrd.

void DelKeywordByLen(std::list <File> &, int len);
//������� �� ������ �������� �����, ����� ������ len.

void SortBySize(std::list <File> &);
//������������� �������� ���������� � ������������������ ������� ���� ������.

void SortByKeywordsNumber(std::list <File> &);
//������������� �������� ��������� � ������� ���������� ����� �������� ����.