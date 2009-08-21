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
struct node *get_node(struct node *n, int index);

struct node *copy_list(struct node *n);
struct node *copy_list_of_lists(struct node *n);

unsigned char is_inside(struct node *list_of_lists, struct node *list);

unsigned char same_list(struct node *l_1, struct node *l_2);

unsigned char remove_list(struct node **list_of_lists, struct node *list);

void free_ints(void *data);
void free_list(struct node **n,void (*free_funct)(void *));
void free_list_of_lists(struct node **n);

struct node *mergesort(struct node *head,int (*cmp)(void *,void *));
struct node *merge(struct node *head_one, struct node *head_two,int (*cmp)(void *,void *));

int compare_lists(void* first, void* second);
int compare_ints(void* first, void* second);

int is_subset(struct node *l_1, struct node *l_2);



#endif /*LINKED_LIST_*/
