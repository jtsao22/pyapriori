#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "linked_list.h"
#include "hash_tree.h"
#include "hash_map.h"
#include "apriori.h"

#ifdef CMOCKERY
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif 

/****************************************************************************/
/*							Hash Tree Node 									*/
/****************************************************************************/ 

void init_hash_tree_node(struct hash_tree_node *ht_node, struct hash_tree_node *parent, 
		enum state node_type, unsigned char depth)
{
	ht_node->parent = (void *) parent;
	ht_node->children = NULL;
	ht_node->node_type = node_type;
	ht_node->item_lists = NULL;
	ht_node->depth = depth;
}

void add_child(struct hash_tree_node *ht_node, uint32_t depth,
		struct hash_tree_node *child)
{
	insert_in_hash(ht_node->children,depth,child);
}
	
int add_transaction(struct hash_tree_node *ht_node, void *data)
{
	return add(&ht_node->item_lists,data,0);
}

int get_num_lists(struct hash_tree_node *ht_node)
{
	return get_len_list(ht_node->item_lists);
}

void make_interior(struct hash_tree_node *ht_node)
{
	ht_node->node_type = interior;
//	print_lists(ht_node->item_lists);
//	free_list_of_lists(&ht_node->item_lists);
	ht_node->item_lists = NULL;
}

int expand_node(struct hash_tree_node *ht_node, int threshold)
{
	int k;
	void *data;
	uint32_t key;
	struct node *present;
	struct hash_tree_node *child = NULL;
	if(get_num_lists(ht_node) <= threshold)
		return FALSE;
	struct node *next = NULL;
	struct node *iter = ht_node->item_lists;
	if(ht_node->children == NULL)
	{
		initialize_hash_map(&ht_node->children);
	}
	while(iter != NULL)
	{	
		data = get_data((struct node *)iter->data,ht_node->depth);
		if(data != NULL)
		{
			key = *((uint32_t *)data);
			present = get_data_from_hash(ht_node->children,key);
			if(present != NULL)
			{
				child = present->data;
			}
			else
			{
				child = malloc(sizeof(struct hash_tree_node));
				init_hash_tree_node(child,ht_node,leaf,ht_node->depth + 1);
				add_child(ht_node,key,child);	
			}
			
			add_transaction(child,iter->data);
		}
		next = iter->next;
		free(iter);
		iter = next;
	}
	
	make_interior(ht_node);
	
	for(k = 0; k < ht_node->children->size; k++)
	{
		if(ht_node->children->hash_table[k] != NULL)
		{
			expand_node((struct hash_tree_node *)ht_node
					->children->hash_table[k]->data,threshold);
		}
	}
	return TRUE;
}
	
void free_hash_tree_node(struct hash_tree_node **ht_node) 
{
	if(*ht_node != NULL)
	{
		if((*ht_node)->children != NULL)
		{
			free_hash_map(&(*ht_node)->children);
			
		}
		if((*ht_node)->item_lists != NULL)
		{
			free_list_of_lists(&(*ht_node)->item_lists);
		}
		free(*ht_node);
		*ht_node = NULL;
	}
	
}


void free_hash_tree_int_node(void *ht_node)
{
	free(((struct hash_tree_node *)(ht_node))->children);
	free(ht_node);
}


/****************************************************************************/
/*								Hash Tree 									*/
/****************************************************************************/ 


void init_hash_tree(struct hash_tree **ht, unsigned char threshold)
{
	(*ht) = malloc(sizeof(struct hash_tree));
	(*ht)->threshold = threshold;
	(*ht)->root = NULL;
	(*ht)->cand_list_final = NULL;
	(*ht)->l_k_set = NULL;
}

void reinit_hash_tree(struct hash_tree *ht)
{
	free_hash_tree_node(&ht->root);
	
	
}

void add_trans(struct hash_tree **ht,struct node *trans)
{
	if((*ht)->root == NULL)
	{
		(*ht)->root = malloc(sizeof(struct hash_tree_node));
		init_hash_tree_node((*ht)->root,NULL,leaf,0);
		add_transaction((*ht)->root,trans);
		
	}
	else
	{
		add_trans_recursive((*ht),(*ht)->root,mergesort(trans,&compare_ints),0);
	}
	
}

