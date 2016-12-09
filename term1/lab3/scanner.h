/************************************************************************
*file: scanner.h
*purpose: declarations for scanner functions
*author: Melnyk Andriy
*written: 29/10/2013
*last modified: 29/10/2013
*************************************************************************/

#pragma once
#pragma warning (disable : 4996)

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <io.h>

typedef struct {
	char manufacturer[127];		// изготовитель
	int year;					// год изготовления
	char model[128];			// наименование модели
	float price;				// цена
	int x_size;					// горизонтальный размер области сканирования
	int y_size;					// вертикальный размер области сканирования
	int optr;					// оптическое разрешение
} SCAN_INFO;

typedef struct {
	int rec_nmb;				//number of records
	SCAN_INFO *recs;			//records 
}RECORD_SET;

	

int add_scanner(FILE* scanners,SCAN_INFO* new_scanner);

int init_fill (char *dba,char *csv_file);

int make_index(char *dba, char *field_name);

RECORD_SET* get_recs_by_index(char *dba , char *indx_field );

void reindex(char *dba);

int del_scan(char *dba, int n);

int prn2file_less_price(char* dba,char* output,float price_limit);

//////////////////

int print_to_file(char* dba,char* output);

FILE* fopen_with_check(char* path,char* mod);