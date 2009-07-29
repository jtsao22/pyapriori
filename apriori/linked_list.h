#ifndef LINKED_LIST_
#define LINKED_LIST_


struct node 
{
	void* data;
	struct node* next;
};



int add(struct node **n, void* d);
void print_nodes(struct node *n);
int get_len_list(struct node *n);
void *get_data(struct node *n, int index);
void free_list(struct node **n);

struct node *mergesort(struct node *head);
struct node *merge(struct node *head_one, struct node *head_two);

#endif /*LINKED_LIST_*/
