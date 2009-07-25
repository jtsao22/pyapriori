#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>






int add(struct node **n, int d)
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
	while(n!= NULL)
	{
		printf("%s",n->data);
		n = n->next;
	}
	
	
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

int get_data(struct node *n, int index)
{
	int count = 0;
	while(n != NULL)
	{
		if(count == index)
			return n->data;
		count += 1;
		n = n->next; 	
	}

	// Functions that call this function will only call
	// this function if they know the data is in the list
	// Thus, this line should not be outputted and is here
	// in case there's an error. 	
	printf("Error: Could not find data");
}


