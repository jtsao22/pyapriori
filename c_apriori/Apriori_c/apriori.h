#ifndef APRIORI_H_
#define APRIORI_H_
#include<stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "hash_tree.h"

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif

#include <stdlib.h>

struct Transaction
{
	struct node *item_list;
	int count;
	
};

struct node* apriori(double minsup, int w_size,
		char *i_file, char *o_file, int d_window, unsigned char node_threshold);

struct node *generate(struct node **f_item_list,double minsup,
		struct hash_tree *ht);
		
struct node *get_subsets_of(struct node *item_list);
		
struct node *check_item_last(struct node *trans_1, struct node *trans_2);
		
void print_lists(struct node *n);

struct node* parser(char* file_name,int w_size, int max_d_size);

struct node* one_item_sets(struct node* T, double *minsup);

FILE* read_file(char* file_name);

struct node* get_token_list(FILE* fp);
 
struct node* get_windows(struct node* token_list, int w_size);

int check_inside(int value, struct node *list);

struct node* get_dynamic_windows(struct node* token_list,int max_d_size);

int compare_ints(void* first, void* second);

int compare_lists(void* first, void* second);




#endif /*APRIORI_H_*/
