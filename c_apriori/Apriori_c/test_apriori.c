#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmockery.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "apriori.h"
#include "linked_list.h"
#include "hash_map.h"
#include "hash_tree.h"


extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)




void print_nodes(struct node *n)
{
	//print the node data in the linked list
	while(n != NULL)
	{
		printf("%i ",*((int *)n->data));
		n = n->next;
	}
		
}

void print_lists(struct node *n)
{
	while(n != NULL)
	{
		printf("List: ");
		print_nodes((struct node *)(n->data));
		printf("\n");
		n = n->next;	
	}
}

void test_apriori(void **state)
{
	struct node *freq_list = apriori(.03,3,"test3.dat", "output.dat",FALSE,3);	
	
	free_list_of_lists(&freq_list);
}

void test_one_item_sets(void **state)
{
	/* test file with 1 2 3 4 5 2 3 4 5 6 1 2 3 4 5 2 3 4 5 6 7 8 9 1 2 3 */ 
	struct node *trans_list = parser("test3.dat",3,FALSE);
	double minsup = .03;
	struct node *final_list = one_item_sets(trans_list, &minsup);
	assert_true(minsup == 0.72);
	struct node *iter = final_list;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(final_list,0)),0))),1);
	assert_int_equal(iter->count,7);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(final_list,1)),0))),2);
	assert_int_equal(iter->count,13);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),3);
	assert_int_equal(iter->count,13);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),4);
	assert_int_equal(iter->count,12);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),5);
	assert_int_equal(iter->count,12);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),6);
	assert_int_equal(iter->count,6);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),7);
	assert_int_equal(iter->count,3);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),8);
	assert_int_equal(iter->count,3);
	iter = iter->next;
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(iter,0)),0))),9);
	assert_int_equal(iter->count,3);
	iter = iter->next;
	assert_true(iter==NULL);

	free_list_of_lists(&final_list);
	
	
}



void test_parser(void **state) 
{
	struct node *list = parser("test.dat",3,FALSE);
	assert_true(list != NULL);
	free_list_of_lists(&list);
	/* test empty file */ 
	struct node *list1 = parser("test2.dat",3,FALSE);
	assert_true(list1 == NULL);
	free_list_of_lists(&list1);
}

void test_get_token_list(void **state)
{
	// Test file w/ 1 2 3 4 on same line
	FILE *g;
	FILE *f = read_file("test.dat");
	
	struct node* check = get_token_list(f);
	assert_true(*((int *)get_data(check,0))==1);
	assert_true(*((int *)get_data(check,1))==2);
	assert_true(*((int *)get_data(check,2))==3);
	assert_true(*((int *)get_data(check,3))==4);
	free_list(&check);
	fclose(f);
	
	g = read_file("test2.dat");
	check = get_token_list(g);
	assert_true(check==NULL);
	fclose(g);

}

void test_read_file(void **state) 
{
	FILE *f;
	assert_true((f=read_file("random.dat")) == NULL);	
	assert_true((f=read_file("test.dat")) !=NULL);
	fclose(f);
}

void test_get_len_list(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	assert_int_equal(get_len_list(check),4);
	free_list(&check);
	f = read_file("test1.dat");
	check = get_token_list(f);
	assert_int_equal(get_len_list(check),6);
	free_list(&check);
		
}

void test_get_windows(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	struct node* list_of_parses = get_windows(check,3);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,0)),0))),1);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,0)),1))),2);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,0)),2))),3);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,1)),0))),2);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,1)),1))),3);
	assert_int_equal(*((int *)(get_data((struct node *)(
			get_data(list_of_parses,1)),2))),4);
	free_list(&check);
	free_list_of_lists(&list_of_parses);
	fclose(f);
	
	f = read_file("test2.dat");
	check = get_token_list(f);
	assert_true(check==NULL);
	list_of_parses = get_windows(check,3);
	assert_true(list_of_parses==NULL);
	fclose(f);
		
	FILE *h = read_file("test1.dat");
	check = get_token_list(h);
	list_of_parses = get_windows(check,3);
	print_lists(list_of_parses);
	print_nodes(check);
	free_list(&check);
	free_list_of_lists(&list_of_parses);
	fclose(h);
	
}

void test_check_inside(void **state)
{
	struct node *parse_list = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 3;
	add(&parse_list,(void *)temp,1);
	
	assert_true(check_inside(3,parse_list));
	assert_false(check_inside(4,parse_list));
	free_list(&parse_list);
}

