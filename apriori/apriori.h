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



struct node* parser(char* file_name,int w_size, int d_wind);

FILE* read_file(char* file_name);

struct node* get_token_list(FILE* fp);
 
struct node* get_windows(struct node* token_list, int w_size);

int compare_ints(void* first, void* second);

int compare_lists(void* first, void* second);

#endif /*APRIORI_H_*/
