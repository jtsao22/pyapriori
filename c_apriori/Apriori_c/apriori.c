#include <stdio.h>
#include <string.h>

#include "apriori.h"
#include "linked_list.h"


extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)



struct node* apriori(double minsup, int w_size,
		char *i_file, char *o_file, int d_window, int node_threshold)
{
	struct node *transaction_list = parser(i_file, w_size,d_window);
	
	struct node *L_1 = one_item_sets(transaction_list,&minsup);

	struct node *L_kminusone_set = L_1;
	
	printf("Minsup: %g\n",minsup);
	
	int k = 2;
	struct node *cand_trans_list = NULL;
	struct node *cand_list_final = NULL;
	
	
	
	return L_1;
			
}			


struct node* one_item_sets(struct node* T, double *minsup)
{
	struct node *iter = T;
	struct node *all_trans_list = NULL; 
	int total_num_trans = 0;
	int *temp = NULL;
	while(iter != NULL)
	{
		struct node *transaction = (struct node*)iter->data;
		while(transaction != NULL)
		{
			temp = malloc(sizeof(int));
			*temp = *((int *)(transaction->data));
			if(*temp != 0)
			{
				if(!add(&all_trans_list,(void *)temp,0))
	 			{
	 				printf("Error with Memory Allocation");
	 				exit(0);
	 			}
			}
			transaction = transaction->next;
		}
		total_num_trans++;
		iter = iter->next;
	}
	
	/* calculate the finite minsup number out of the percentage and total */ 
	*minsup = (*minsup) * total_num_trans;

	free_list_of_lists(&T);
	
	all_trans_list = mergesort(all_trans_list,&compare_ints);
	
	/* set iterator for all_trans_list and initialize variables */ 
	iter = all_trans_list;
	
	struct node *item_list = NULL;
	struct node *temp_list = NULL;
	temp = NULL;
	int item = *((int *)(iter->data));
	int count = 0;
	while(iter != NULL)
	{
		if(*((int *)(iter->data)) != item)
		{
			if(count >= *minsup)
			{
				temp = malloc(sizeof(int));
				*temp = item;
				if(*temp != 0)
				{
					if(!add(&temp_list,(void *)temp,1))
		 			{
		 				printf("Error with Memory Allocation");
		 				exit(0);
		 			}
				}
				
				if(!add(&item_list,(void *)temp_list,count))
				{
					printf("Error with Memory Allocation");
		 			exit(0);
				}
				item = *((int *)(iter->data));
				count = 1;
				temp_list = NULL;
			}

		}
		else
		{
			count++;
		}
		iter = iter->next;
		
	}
	/* add last transaction */ 
	if(count > *minsup)
	{
		temp = malloc(sizeof(int));
		*temp = item;
		if(*temp != 0)
		{
			if(!add(&temp_list,(void *)temp,1))
 			{
 				printf("Error with Memory Allocation");
 				exit(0);
 			}
		}
		if(!add(&item_list,(void *)temp_list,count))
		{
			printf("Error with Memory Allocation");
		 	exit(0);
		}
	}
	
	
	free_list(&all_trans_list);
	
	
	return item_list;
}








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
		/* get the windows w/dynamic windowing */ 
		list_of_parses = get_dynamic_windows(token_list);
	}
	//sort the list
	list_of_parses = mergesort(list_of_parses,&compare_lists);
	
	/* find average window size and max window size */ 

	struct node* iter = list_of_parses;
	
	int total_window_size = 0;
	int max_window_size = 0;
	int temp;
	
	while(iter != NULL)
	{
		temp = get_len_list((struct node*)(iter->data));
		total_window_size += temp;
		if(max_window_size < temp)
			max_window_size = temp;
		iter = iter->next;	
	}
	
	printf("Average Window Size: ");
	if(get_len_list((struct node*)(list_of_parses)) > 0)
	{
		printf("%i\n",total_window_size/get_len_list((struct node*)(list_of_parses)));
	}
	printf("Max Window Size: ");
	printf("%i\n",max_window_size);

	/*cleanup */ 
	free_list(&token_list);
	fclose(fp);

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
 	struct node *current = token_list;
 	struct node *temp_token = NULL;
 	int end_point = get_len_list(token_list)-w_size +1;

 	while(current != NULL && k < end_point)
 	{ 
 		temp_token = current;
 		token = k;
 		while(temp_token != NULL && token < k + w_size)
 		{
 			temp = (int *)malloc(sizeof(int));
 			*temp = *((int *)temp_token->data);
 			if(*temp != 0)
 			{
 				/* this check_inside function checks if *temp is in side 
 				 * parse_list by parsing through the list. This means we
 				 * assume a fairly small window size for performance */ 
 				if(!check_inside(*temp, parse_list))
 				{
		 			if(!add(&parse_list,(void *)temp,1))
		 			{
		 				printf("Error while reading from file");
		 				exit(0);
		 			}
		 		
 				}
				if(iter < w_size -1)
	 				iter++;
	 			else
	 			{
	 				parse_list = mergesort(parse_list,&compare_ints);
	 				add(&list_of_parses,(void *)parse_list,1);
	 				parse_list = NULL;
	 				iter = 0;
	 					
	 			}
	 			temp_token = temp_token->next;
	 			token++;
 			}
 		} 	
 		current = current->next;
 		k++;
 				
 	}
 	return list_of_parses;
}

int check_inside(int value, struct node *list)
{
	while(list != NULL)
	{
		if(*((int *)(list->data)) == value)
			return TRUE;
		list = list->next;
	}
	
	return FALSE;
}

struct node* get_dynamic_windows(struct node* token_list)
{
	int *temp = NULL;
	struct node *parse_list = NULL;
 	struct node *list_of_parses = NULL;
	struct node* start_t = token_list;
	struct node* token = NULL;
	while(start_t != NULL)
	{
		temp = (int *)malloc(sizeof(int));
		*temp = *((int *)start_t->data);
		if(!add(&parse_list,(void *)temp,1))
		{
			printf("Error while reading from file");
			exit(0);
		}
		token = start_t->next;
		while(token != NULL)
		{
			if(*((int *)token->data) == *((int *)start_t->data))
			{
				parse_list = mergesort(parse_list,&compare_ints);
				if(!add(&list_of_parses,(void *)parse_list,1))
				{
					printf("Error with Memory Allocation");
		 			exit(0);
				}
				parse_list = NULL;
				break;
			}
			else
			{
				temp = (int *)malloc(sizeof(int));
				*temp = *((int *)token->data);
				if(!add(&parse_list,(void *)temp,1))
				{
					printf("Error while reading from file");
					exit(0);
				}
			}
			token = token->next;
		}
		if(parse_list != NULL || *((int *)token->data) != *((int *)start_t->data))
		{
			if(parse_list != NULL)
			{
				parse_list = mergesort(parse_list,&compare_ints);
				if(!add(&list_of_parses,(void *)parse_list,1))
				{
					printf("Error with Memory Allocation");
		 			exit(0);
				}
			}
			parse_list = NULL;
		}	
		start_t = start_t->next;
		
			
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
			if(!add(&head,(void *) temp,1))
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




