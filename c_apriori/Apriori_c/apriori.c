#include <stdio.h>
#include <string.h>
#include "hash_map.h"
#include "apriori.h"
#include "linked_list.h"
#include "hash_tree.h"

#ifdef CMOCKERY
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif


struct node* apriori(double minsup, int w_size,
		char *i_file, char *o_file, int d_window_size, unsigned char node_threshold)
{
	struct node *transaction_list = parser(i_file, w_size,d_window_size);

	struct node *L_kminusone_set = one_item_sets(transaction_list,&minsup);

	printf("Minsup: %g\n",minsup);
	
	struct node *cand_trans_list = NULL;
	struct node *all_Lk = NULL;
	struct node *trans;
	

	struct hash_tree *ht = NULL;
	init_hash_tree(&ht,node_threshold);

	add(&all_Lk,copy_list_of_lists(L_kminusone_set),0);

	while(L_kminusone_set != NULL)
	{
		reinit_hash_tree(ht);
		cand_trans_list = generate(&L_kminusone_set,minsup,ht);
				
		trans = transaction_list;
		while(trans != NULL)
		{
			free_list_of_lists(&ht->cand_list_final);
			subset(ht,(struct node **)&trans->data);	
			trans = trans->next;
		}
		
		ht->l_k_set = NULL;
		
		check_minsup(ht,ht->root,minsup);
		
		if(ht->l_k_set != NULL)
		{
			add(&all_Lk,ht->l_k_set,0);
		}	
		
		free_list_of_lists(&cand_trans_list);	
		
		free_list_of_lists(&L_kminusone_set);
		L_kminusone_set = copy_list_of_lists(ht->l_k_set);
		
	}

	
	

	free_list_of_lists(&L_kminusone_set);

	free_list_of_lists(&transaction_list);
	ht->l_k_set = NULL;
	free_hash_tree(ht);
	
	return all_Lk;
}
void print_nodes(struct node *n)
{
	//print the node data in the linked list
	uint32_t k;
	
	while(n != NULL)
	{
		k = *((uint32_t *)n->data);
		printf("%i ",*((uint32_t *)n->data));
		n = n->next;
	}
}

void print_lists(struct node *n)
{
	while(n != NULL)
	{
		printf("List: ");
		print_nodes((struct node *)(n->data));
		
		printf("occurs: %i\n",n->count);
		n = n->next;	
	}
}

struct node *generate(struct node **f_item_list,double minsup,
		struct hash_tree *ht)
{
	*f_item_list = mergesort(*f_item_list,&compare_lists);
	
	/* Join Step Variable Declarations */ 
	struct node *trans_1 = *f_item_list;
	struct node *trans_2 = NULL;
	struct node *check = NULL;
	struct node *cand_trans_list = NULL; 
	
	/* Prune Step Variable Declarations */
	struct node *subsets;
	struct node *temp_list;
	struct node *item_list;
	struct node *copy;
	struct node *iter;
	struct node *next;
	unsigned char inside;
	struct node *checked_sets = NULL;
	
	/* Join Step of Generate function */
	
	while(trans_1 != NULL)
	{
		trans_2 = trans_1->next;
		while(trans_2 != NULL)
		{			
			check = check_item_last(trans_1->data,trans_2->data);
			if(check != NULL)
				add(&cand_trans_list,(void *)check,0);	
			trans_2 = trans_2->next;
		}
		trans_1 = trans_1->next;
	}
	
	/* Prune Step of Generate function */ 
	item_list = cand_trans_list;
	
