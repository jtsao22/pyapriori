#ifndef HASH_TREE_H
#define HASH_TREE_H

#include<stdio.h>
#include <stdint.h>
#include "linked_list.h"

enum state {leaf,interior};


/****************************************************************************/
/*							Hash Tree Node 									*/
/****************************************************************************/ 

struct hash_tree_node
{
	unsigned int key;
	unsigned char depth;
	unsigned char count;
	void *parent;
	
	enum state node_type;
	/* if state is leaf */ 
	struct node *item_lists;
	
	/* if state is interior */ 
	struct hash_map *children;
	
};

void init_hash_tree_node(struct hash_tree_node *ht_node, struct hash_tree_node *parent, 
		enum state node_type, unsigned char depth);

void add_child(struct hash_tree_node *ht_node, uint32_t depth,
		struct hash_tree_node *child);

int add_transaction(struct hash_tree_node *ht_node, void *data);

int get_num_lists(struct hash_tree_node *ht_node);

void make_interior(struct hash_tree_node *ht_node);

int expand_node(struct hash_tree_node *ht_node, int threshold);

void free_hash_tree_node(struct hash_tree_node **ht_node);

void free_hash_tree_int_node(void *ht_node);


/****************************************************************************/
/*								Hash Tree 									*/
/****************************************************************************/ 

struct hash_tree
{
	unsigned char threshold;
	struct hash_tree_node *root;
	struct node *cand_list_final;
	struct node *l_k_set;
};

void init_hash_tree(struct hash_tree **ht, unsigned char threshold);

void reinit_hash_tree(struct hash_tree *ht);

void add_trans(struct hash_tree **ht,struct node *data);

void add_trans_recursive(struct hash_tree *ht,struct hash_tree_node *ht_node, 
		struct node *trans, uint32_t depth);

void print_all_tree(struct hash_tree_node *ht_node);

void subset(struct hash_tree *ht,struct node **trans);

void subset_recursive(struct hash_tree *ht, struct hash_tree_node *ht_node,
		uint32_t num_to_hash, struct node *trans);

void check_minsup(struct hash_tree *ht, struct hash_tree_node *ht_node,
		double minsup);

void free_hash_tree(struct hash_tree *ht);

#endif /*HASH_TREE_H*/
