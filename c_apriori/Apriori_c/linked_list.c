#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)

// Redirect assert to mock_assert() so assertions can be caught by cmockery.
#ifdef assert
#undef assert
#endif // assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__)
void mock_assert(const int result, const char* expression, const char *file,
                 const int line);


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
		struct node *temp = *n;	
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		if((temp->next = malloc(sizeof(struct node)))==NULL)
		{
			printf("Memory allocation error");
			return 0;
		}
		temp->next->next = NULL;
		temp->next->data = d;	
	}
	return 1;
	
}




void free_list(struct node **n)
{
	struct node *current;
	struct node *next;
	for(current = *n; current != NULL; current = next)
	{
		next = current->next; 
		free(current->data);
		free(current);
	}

}

void free_list_of_lists(struct node **n)
{
	struct node *current;
	struct node *next;
	for(current = *n; current != NULL; current = next)
	{
		next = current->next;
		//struct node** temp = ;
		free_list(((struct node**)(&current->data)));
		free(current);
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
	printf("Error: The data was not found in linked list");
	assert(FALSE);

}



int compare_ints(void* first, void* second)
{
	int int_1 = *((int *)(first));
	int int_2 = *((int *)(second));
	if(int_1 < int_2)
		return -1;
	else if(int_1 > int_2)
		return 1;
	else
		return 0;
	
	
}


int compare_lists(void* first, void* second)
{
	
	struct node* list_1 = (struct node*)(first);
	struct node* list_2 = (struct node*)(second);
	
	while(list_1 != NULL && list_2 != NULL)
	{
		if(*((int *)(list_1->data)) < *((int *)(list_2->data)))
			return -1;
		else if(*((int *)(list_1->data)) > *((int *)(list_2->data)))
			return 1;
		else
		{
			list_1 = list_1->next;
			list_2 = list_2->next;
		}	
		
		
	}	
	
	if(list_1 == NULL && list_2 == NULL)	
		return 0;
	else if(list_1 == NULL && list_2 != NULL)
		return -1;
	else
		return 1;	
	
}
/* merge the lists.. */
struct node *merge(struct node *head_one, struct node *head_two,int (*cmp)(void *,void *)) 
{
	struct node *head_three;
	
	if(head_one == NULL) 
		return head_two;
	
	if(head_two == NULL) 
		return head_one;
	
	int compare = (*cmp)(head_one->data,head_two->data);
	if(compare == -1) 
	{
	  	head_three = head_one;
		head_three->next = merge(head_one->next, head_two,cmp);
	} 
	else 
	{
	  	head_three = head_two;
		head_three->next = merge(head_one, head_two->next,cmp);
	}
	
	return head_three;
}

struct node *mergesort(struct node *head,int (*cmp)(void *,void *)) 
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
	
	return merge(mergesort(head_one,cmp), mergesort(head_two,cmp),cmp);
}


