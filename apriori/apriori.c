#include <stdio.h>
#include <string.h>
#include "apriori.h"
#include "linked_list.h"

int parser(char* file_name,int w_size, int d_wind)
{
	// Open the file and get the file descriptor
	FILE* fp = read_file(file_name);
	
	if(fp == NULL)
	{
		return 0;
	}
	
	// get the token list
	struct node* token_list = get_token_list(fp);
	
	if(d_wind == FALSE)
	{
		//get_windows(
		
	}
	
	else
	{
	}
	
	return 1;

}

 struct node** get_windows(struct node* token_list, int w_size)
 {
 	int k = 0;
 	int i = 0;
 	int token = 0;
 	int iter = 0;
 	struct node *parse_list = NULL;
 	 	
 	for(k; k < get_len_list(token_list)-w_size + 1; k++)
 	{ 
 		for(token = i; token < i + w_size; token++)
 		{
 			if(!add(&parse_list,get_data(token_list,token)))
 			{
 				printf("Error while reading from file");
 				exit(0);
 			}
 			if(iter < w_size -1)
 				iter++;
 			
 		}
 			
 	}
 	
 }

struct node* get_token_list(FILE* fp)
{
	char* s;
	struct node *head = NULL;
	
		
	while(!feof(fp))
	{
		
		if(fscanf(fp,"%as",&s) > 0)
		{	
			if(!add(&head,atoi(s)))
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


