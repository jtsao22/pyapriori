#ifndef LINKED_LIST_
#define LINKED_LIST_


struct node 
{
	int data;
	struct node* next;
};



int add(struct node **n, int d);
void print_nodes(struct node *n);
int get_len_list(struct node *n);
int get_data(struct node *n, int index);



#endif /*LINKED_LIST_*/
