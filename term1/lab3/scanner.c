/************************************************************************
 *file: scanner.cpp
 *synopsis: definition of functions
 *author: Melnyk Andriy
 *written: 29/10/2013
 *last modified: 07/10/2013
 ************************************************************************/

#include "scanner.h"

SCAN_INFO* get_rec(char *csv_line)
{
	unsigned int i = 0,j=0;
	int field_numb = 1;
	char *tmp = (char *) malloc(128*sizeof(char));
	SCAN_INFO* rec = (SCAN_INFO *) malloc(sizeof(SCAN_INFO));

	if (rec == NULL || tmp == NULL || csv_line == NULL)
	{
		free(rec);
		free(tmp);
		return NULL;
	}

	for (i=0;i<=strlen(csv_line);i++)
	{
		if (csv_line[i] == ';' || csv_line[i] == 0)
		{
			tmp[j] = '\0';
			switch (field_numb)
			{
				case 1:	strcpy(rec->manufacturer,tmp);
						break;
				case 2:	strcpy(rec->model,tmp);
						break;
				case 3:	rec->year = atoi(tmp);
						break;
				case 4: rec->price = atof(tmp);
						break;
				case 5: rec->x_size = atoi(tmp);
						break;
				case 6: rec->y_size = atoi(tmp);
						break;
				case 7: rec->optr = atoi(tmp);
						break;
			}
			field_numb++;
			j=0;
			continue;
		}
		tmp[j] = csv_line[i];
		j++;
	}
	free(tmp);
	if (field_numb == 8) 
		return rec;

	free(rec);
	return NULL;
}

int scanner_equal(SCAN_INFO scn1,SCAN_INFO scn2)
//	return value  -> 0 if scn1 == scn2
//				  -> 1 if scn1 != scn2
{
	if (strcmp(scn1.manufacturer,scn2.manufacturer) == 0 &&
		strcmp(scn1.model,scn2.model) == 0 &&
		scn1.price == scn2.price &&
		scn1.year == scn2.year &&
		scn1.x_size == scn2.x_size &&
		scn1.y_size == scn2.y_size &&
		scn1.optr == scn2.optr)
			return 1;
	return 0;
}

FILE* fopen_with_check(char* path,char* mod)
{
	FILE* file;
	if (path == NULL || mod == NULL)
		return NULL;

	file = fopen(path,mod);
	if (file == NULL)
	{
		char buffer[255];
		strcpy(buffer,strerror(errno));
		printf("%s \n",buffer);
		exit(1);
	}

	return file;
}

int add_scanner(FILE* scanners,SCAN_INFO* new_scanner)
//return value 0 - failed
//			   1 - successfully
{
	int i = 1;
	int el_numb;
	SCAN_INFO tmp_scanner;
	if (scanners == NULL || new_scanner == NULL)
		return 0;
	
	rewind(scanners);
	if (fread(&el_numb,sizeof(int),1,scanners) == 0)
	{
		fwrite(&i,sizeof(int),1,scanners);
		fwrite(new_scanner,sizeof(SCAN_INFO),1,scanners);
	} else {
		while (fread(&tmp_scanner,sizeof(SCAN_INFO),1,scanners))
		{
			if (scanner_equal(tmp_scanner,*new_scanner))
				break;
			i++;
		}
		if (i - 1 == el_numb)
		{
			fwrite(new_scanner,sizeof(SCAN_INFO),1,scanners);
			rewind(scanners);
			fwrite(&i,sizeof(int),1,scanners);
		}
	}
	return 1;
}

int init_fill(char *dba,char *csv_file)
//return value 0 - failed
//			   1 - successfully
{
	char buf[512];
	char *csv_line;
	FILE* scanners;
	FILE* source_file;
	SCAN_INFO* tmp_scn;
	if (dba == NULL || csv_file == NULL)
		return 0;
	
	scanners = fopen_with_check(dba,"wb+");
	source_file = fopen_with_check(csv_file,"rt");
	while (! feof(source_file))
	{
		csv_line = fgets(buf,513,source_file);
		if ((tmp_scn = get_rec(csv_line)) != NULL)
			add_scanner(scanners,tmp_scn);
		free(tmp_scn);
	}
	fclose(scanners);
	fclose(source_file);
	return 1;
}

void scan_clone(SCAN_INFO* res,SCAN_INFO source)
{
	strcpy(res->manufacturer,source.manufacturer);
	strcpy(res->model,source.model);
	res->year = source.year;
	res->optr = source.optr;
	res->price = source.price;
	res->x_size = source.x_size;
	res->y_size = source.y_size;
}

