/************************************************************************
 *file: scanner_db.c
 *synopsis: testing of functions
 *author: Melnyk Andriy
 *written: 29/10/2013
 *last modified: 07/11/2013
 ************************************************************************/

#include "scanner.h"

int main ()
{
	int indx;
	int i;
	char csv_name[] = "scanners.csv";
	char dba_name[] = "scanners.dat";
	RECORD_SET* test;
	FILE* test_idx;

	printf("Test init_fill. Return value : 1 -> successfully \n");
    printf("                             : 0 -> failed \n");
	printf("Result  %d \n\n",init_fill(dba_name,csv_name));
	init_fill(dba_name,csv_name);
	print_to_file(dba_name,"afterFilling.txt");

	printf("Test make_index. Return value : 1 -> successfully \n");
    printf("                              : 0 -> failed \n");
	printf("Result  %d \n\n",make_index(dba_name,"model"));
	test_idx = fopen_with_check("model.idx","rb");
	printf("File model.idx \n");
	for (i = 0; i < 6 ; i++)
	{
		fread(&indx,sizeof(int),1,test_idx);
		printf("& %d &",indx);
	}
	printf("\n\n");
	fclose(test_idx);
	reindex(dba_name);

	printf("Test get_recs_by_index. Return value : vector \n");
	printf("Returned vector is\n\n");
	test = get_recs_by_index(dba_name,"model");
	for (i = 0;i < 6; i++)
	{
		printf("manufacturer   => %s \n",test->recs[i].manufacturer);
		printf("model          => %s \n",test->recs[i].model);
		printf("year           => %d \n",test->recs[i].year);
		printf("price          => %f \n",test->recs[i].price);
		printf("x_size         => %d \n",test->recs[i].x_size);
		printf("y_size         => %d \n",test->recs[i].y_size);
		printf("optr           => %d \n\n\n",test->recs[i].optr);
	}
	free(test);

	printf("Test del_scan. Return value : 0 -> deleted \n");
	printf("                            : 1 -> failed \n");
	print_to_file(dba_name,"beforeDel.txt");
	printf("Result(1) -> %d \n",del_scan(dba_name,1));
	printf("Result(0) -> %d \n",del_scan(dba_name,0));
	printf("Result(3) -> %d \n\n",del_scan(dba_name,3));
	print_to_file(dba_name,"afterDel.txt");

	init_fill(dba_name,csv_name);
	printf("Test prn2file_less_price \n\n");
	prn2file_less_price(dba_name,"price390.txt",300);
	prn2file_less_price(dba_name,"price960.txt",960);
	return 0;
}
