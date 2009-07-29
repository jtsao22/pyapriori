#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define malloc(size) _test_malloc(size, __FILE__, __LINE__)

int add(struct node **n, void* d)
{
	//add a node to linked list
	if(*n == NULL)
	{
		if((*n = malloc(sizeof(struct node)))==NULL)
		{
			printf("Memory allocation error");
			return 0;
		}
		(*n)->next = NULL;
		(*n)->data = d;
		
		
		
	}
	else
	{
		add(&((*n)->next),d);	
	}
	return 1;
	
}

void print_nodes(struct node *n)
{
	//print the node data in the linked list
	while(n != NULL)
	{
		printf("%i\n",*((int *)n->data));
		n = n->next;
	}
		
}


void free_list(struct node **n)
{
	struct node *current;
	struct node *next;
	for(current = *n; current != NULL; current= next)
	{
		next = current->next; 
		free(current);
	}
	*n = current;
	
	
}




int get_len_list(struct node *n)
{
	int len = 0;
	while(n != NULL)
	{
		len += 1;
		n = n->next;
	}
	return len;		
}

void *get_data(struct node *n, int index)
{
	int count = 0;
	while(n != NULL)
	{
		if(count == index)
		{
			return n->data;
		}
		count++;
		n = n->next; 	
	}

	// Functions that call this function will only call
	// this function if they know the data is in the list
	// Thus, this line should not be outputted and is here
	// in case there's an error. 	
	printf("Error: Could not find data\n");
	int *temp = malloc(sizeof(int));
	*temp = -3;
	return (void *)temp;
}

/* merge the lists.. */
struct node *merge(struct node *head_one, struct node *head_two) 
{
	struct node *head_three;
	
	if(head_one == NULL) 
		return head_two;
	
	if(head_two == NULL) 
		return head_one;
	
	if(*((int *)(head_one->data)) < *((int *)(head_two->data))) 
	{
	  	head_three = head_one;
		head_three->next = merge(head_one->next, head_two);
	} 
	else 
	{
	  	head_three = head_two;
		head_three->next = merge(head_one, head_two->next);
	}
	
	return head_three;
}



struct node *mergesort(struct node *head) 
{
	struct node *head_one;
	struct node *head_two;
	
	if((head == NULL) || (head->next == NULL)) 
		return head;
	
	head_one = head;
	head_two = head->next;
	while((head_two != NULL) && (head_two->next != NULL)) 
	{
		head = head->next;
	  	head_two = head->next->next;
	}
	head_two = head->next;
	head->next = NULL;
	
	return merge(mergesort(head_one), mergesort(head_two));
}


