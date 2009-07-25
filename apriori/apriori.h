#ifndef APRIORI_H_
#define APRIORI_H_
#include<stdlib.h>
#include <string.h>
#include "linked_list.h"

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif



int parser(char* file_name,int w_size, int d_wind);

FILE* read_file(char* file_name);

 struct node* get_token_list(FILE* fp);
 
 struct node** get_windows(struct node* token_list, int w_size);

#endif /*APRIORI_H_*/
