#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdint.h>     /* defines uint32_t etc */

#define hashsize(n) ((uint32_t)1<<(n))
#define hashmask(n) (hashsize(n)-1)
#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

struct hash_map
{
	void *hash_table[100];
	int count;
};

void initialize_hash_map(struct hash_map hm);
int hash(uint32_t num);
uint32_t hashword(const uint32_t *k,size_t length,uint32_t initval);
void insert_in_hash(struct hash_map *hash_table, uint32_t num,void *data);

#endif /*HASH_MAP_H*/