void add_trans_recursive(struct hash_tree *ht,struct hash_tree_node *ht_node, 
		struct node *trans, uint32_t depth)
{
	/* if its an interior node */ 
	uint32_t num;
	void *data;
	if(ht_node->node_type == interior)
	{
		data = get_data(trans,depth);
		if(data != NULL)
		{
			num = *((uint32_t *)data);
			struct node *ll = get_data_from_hash(ht_node->children,num);
			if(ll != NULL)
			{
				add_trans_recursive(ht, (struct hash_tree_node *)ll->data,trans,depth + 1);
			}
			else
			{
				struct hash_tree_node *temp = malloc(sizeof(struct hash_tree_node));
				init_hash_tree_node(temp,ht_node,leaf,depth+1);
				add_transaction(temp,trans);
				
				add_child(ht_node,num,temp);
				
			}
		}
	}
	/* if its a leaf node */ 
	else
	{	
		add_transaction(ht_node,trans);
		expand_node(ht_node,ht->threshold);
	}
}

void free_hash_tree(struct hash_tree *ht)
{
	if(ht->root != NULL)
	{
		free_hash_tree_node(&ht->root);
	}
	if(ht->cand_list_final != NULL)
		free_list_of_lists(&ht->cand_list_final);
	if(ht->l_k_set != NULL)
		free_list_of_lists(&ht->l_k_set);
	free(ht);
	
}

void print_all_tree(struct hash_tree_node *ht_node)
{
	if(ht_node != NULL)
	{
		if(ht_node->node_type == interior)
		{
			int k;
			
			printf("In an interior node\n");
			for(k = 0; k < ht_node->children->size; k++)	
			{
				if(ht_node->children->hash_table[k] != NULL)
				{
					print_all_tree((struct hash_tree_node *)ht_node->
							children->hash_table[k]->data);	
				}
			}
			printf("Out of interior node\n");
		}
		else
		{
			printf("Leaf node list: \n");
			print_lists(ht_node->item_lists);
		}
	}
}

void subset(struct hash_tree *ht,struct node **trans)
{
	if(ht->root != NULL)
	{
		*trans = mergesort(*trans,&compare_ints);
		subset_recursive(ht,ht->root,0,*trans);
	}
}

void subset_recursive(struct hash_tree *ht, struct hash_tree_node *ht_node,
		uint32_t num_to_hash, struct node *trans)
{	
	struct node *child = NULL;
	struct node *iter = NULL;
	/* if root, hash on every item in trans */ 
	if(ht_node->parent == NULL)
	{
		
		if(ht_node->node_type == interior)
		{
			iter = trans;
			
			while(iter != NULL)
			{
				if((child = get_data_from_hash(ht_node->children,*((uint32_t *)iter->data))))
				{
					subset_recursive(ht,(struct hash_tree_node *)child->data,num_to_hash+1,trans);
				}
				iter = iter->next;
			}
		}
		else
		{
			struct node *iter = ht_node->item_lists;
			while(iter != NULL)
			{
				
				if(is_subset(trans,(struct node *)iter->data))
				{	
					
					iter->count += 1;
					
				}
				
				iter = iter->next;
			}
		}
	}
	else
	{
		if(ht_node->node_type == leaf)
		{
			struct node *iter = ht_node->item_lists;
			while(iter != NULL)
			{
				if(is_subset(trans,(struct node *)iter->data))
				{	
					iter->count += 1;
				}
				
				iter = iter->next;
				
				
			}
		}
		else
		{
			unsigned char index = 0;
			iter = get_node(trans,num_to_hash);
			while(iter != NULL)
			{
				if((child = get_data_from_hash(ht_node->children,*((uint32_t *)iter->data))) != NULL)
				{
					subset_recursive(ht,(struct hash_tree_node *)child->data,index+num_to_hash+1,trans);
				}
				index++;
				iter = iter->next;
			}
		}
	}
}

void check_minsup(struct hash_tree *ht, struct hash_tree_node *ht_node,double minsup)
{
	if(ht_node != NULL)
	{
		if(ht_node->node_type == interior)
		{
			
			int iter;
			for(iter = 0; iter < ht_node->children->size; iter++)
			{
				if(ht_node->children->hash_table[iter] != NULL)
				{
					check_minsup(ht,(struct hash_tree_node *)ht_node->children
							->hash_table[iter]->data,minsup);
				}
			}
		}
		else
		{
			struct node *iter = ht_node->item_lists;
			struct node *copy = NULL;
			while(iter != NULL)
			{
				if(iter->count  >= minsup)
				{
					copy = copy_list(iter->data);
					add(&ht->l_k_set,copy,iter->count);
				}
				iter = iter->next;
			}
		}
		
	}
}