void test_get_dynamic_windows(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	struct node* list_of_parses = get_dynamic_windows(check);
	struct node *temp = (struct node *)(get_data(list_of_parses,0));
	assert_int_equal(*((int *)(get_data(temp,0))),1);
	assert_int_equal(*((int *)(get_data(temp,1))),2);
	assert_int_equal(*((int *)(get_data(temp,2))),3);
	assert_int_equal(*((int *)(get_data(temp,3))),4);
	temp = (struct node *)(get_data(list_of_parses,1));
	assert_int_equal(*((int *)(get_data(temp,0))),2);
	assert_int_equal(*((int *)(get_data(temp,1))),3);
	assert_int_equal(*((int *)(get_data(temp,2))),4);
	temp = (struct node *)(get_data(list_of_parses,2));
	assert_int_equal(*((int *)(get_data(temp,0))),3);
	assert_int_equal(*((int *)(get_data(temp,1))),4);
	temp = (struct node *)(get_data(list_of_parses,3));
	assert_int_equal(*((int *)(get_data(temp,0))),4);
	free_list(&check);
	free_list_of_lists(&list_of_parses);
	fclose(f);
}

void test_get_data(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	assert_true(*((int *)get_data(check,0))==1);
	assert_true(*((int *)get_data(check,1))==2);
	assert_true(*((int *)get_data(check,2))==3);
	assert_true(*((int *)get_data(check,3))==4);
	fclose(f);
	free_list(&check);
}

void test_merge_sort(void **state)
{
	struct node *test = NULL;
	struct node *test_2 = NULL;
	int * temp = malloc(sizeof(int));
	*temp = 1;
	add(&test,(void *) temp,1);
	//test mergesort on one item (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp,1);
	//test mergesort on three items (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),4);
	temp = malloc(sizeof(int));
	*temp = 55;
	add(&test,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 3;
	add(&test,(void *)temp,1);
	//mergesort on 5 items (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),3);
	assert_int_equal(*((int *)get_data(test,3)),4);
	assert_int_equal(*((int *)get_data(test,4)),55);
	//test mergesort on lists
	add(&test_2,(void *)test,1);
	test = NULL;
	temp = malloc(sizeof(int));
	*temp = 1;
	add(&test,(void *) temp,1);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 5;
	add(&test,(void *)temp,1);
	add(&test_2,(void *)test,1);
	test_2 = mergesort(test_2,&compare_lists);
	
	print_lists(test_2);
	
	free_list_of_lists(&test_2);

	
}
	

void test_free_list(void **state)
{
	struct node *test = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp,1);
	assert_int_equal(*((int *)get_data(test,0)),4);
	assert_int_equal(*((int *)get_data(test,1)),2);
	free_list(&test);
	
	
}

void test_free_list_of_lists(void **state)
{
	struct node *test = NULL;
	struct node *test_2 = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp,1);
	
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp,1);
	
	assert_int_equal(*((int *)get_data(test,0)),4);
	assert_int_equal(*((int *)get_data(test,1)),2);

	add(&test_2, (void *)test,1);
	temp = NULL;
	temp = malloc(sizeof(int));
	*temp = 3;
	add(&test,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp,1);
	free_list_of_lists(&test_2);	
	
}

void test_compare_lists(void **state)
{
	struct node *test_1 = NULL;
	struct node *test_2 = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_1,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test_1,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 1;
	add(&test_2,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_2,(void *)temp,1);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),1);
	assert_int_equal(compare_lists((void *)test_2,(void *)test_1),-1);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_2,(void *)temp,1);
	temp = malloc(sizeof(int));
	*temp = 5;
	add(&test_2,(void *)temp,1);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),1);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_1),0);
	assert_int_equal(compare_lists((void *)test_2,(void *)test_2),0);
	free_list(&test_1);
	free_list(&test_2);
}

void test_hash(void **state)
{
	uint32_t a;
	uint32_t b;
	a = 22;
	b = hash(a);
//	assert_true(b == 1970502188);
	
}

void test_insert_in_hash(void **state)
{

	struct hash_map *hm = malloc(sizeof(struct hash_map));
	initialize_hash_map(hm);
	int *temp = malloc(sizeof(int));
	*temp = 4;
	struct hash_tree_node *ht_node = malloc(sizeof(struct hash_tree_node));
	ht_node->key = 2;
	ht_node->children = (void *)temp;
	ht_node->count = 1;
	
	insert_in_hash(hm,2,(void *)ht_node);
	assert_int_equal(*((int *)((struct hash_tree_node *)(hm->hash_table[2]->data))->children),4);
	free(temp);
}




int main(int argc, char* argv[]) 
{
	UnitTest tests[] = 
	{
		unit_test(test_free_list),
		unit_test(test_free_list_of_lists),
		unit_test(test_parser),
		unit_test(test_read_file),
		unit_test(test_get_token_list),
		unit_test(test_get_len_list),
		unit_test(test_get_windows),
		unit_test(test_get_data),
		unit_test(test_merge_sort),
		unit_test(test_compare_lists),
		unit_test(test_get_dynamic_windows),
		unit_test(test_apriori),
		unit_test(test_one_item_sets),
		unit_test(test_check_inside),
		unit_test(test_hash)
		
	};
	return run_tests(tests);
}