#include <malloc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"

#ifdef CMOCKERY
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif 
// Redirect assert to mock_assert() so assertions can be caught by cmockery.
#ifdef assert
#undef assert
#endif // assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__)
void mock_assert(const int result, const char* expression, const char *file,
                 const int line);


int add(struct node **n, void* d, int count)
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
		(*n)->count = count;
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
		temp->next->count = count;
	}
	return 1;
	
}

unsigned char is_inside(struct node *list_of_lists, struct node *list)
{
	struct node *iter = list_of_lists;
	struct node *l_iter;
	struct node *temp;
	unsigned char inside;
	
	while(iter != NULL)
	{
		inside = TRUE;
		temp = (struct node *)iter->data;
		l_iter = list;
		while(temp != NULL)
		{
			if(*((uint32_t *)temp->data) != *((uint32_t *)l_iter->data))
				inside = FALSE;
			l_iter = l_iter->next;
			temp = temp->next;
		}
		if(inside == TRUE)
			return TRUE;
		iter = iter->next;
	}
	
	return FALSE;
}

unsigned char remove_list(struct node **list_of_lists, struct node *list)
/* Removes list from list_of_lists */ 
{
	if(list_of_lists == NULL)
		return FALSE;
	struct node *iter = *list_of_lists;
	struct node *temp;
	unsigned char inside = FALSE;
	
	if(iter == NULL || list == NULL)
		return FALSE;
	
	if(same_list((struct node *)iter->data,list))
	{
		*list_of_lists = iter->next;
		free_list((struct node **)&iter->data,&free_ints);
		free(iter);
		return TRUE;
	}
	
	while(iter->next != NULL)
	{
		if(same_list((struct node *)iter->next->data,list))
		{
			inside = TRUE;
			break;
		}
		iter = iter->next;
	}
	
	if(inside == TRUE)
	{
		temp = iter->next->next;
		free_list((struct node **)&iter->next->data,&free_ints);
		free(iter->next);
		
		iter->next = temp;
		return TRUE;
	}
	else
		return FALSE;
	
	
}

unsigned char same_list(struct node *l_1, struct node *l_2)
{
	struct node *iter_1 = l_1;
	struct node *iter_2 = l_2;
	while(iter_1 != NULL && iter_2 != NULL)
	{
		if(*((uint32_t *)iter_1->data) != *((uint32_t *)iter_2->data))
			return FALSE;
		iter_1 = iter_1->next;
		iter_2 = iter_2->next;
	}
	return TRUE;
}


void free_list(struct node **n,void (*free_funct)(void *))
{
	struct node *current;
	struct node *next;
	for(current = *n; current != NULL; current = next)
	{
		next = current->next; 
		(*free_funct)(current->data);
		free(current);
	}
	*n = NULL;
}

void free_ints(void *data)
{
	free(data);
}

void free_list_of_lists(struct node **n)
{
	struct node *current;
	struct node *next;
	for(current = *n; current != NULL; current = next)
	{
		next = current->next;
		free_list(((struct node**)(&current->data)),&free_ints);
		free(current);
	}		
	*n = NULL;
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

	return NULL;
}

struct node *get_node(struct node *n, int index)
{
	int count = 0;
	while(n != NULL)
	{
		if(count == index)
		{
			return n;
		}
		count++;
		n = n->next; 	
	}

	return NULL;
}

struct node *copy_list(struct node *n)
{
	uint32_t *temp = NULL;
	struct node *iter = n;
	struct node *copy = NULL;
	while(iter != NULL)
	{
		temp = malloc(sizeof(uint32_t));
		*temp = *((uint32_t *)iter->data);
		add(&copy,(void *)temp,iter->count);
		iter = iter->next;
	}
	return copy;
}

struct node *copy_list_of_lists(struct node *n)
{
	struct node *iter = n;
	struct node *copy = NULL;
	
	while(iter != NULL)
	{
		add(&copy,copy_list((struct node *)iter->data),iter->count);
		iter = iter->next;
	}
	return copy;
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

int is_subset(struct node *l_1, struct node *l_2)
/* Returns if l_2 is a subset of l_1 */ 
{
	if(l_1 == NULL || l_2 == NULL)
		return FALSE;
	
	if(get_len_list(l_1) < get_len_list(l_2))
		return FALSE;
	
	unsigned char inside;
	struct node *iter_1;
	struct node *iter_2 = l_2;

	while(iter_2 != NULL)
	{
		iter_1 = l_1;
		inside = FALSE;
		while(iter_1 != NULL)
		{
			if(*((int *)iter_1->data) == *((int *)iter_2->data))
				inside = TRUE;
			iter_1 = iter_1->next;
		}
		if(inside == FALSE)
			return FALSE;
		iter_2 = iter_2->next;
	}

	return TRUE;
}