	while(item_list != NULL)
	{
		
		next = item_list->next;
		temp_list = NULL;
		subsets = NULL;
		subsets = get_subsets_of((struct node *)item_list->data);
				
		iter = subsets;
	
		while(iter != NULL)
		{
//			if(!is_inside(checked_sets,(struct node *)iter->data))
//			{
				copy = copy_list((struct node *)iter->data);
				add(&checked_sets,copy,0);
				inside = FALSE;
				
				trans_1 = *f_item_list;
				while(trans_1 != NULL)
				{
					if(same_list((struct node *)trans_1->data,
							(struct node *)iter->data))
					{
						inside = TRUE;
						break;
					}
					trans_1 = trans_1->next;
				}
				
				if(inside == FALSE)
				{
					remove_list(&cand_trans_list,(struct node *)item_list->data);
					break;
				}
//			}	
			iter = iter->next;
			
		}
		
		free_list_of_lists(&subsets);	
		item_list = next;
		
	}
		
	item_list = cand_trans_list;
	while(item_list != NULL)
	{
		add_trans(&ht,copy_list((struct node *)item_list->data));
		item_list = item_list->next;
	}

	free_list_of_lists(&checked_sets);	
	return cand_trans_list;
}

struct node *get_subsets_of(struct node *item_list)
{
	int t;
	struct node *temp_list = NULL;
	struct node *iter = item_list;
	struct node *iter_2 = NULL;
	struct node *return_list = NULL;
	uint32_t *temp = NULL;
	
	while(iter != NULL)
	{
		iter_2 = item_list;	
		while(iter_2 != iter)
		{
			temp = malloc(sizeof(uint32_t));
			
			*temp = *((int *)iter_2->data);
			t = *temp;
			add(&temp_list,(void *)temp,0);
			iter_2 = iter_2->next;
		}
		
		iter_2 = iter->next;
		while(iter_2 != NULL)
		{
			temp = malloc(sizeof(uint32_t));
			*temp = *((uint32_t *)iter_2->data);
			t = *temp;
			add(&temp_list,(void *)temp,0);
			iter_2 = iter_2->next;
			
		}
		add(&return_list,(void *)temp_list,0);
		temp_list = NULL;
		
		iter = iter->next;
	}
	
	return return_list;
}




struct node *check_item_last(struct node *trans_1, struct node *trans_2)
{
	if(trans_1 == NULL || trans_2 == NULL)
		return NULL;
	
	struct node *iter_1 = trans_1;
	struct node *iter_2 = trans_2;
	
	while(iter_1->next != NULL)
	{
		if(*((uint32_t *)iter_1->data) != *((uint32_t *)iter_2->data))
		{
			return NULL;
		}
		iter_1 = iter_1->next;
		iter_2 = iter_2->next;
	}
	if(*((uint32_t *)iter_1->data) != *((uint32_t *)iter_2->data))
	{
		uint32_t *temp = malloc(sizeof(uint32_t));
		*temp = *((uint32_t *)iter_2->data);
		iter_1 = NULL;
		iter_1 = copy_list(trans_1);
		add(&iter_1,(void *)temp,0);
		return iter_1;
	}
	else
		return NULL;
}