void Qsort(int L,int R,SCAN_INFO** arr,int (*func_p)(SCAN_INFO,SCAN_INFO))
{
	SCAN_INFO centr = (*arr)[(L+R)/2];
	SCAN_INFO tmp_scn;
	int i = L, j= R;
	while (i <= j)
	{
		while (func_p((*arr)[i],centr))
			i++;
		while (func_p(centr,(*arr)[j]))
			j--;
		if (i <= j) 
		{
			scan_clone(&tmp_scn,(*arr)[i]);
			scan_clone(&(*arr)[i],(*arr)[j]);
			scan_clone(&(*arr)[j],tmp_scn);
			i++;
			j--;
		}
	}
	if (L < j) Qsort(L,j,arr,func_p); 
	if (i < R) Qsort(i,R,arr,func_p);
}

// functions predicates

#define CMP_STR_DEFINE(field) int field ##_cmp (SCAN_INFO scn1,SCAN_INFO scn2) {return (strcmp(scn1. ##field,scn2. ##field) < 0)?(1):(0);}
#define CMP_NUMB_DEFINE(field) int field ##_cmp (SCAN_INFO scn1,SCAN_INFO scn2) { return (scn1. ##field < scn2. ##field)?(1):(0);}
#define RETURN_CMP(name) if (strcmp(field_name,#name) == 0) return name ##_cmp;

CMP_STR_DEFINE(manufacturer);
CMP_STR_DEFINE(model);
CMP_NUMB_DEFINE(year);
CMP_NUMB_DEFINE(price);
CMP_NUMB_DEFINE(x_size);
CMP_NUMB_DEFINE(y_size);
CMP_NUMB_DEFINE(optr);

int (*find_cmp(char* field_name)) (SCAN_INFO,SCAN_INFO)
{
	RETURN_CMP(manufacturer);
	RETURN_CMP(model);
	RETURN_CMP(year);
	RETURN_CMP(optr);
	RETURN_CMP(price);
	RETURN_CMP(x_size);
	RETURN_CMP(y_size);
	return NULL;
}

//

int make_index(char *dba, char *field_name)
//return value 0 - failed
//			   1 - successfully
{
	FILE *scanners;
	FILE *indx_file;
	SCAN_INFO *tmp_arr,tmp_scanner;
	char indx_file_name[17];
	int el_numb,i,j;
	int (*func_p)(SCAN_INFO,SCAN_INFO);
	if (dba == NULL || field_name == NULL)
		return 0;

	func_p = find_cmp(field_name);
	scanners = fopen_with_check(dba,"rb");

	if (fread(&el_numb,sizeof(int),1,scanners) == 0 || func_p == NULL)
	{
		return 0;
		fclose(scanners);
	}
	
	if((tmp_arr = (SCAN_INFO *) calloc (el_numb,sizeof(SCAN_INFO))) == NULL)
	{
		return 0;
		fclose(scanners);
	}

	for (i = 0;i<el_numb;i++)
	{
		fread(&tmp_scanner,sizeof(SCAN_INFO),1,scanners);
		tmp_arr[i] = tmp_scanner;
	}
	Qsort(0,el_numb-1,&tmp_arr,func_p);
	indx_file = fopen_with_check(strcat(strcpy(indx_file_name,field_name),".idx"),"wb");
	if (fseek(scanners,sizeof(int),SEEK_SET))
	{
		fclose(scanners);
		return 0;
	}
	for (i = 0; i < el_numb;i++)
	{
		fread(&tmp_scanner,sizeof(SCAN_INFO),1,scanners);
		for (j = 0; j < el_numb;j++)
		 if (scanner_equal(tmp_scanner,tmp_arr[j]))
			fwrite(&j,sizeof(int),1,indx_file);	
	}

	free(tmp_arr);
	fclose(indx_file);
	fclose(scanners);
	return 1;
}

