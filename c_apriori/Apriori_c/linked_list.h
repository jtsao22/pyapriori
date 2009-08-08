#ifndef LINKED_LIST_
#define LINKED_LIST_

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif


struct node 
{
	void* data;
	int count;
	struct node* next;
};



int add(struct node **n, void* d, int count);
void print_nodes(struct node *n);
int get_len_list(struct node *n);
void *get_data(struct node *n, int index);
void free_ints(void *data, void *extra_free);
void free_list(struct node **n,void (*free_funct)(void *,void *));


void free_list_of_lists(struct node **n);

struct node *mergesort(struct node *head,int (*cmp)(void *,void *));
struct node *merge(struct node *head_one, struct node *head_two,int (*cmp)(void *,void *));

#endif /*LINKED_LIST_*/
