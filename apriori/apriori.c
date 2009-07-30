#include <stdio.h>
#include <string.h>
#include "apriori.h"
#include "linked_list.h"

//#if UNIT_TESTING
//#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
//#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
//#endif // UNIT_TESTING

struct node* parser(char* file_name,int w_size, int d_wind)
{
	struct node* list_of_parses = NULL;
	// Open the file and get the file descriptor
	FILE* fp = read_file(file_name);
	if(fp == NULL)
	{
		return NULL;
	}
	
	// get the token list
	struct node* token_list = get_token_list(fp);
	
	if(d_wind == FALSE)
	{
		//get the windows w/o dynamic windowing
		list_of_parses = get_windows(token_list, w_size);
		
	}
	
	else
	{
	}
	
	//sort the list
	list_of_parses = mergesort(list_of_parses,&compare_lists);
	
	
	return list_of_parses;

}

struct node* get_windows(struct node* token_list, int w_size)
{
 	int k = 0;
 	int token = 0;
 	int iter = 0;
 	int * temp = NULL;
 	struct node *parse_list = NULL;
 	struct node *list_of_parses = NULL;
 	for(k; k < get_len_list(token_list)-w_size + 1; k++)
 	{ 
 		for(token = k; token < k + w_size; token++)
 		{
 			temp = malloc(sizeof(int));
 			*temp = *((int *)get_data(token_list,token));
 			if(!add(&parse_list,(void *)temp))
 			{
 				printf("Error while reading from file");
 				exit(0);
 			}
 			
 			if(iter < w_size -1)
 				iter++;
 			else
 			{
 				add(&list_of_parses,(void *)parse_list);
 				parse_list = NULL;
 				iter = 0;
 					
 			}
 			
 		} 			
 	}
 
 	return list_of_parses;
  	
}

struct node* get_token_list(FILE* fp)
{
	char *s;
	struct node *head = NULL;
	int *temp = NULL;
		
	while(!feof(fp))
	{
		
		if(fscanf(fp,"%as",&s) > 0)
		{	
			temp = malloc(sizeof(int));
			*temp = atoi(s);
			if(!add(&head,(void *) temp))
			{
				printf("Error while reading from file");
				exit(1);
			}
			
		}
		else
			break;
			
	}	
	
	return head;
	
}



FILE* read_file(char* file_name)
{
	
	
	FILE *fp;

	if((fp=fopen(file_name,"r"))==NULL)
	{
		printf("Cannot open file.\n");
		return NULL;
	}
	
	
	return fp;
		
	
}




