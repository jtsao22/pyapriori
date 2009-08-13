#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     /* defines uint32_t etc */
#include "hash_tree.h"

#define hashsize(n) ((uint32_t)1<<(n))
#define hashmask(n) (hashsize(n)-1)
#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))



struct hash_map
{
	/* array of pointer to nodes (linked lists) */ 
	struct node **hash_table;
	
	/* number of buckets */ 
	int size;
	
	/* number of used buckets */  
	int count;	
	
	/* number of used buckets/number of buckets */ 
	double density;
};

void initialize_hash_map(struct hash_map **hm);
void free_hash_map(struct hash_map **hm);
uint32_t hash(uint32_t num);
uint32_t hashword(const uint32_t *k,size_t length,uint32_t initval);
void insert_in_hash(struct hash_map *hm, uint32_t num,struct hash_tree_node *ht_node);
struct node *get_data_from_hash(struct hash_map *hm, uint32_t num);

#endif /*HASH_MAP_H*/