struct node* one_item_sets(struct node* T, double *minsup)
{
	struct node *iter = T;
	struct node *all_trans_list = NULL;
	int total_num_trans = 0;
	uint32_t *temp = NULL;
	while(iter != NULL)
	{
		struct node *transaction = (struct node*)iter->data;
		while(transaction != NULL)
		{
			temp = malloc(sizeof(uint32_t));
			*temp = *((uint32_t *)(transaction->data));
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

	all_trans_list = mergesort(all_trans_list,&compare_ints);

	/* set iterator for all_trans_list and initialize variables */
	iter = all_trans_list;

	struct node *item_list = NULL;
	struct node *temp_list = NULL;
	temp = NULL;
	uint32_t item;
	if(iter != NULL)
		item = *((uint32_t *)(iter->data));
	int count = 0;
	while(iter != NULL)
	{		
		if(*((uint32_t *)(iter->data)) != item)
		{
			if(count >= *minsup)
			{
				temp = malloc(sizeof(uint32_t));
				*temp = item;
				if(*temp != 0)
				{
					if(!add(&temp_list,(void *)temp,0))
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
			item = *((uint32_t *)(iter->data));
			count = 1;
			temp_list = NULL;

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
		temp = malloc(sizeof(uint32_t));
		*temp = item;
		if(*temp != 0)
		{
			if(!add(&temp_list,(void *)temp,0))
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

	free_list(&all_trans_list,&free_ints);
	return item_list;
}

struct node* parser(char* file_name,int w_size, int max_d_size)
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

	if(max_d_size < 0)
	{
		//get the windows w/o dynamic windowing
		list_of_parses = get_windows(token_list, w_size);

	}
	else
	{
		/* get the windows w/dynamic windowing */
		list_of_parses = get_dynamic_windows(token_list,max_d_size);
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
	free_list(&token_list,&free_ints);
	fclose(fp);

	return list_of_parses;
}



struct node* get_windows(struct node* token_list, int w_size)
{
 	int k = 0;
 	int token = 0;
 	int iter = 0;
 	int value = 0;
 	uint32_t * temp = NULL;
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
 			value = *((uint32_t *)temp_token->data);

			/* this check_inside function checks if *temp is in side
			 * parse_list by parsing through the list. This means we
			 * assume a fairly small window size for performance */
			if(!check_inside(value, parse_list))
			{
				temp = (uint32_t *)malloc(sizeof(uint32_t));
				*temp = value;
	 			if(!add(&parse_list,(void *)temp,0))
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
 				add(&list_of_parses,(void *)parse_list,0);
 				parse_list = NULL;
 				iter = 0;
 			}
 			temp_token = temp_token->next;
 			token++;

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
		if(*((uint32_t *)(list->data)) == value)
			return TRUE;
		list = list->next;
	}

	return FALSE;
}

struct node* get_dynamic_windows(struct node* token_list,int max_d_size)
{
	uint32_t *temp = NULL;
	int infinite = FALSE;
	int counter;
	struct node *parse_list = NULL;
 	struct node *list_of_parses = NULL;
	struct node* start_t = token_list;
	struct node* token = NULL;
	if(max_d_size >= 0 && max_d_size <= 1)
	{
		infinite = TRUE;
		max_d_size = 2;
	}
	while(start_t != NULL)
	{
		temp = (uint32_t *)malloc(sizeof(uint32_t));
		*temp = *((uint32_t *)start_t->data);
		if(!add(&parse_list,(void *)temp,0))
		{
			printf("Error while reading from file");
			exit(0);
		}
		token = start_t->next;
		counter = 1;
		
		while(token != NULL)
		{
			
				
			if(*((uint32_t *)token->data) == *((uint32_t *)start_t->data) || counter >= max_d_size)
			{
				
				if(!add(&list_of_parses,(void *)parse_list,0))
				{
					printf("Error with Memory Allocation");
		 			exit(0);
				}
				parse_list = NULL;
				break;
				
			}
			else
			{
				if(!check_inside(*((uint32_t *)token->data), parse_list))
				{
					temp = (uint32_t *)malloc(sizeof(uint32_t));
					*temp = *((uint32_t *)token->data);
			
					if(!add(&parse_list,(void *)temp,0))
					{
						printf("Error while reading from file");
						exit(0);
					}
				}
			}
			token = token->next;
			if(infinite == FALSE)
				counter += 1;
		}
		if(parse_list != NULL || *((uint32_t *)token->data) != *((uint32_t *)start_t->data))
		{
			if(parse_list != NULL)
			{
				parse_list = mergesort(parse_list,&compare_ints);
				if(!add(&list_of_parses,(void *)parse_list,0))
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
	uint32_t *temp = NULL;

	while(!feof(fp))
	{

		if(fscanf(fp,"%as",&s) > 0)
		{
			temp = malloc(sizeof(uint32_t));
			*temp = atoi(s);
			if(!add(&head,(void *) temp,0))
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




