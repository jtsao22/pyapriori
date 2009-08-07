#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmockery.h>
#include "hash_map.h"
#include "linked_list.h"
#include "hash_tree.h"

extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}


#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

uint32_t hashword(
const uint32_t *k,                   /* the key, an array of uint32_t values */
size_t          length,               /* the length of the key, in uint32_ts */
uint32_t        initval)         /* the previous hash, or an arbitrary value */
{
  uint32_t a,b,c;

  /* Set up the internal state */
  a = b = c = 0xdeadbeef + (((uint32_t)length)<<2) + initval;

  /*------------------------------------------------- handle most of the key */
  while (length > 3)
  {
    a += k[0];
    b += k[1];
    c += k[2];
    mix(a,b,c);
    length -= 3;
    k += 3;
  }

  /*------------------------------------------- handle the last 3 uint32_t's */
  switch(length)                     /* all the case statements fall through */
  {
  case 3 : c+=k[2];
  case 2 : b+=k[1];
  case 1 : a+=k[0];
    final(a,b,c);
  case 0:     /* case 0: nothing left to add */
    break;
  }
  /*------------------------------------------------------ report the result */
  return c;
}

int hash(uint32_t num)
{
	return hashword(&num,1,22)%100; /* NOTE: 22 is an arbitrary value */ 
}

void initialize_hash_map(struct hash_map *hm)
{
	int k;
	hm->size = 100;
	hm->hash_table = malloc(hm->size*sizeof(struct node));
	for(k = 0; k < hm->size; k++)
		hm->hash_table[k] = NULL;
	hm->count = 0;
}

void free_hash_map(struct hash_map *hm)
{
	int k;
	for(k= 0; k < hm->size; k++)
		free_list(&hm->hash_table[k]);
	free(hm->hash_table);
	free(hm);
}

void insert_in_hash(struct hash_map *hm, uint32_t num,void *data)
{
	uint32_t converted = hash(num)%100;
	printf("Converted num: %i\n",converted);
	struct hash_tree_node *ht_node = malloc(sizeof(struct hash_tree_node));
	ht_node->key = num;
	ht_node->children = data;
	ht_node->count = 1;
	if(!add(&hm->hash_table[converted],(void *) ht_node,1))
	{
		exit(0);
	}
	hm->count++;

}

void *get_data_from_hash(struct hash_map *hm, uint32_t num)
{
	uint32_t converted = hash(num)%100;
	return hm->hash_table[converted];
}