RECORD_SET* get_recs_by_index(char *dba , char *indx_field )
{
	FILE* scanners;
	FILE* indx_file;
	char idx_name[20];
	SCAN_INFO tmp_scan;
	RECORD_SET* return_set;
	int el_numb,indx,i;

	if (dba == NULL || indx_field == NULL)
		return NULL;

	scanners = fopen_with_check(dba,"rb");
	indx_file = fopen_with_check(strcat(strcpy(idx_name,indx_field),".idx"),"rb");

	if (fread(&el_numb,sizeof(int),1,scanners) == 0 ||
		(return_set = (RECORD_SET *) malloc (sizeof(RECORD_SET))) == NULL)
	{
		free(return_set);
		fclose(scanners);
		fclose(indx_file);
		return NULL;
	}

	return_set->rec_nmb = el_numb;
	if ((return_set->recs = (SCAN_INFO *) calloc (el_numb,sizeof(SCAN_INFO))) == NULL)
	{
		fclose(scanners);
		fclose(indx_file);
		return NULL;
	}

	
	i = 0;
	while (fread(&indx,sizeof(int),1,indx_file))
	{
		if (indx >= el_numb)
		{
			i = -1;
			break;
		}
		fread(&tmp_scan,sizeof(SCAN_INFO),1,scanners);
		return_set->recs[indx] = tmp_scan;
		i++;
	}

	fclose(scanners);
	fclose(indx_file);
	if (i == el_numb)
		return return_set;
	free(return_set->recs);
	free(return_set);
	return NULL;
}

void reindex(char *dba)
{
	make_index(dba,"manufacturer");
	make_index(dba,"model");
	make_index(dba,"year");
	make_index(dba,"x_size");
	make_index(dba,"y_size");
	make_index(dba,"optr");
	make_index(dba,"price");
}

int del_scan(char *dba, int n)
{
	int el_numb,i;
	FILE* scanners;
	SCAN_INFO tmp_scn;

	if (dba == NULL)
		 return 0;
	scanners = fopen_with_check(dba,"rb+");
	if (fread(&el_numb,sizeof(int),1,scanners) == 0)
	{
		fclose(scanners);
		return 0;
	}
	if  (n >= el_numb || n < 0)
	{
		fclose(scanners);
		return 0;
	}

	for (i = n + 1; i < el_numb; i++)
	{
		fseek(scanners,sizeof(int) + i*sizeof(SCAN_INFO),SEEK_SET);
		fread(&tmp_scn,sizeof(SCAN_INFO),1,scanners);
		fseek(scanners,sizeof(int) + (i-1)*sizeof(SCAN_INFO),SEEK_SET);
		fwrite(&tmp_scn,sizeof(SCAN_INFO),1,scanners);
	}
	_chsize(_fileno(scanners),sizeof(int) + (--el_numb)*sizeof(SCAN_INFO));
	rewind(scanners);
	fwrite(&el_numb,sizeof(int),1,scanners);

	fclose(scanners);
	reindex(dba);
	return 1;
}

/*******************************************************************************/

void scanner_to_file(FILE * output_file,SCAN_INFO scanner)
{
		fprintf(output_file,"manufacturer   => %s \n",scanner.manufacturer);
		fprintf(output_file,"model          => %s \n",scanner.model);
		fprintf(output_file,"year           => %d \n",scanner.year);
		fprintf(output_file,"price          => %f \n",scanner.price);
		fprintf(output_file,"x_size         => %d \n",scanner.x_size);
		fprintf(output_file,"y_size         => %d \n",scanner.y_size);
		fprintf(output_file,"optr           => %d \n\n\n",scanner.optr);
}

int prn2file_less_price(char* dba,char* output,float price_limit)
{
	SCAN_INFO tmp_scan;
	FILE* scanners;
	FILE* output_file;
	int el_numb,i = 0;

	if (dba == NULL || output == NULL)
		return 0;

	scanners = fopen_with_check(dba,"rb");
	output_file = fopen_with_check(output,"wt");
	
	if (fread(&el_numb,sizeof(int),1,scanners) == 0) 
	{
		fclose(scanners);
		fclose(output_file);
		return 0;
	}

	while (fread(&tmp_scan,sizeof(SCAN_INFO),1,scanners) != 0 && i < el_numb)
	{
		if (tmp_scan.price <= price_limit)
			scanner_to_file(output_file,tmp_scan);
			i++;
	}

	fclose(scanners);
	fclose(output_file);
	return 1;
}

int print_to_file(char* dba,char* output)
{
	int el_numb=0;
	SCAN_INFO scanner;
	FILE* dba_file;
	FILE* output_file;
	if (dba == NULL || output == NULL)
		return 0;

	dba_file = fopen_with_check(dba,"rb");
	output_file = fopen_with_check(output,"wt");
	if(! fread(&el_numb,sizeof(int),1,dba_file))
	{
		fclose(dba_file);
		fclose(output_file);
		return 0;
	}
	fprintf(output_file,"Number of elements in the file = %d \n\n",el_numb);

	while (fread(&scanner,sizeof(SCAN_INFO),1,dba_file))
		scanner_to_file(output_file,scanner);
	
	fputs("End",output_file);
	fclose(dba_file);
	fclose(output_file);
	return 1;
}
