//#include <stdarg.h>
//#include <stddef.h>
//#include <setjmp.h>
//#include <cmockery.h>
//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//#include <stdint.h>     /* defines uint32_t etc */
//#include "apriori.h"
//#include "linked_list.h"
//#include "hash_map.h"
//#include "hash_tree.h"
//
//#ifdef CMOCKERY
//extern void* _test_malloc(const size_t size, const char* file, const int line);
//extern void _test_free(void* const ptr, const char* file, const int line);
//#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
//#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
//#endif 
//
//
//
//void print_nodes(struct node *n)
//{
//	//print the node data in the linked list
//	uint32_t k;
//	
//	while(n != NULL)
//	{
//		k = *((uint32_t *)n->data);
//		printf("%i ",*((uint32_t *)n->data));
//		n = n->next;
//	}
//		
//}
//
////void print_lists(struct node *n)
////{
////	while(n != NULL)
////	{
////		printf("List: ");
////		print_nodes((struct node *)(n->data));
////		printf("\n");
////		n = n->next;	
////	}
////}
//
//void test_apriori(void **state)
//{
//	struct node *freq_list = apriori(.09,4,"test5.dat", "output.dat",FALSE,3);	
//	struct node *iter = freq_list;
//	struct node *next;
//	
//	printf("all_Lk: \n");
//	while(iter != NULL)
//	{
//		next = iter->next;
//		print_lists((struct node *)iter->data);
//		
//		free_list_of_lists((struct node **)&iter->data);
//		free(iter);
//		
//		iter = next;
//	}
//	
//}
//
//void test_one_item_sets(void **state)
//{
//	/* test file with 1 2 3 4 5 2 3 4 5 6 1 2 3 4 5 2 3 4 5 6 7 8 9 1 2 3 */ 
//	struct node *trans_list = parser("test3.dat",3,FALSE);
//	double minsup = .03;
//	struct node *final_list = one_item_sets(trans_list, &minsup);
//	assert_true(minsup == 0.72);
//	struct node *iter = final_list;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(final_list,0)),0))),1);
//	assert_int_equal(iter->count,7);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(final_list,1)),0))),2);
//	assert_int_equal(iter->count,13);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),3);
//	assert_int_equal(iter->count,13);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),4);
//	assert_int_equal(iter->count,12);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),5);
//	assert_int_equal(iter->count,12);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),6);
//	assert_int_equal(iter->count,6);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),7);
//	assert_int_equal(iter->count,3);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),8);
//	assert_int_equal(iter->count,3);
//	iter = iter->next;
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(iter,0)),0))),9);
//	assert_int_equal(iter->count,3);
//	iter = iter->next;
//	assert_true(iter==NULL);
//
//	free_list_of_lists(&final_list);
//	free_list_of_lists(&trans_list);
//	
//}
//
//
//
//void test_parser(void **state) 
//{
//	struct node *list = parser("test.dat",3,FALSE);
//	assert_true(list != NULL);
//	print_lists(list);
//	free_list_of_lists(&list);
//	/* test empty file */ 
//	struct node *list1 = parser("test2.dat",3,FALSE);
//	assert_true(list1 == NULL);
//	free_list_of_lists(&list1);
//	
//	/* test test3.dat */
//	struct node *list3 = parser("test3.dat",3,FALSE);
//	print_lists(list3);
//	free_list_of_lists(&list3);
//	
//}
//
//void test_get_token_list(void **state)
//{
//	// Test file w/ 1 2 3 4 on same line
//	FILE *g;
//	FILE *f = read_file("test.dat");
//	
//	struct node* check = get_token_list(f);
//	assert_true(*((int *)get_data(check,0))==1);
//	assert_true(*((int *)get_data(check,1))==2);
//	assert_true(*((int *)get_data(check,2))==3);
//	assert_true(*((int *)get_data(check,3))==4);
//
//	free_list(&check,&free_ints);
//	fclose(f);
//	
//	g = read_file("test2.dat");
//	check = get_token_list(g);
//	assert_true(check==NULL);
//	fclose(g);
//
//}
//
//void test_read_file(void **state) 
//{
//	FILE *f;
//	assert_true((f=read_file("random.dat")) == NULL);	
//	assert_true((f=read_file("test.dat")) !=NULL);
//	fclose(f);
//}
//
//void test_get_len_list(void **state)
//{
//	FILE *f = read_file("test.dat");
//	struct node* check = get_token_list(f);
//	assert_int_equal(get_len_list(check),4);
//	free_list(&check,&free_ints);
//	f = read_file("test1.dat");
//	check = get_token_list(f);
//	assert_int_equal(get_len_list(check),6);
//	free_list(&check,&free_ints);
//		
//}
//
//void test_get_windows(void **state)
//{
//	FILE *f = read_file("test.dat");
//	struct node* check = get_token_list(f);
//	struct node* list_of_parses = get_windows(check,3);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,0)),0))),1);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,0)),1))),2);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,0)),2))),3);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,1)),0))),2);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,1)),1))),3);
//	assert_int_equal(*((int *)(get_data((struct node *)(
//			get_data(list_of_parses,1)),2))),4);
//	free_list(&check,&free_ints);
//
//	free_list_of_lists(&list_of_parses);
//	fclose(f);
//	
//	f = read_file("test2.dat");
//	check = get_token_list(f);
//	assert_true(check==NULL);
//	list_of_parses = get_windows(check,3);
//	assert_true(list_of_parses==NULL);
//	fclose(f);
//		
//	FILE *h = read_file("test1.dat");
//	check = get_token_list(h);
//	list_of_parses = get_windows(check,3);
//	free_list(&check,&free_ints);
//	free_list_of_lists(&list_of_parses);
//	fclose(h);
//	
//}
//
//void test_check_inside(void **state)
//{
//	struct node *parse_list = NULL;
//	int *temp = malloc(sizeof(int));
//	*temp = 3;
//	add(&parse_list,(void *)temp,1);
//	
//	assert_true(check_inside(3,parse_list));
//	assert_false(check_inside(4,parse_list));
//	free_list(&parse_list,&free_ints);
//}
//
//void test_get_dynamic_windows(void **state)
//{
//	FILE *f = read_file("test.dat");
//	struct node* check = get_token_list(f);
//	struct node* list_of_parses = get_dynamic_windows(check);
//	struct node *temp = (struct node *)(get_data(list_of_parses,0));
//	assert_int_equal(*((int *)(get_data(temp,0))),1);
//	assert_int_equal(*((int *)(get_data(temp,1))),2);
//	assert_int_equal(*((int *)(get_data(temp,2))),3);
//	assert_int_equal(*((int *)(get_data(temp,3))),4);
//	temp = (struct node *)(get_data(list_of_parses,1));
//	assert_int_equal(*((int *)(get_data(temp,0))),2);
//	assert_int_equal(*((int *)(get_data(temp,1))),3);
//	assert_int_equal(*((int *)(get_data(temp,2))),4);
//	temp = (struct node *)(get_data(list_of_parses,2));
//	assert_int_equal(*((int *)(get_data(temp,0))),3);
//	assert_int_equal(*((int *)(get_data(temp,1))),4);
//	temp = (struct node *)(get_data(list_of_parses,3));
//	assert_int_equal(*((int *)(get_data(temp,0))),4);
//	free_list(&check,&free_ints);
//	free_list_of_lists(&list_of_parses);
//	fclose(f);
//}
//
//void test_get_data(void **state)
//{
//	FILE *f = read_file("test.dat");
//	struct node* check = get_token_list(f);
//	assert_true(*((int *)get_data(check,0))==1);
//	assert_true(*((int *)get_data(check,1))==2);
//	assert_true(*((int *)get_data(check,2))==3);
//	assert_true(*((int *)get_data(check,3))==4);
//	fclose(f);
//	free_list(&check,&free_ints);
//}
//
//void test_merge_sort(void **state)
//{
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	int * temp = malloc(sizeof(int));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	//test mergesort on one item (ints)
//	test = mergesort(test,&compare_ints);
//	assert_int_equal(*((int *)get_data(test,0)),1);
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	//test mergesort on three items (ints)
//	test = mergesort(test,&compare_ints);
//	assert_int_equal(*((int *)get_data(test,0)),1);
//	assert_int_equal(*((int *)get_data(test,1)),2);
//	assert_int_equal(*((int *)get_data(test,2)),4);
//	temp = malloc(sizeof(int));
//	*temp = 55;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	//mergesort on 5 items (ints)
//	test =mergesort(test,&compare_ints);
//	assert_int_equal(*((int *)get_data(test,0)),1);
//	assert_int_equal(*((int *)get_data(test,1)),2);
//	assert_int_equal(*((int *)get_data(test,2)),3);
//	assert_int_equal(*((int *)get_data(test,3)),4);
//	assert_int_equal(*((int *)get_data(test,4)),55);
//	//test mergesort on lists
//	add(&test_2,(void *)test,1);
//	test = NULL;
//	temp = malloc(sizeof(int));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 5;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	test_2 = mergesort(test_2,&compare_lists);
//	
//	free_list_of_lists(&test_2);
//
//	
//}
//	
//
//void test_free_list(void **state)
//{
//	struct node *test = NULL;
//	int *temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	assert_int_equal(*((int *)get_data(test,0)),4);
//	assert_int_equal(*((int *)get_data(test,1)),2);
//	free_list(&test,&free_ints);
//
//}
//
//void test_free_list_of_lists(void **state)
//{
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	int *temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	
//	assert_int_equal(*((int *)get_data(test,0)),4);
//	assert_int_equal(*((int *)get_data(test,1)),2);
//
//	add(&test_2, (void *)test,1);
//	temp = NULL;
//	temp = malloc(sizeof(int));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	free_list_of_lists(&test_2);	
//	
//}
//
//void test_compare_lists(void **state)
//{
//	struct node *test_1 = NULL;
//	struct node *test_2 = NULL;
//	int *temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test_1,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test_1,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 1;
//	add(&test_2,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test_2,(void *)temp,1);
//	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),1);
//	assert_int_equal(compare_lists((void *)test_2,(void *)test_1),-1);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test_2,(void *)temp,1);
//	temp = malloc(sizeof(int));
//	*temp = 5;
//	add(&test_2,(void *)temp,1);
//	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),1);
//	assert_int_equal(compare_lists((void *)test_1,(void *)test_1),0);
//	assert_int_equal(compare_lists((void *)test_2,(void *)test_2),0);
//	free_list(&test_1,&free_ints);
//	free_list(&test_2,&free_ints);
//
//}
//
//void test_hash(void **state)
//{
//	uint32_t a;
//	uint32_t b;
//	a = 22;
//	b = hash(a);
////	assert_true(b == 1970502188);
//	
//}
//
//void test_insert_in_hash(void **state)
//{
//	int *temp = NULL;
//	struct hash_tree_node *h_ptr = NULL;
//	struct node *n_ptr = NULL;
//	struct node *n_ptr_2 = NULL;
//	struct node *n_ptr_3 = NULL;
//	struct hash_tree_node *ht_node = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_2 = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_3 = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_4 = malloc(sizeof(struct hash_tree_node));
//	init_hash_tree_node(ht_node, NULL,interior,1);
//	
//	initialize_hash_map(&ht_node->children);
//	init_hash_tree_node(ht_node_4,ht_node,leaf,1);
//	init_hash_tree_node(ht_node_3,ht_node,leaf,1);
//	init_hash_tree_node(ht_node_2, ht_node,leaf,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 3;	
//	add(&n_ptr,(void *)temp,1);
//	add(&ht_node_2->item_lists,(void *)n_ptr,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&n_ptr_2,(void *)temp,1);
//	add(&ht_node_3->item_lists,(void *)n_ptr_2,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 5;
//	add(&n_ptr_3,(void *)temp,1);
//	add(&ht_node_4->item_lists,(void *)n_ptr_3,1);
//
//	/* test two separate inserts */
//	insert_in_hash(ht_node->children,2,(void *)ht_node_2);
//	insert_in_hash(ht_node->children,3,(void *)ht_node_3);
//
//	h_ptr = (struct hash_tree_node *)(ht_node->children->hash_table[90]->data);
//	assert_int_equal(*((int *)((struct node *)(h_ptr->item_lists->data))->data),3);
//	h_ptr = (struct hash_tree_node *)(ht_node->children->hash_table[93]->data);
//	assert_int_equal(*((int *)((struct node *)(h_ptr->item_lists->data))->data),4);
//	
//	/* test inserts into same bucket */ 
//	insert_in_hash(ht_node->children,2,(void *)ht_node_4);
//	h_ptr = (struct hash_tree_node *)(ht_node->children->hash_table[90]->data);
//	assert_int_equal(*((int *)((struct node *)(h_ptr->item_lists->
//			data))->data),3);
//	h_ptr = (struct hash_tree_node *)(ht_node->children->hash_table[90]
//			->next->data);
//	assert_int_equal(*((int *)((struct node *)(h_ptr->item_lists->data))->data),5);
//
//	free_hash_tree_node(&ht_node);
//
//}
//
//void test_get_data_from_hash(void **state)
//{
//	int *temp = NULL;
//	struct hash_tree_node *ht_node = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_2 = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_3 = malloc(sizeof(struct hash_tree_node));
//	struct hash_tree_node *ht_node_4 = malloc(sizeof(struct hash_tree_node));
//	struct node *n_ptr = NULL;
//	struct node *n_ptr_2 = NULL;
//	struct node *n_ptr_3 = NULL;
//	
//	init_hash_tree_node(ht_node, NULL,interior,1);
//	
//	initialize_hash_map(&ht_node->children);
//	init_hash_tree_node(ht_node_4,ht_node,leaf,1);
//	init_hash_tree_node(ht_node_3,ht_node,leaf,1);
//	init_hash_tree_node(ht_node_2, ht_node,leaf,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 3;	
//	add(&n_ptr,(void *)temp,1);
//	add(&ht_node_2->item_lists,(void *)n_ptr,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&n_ptr_2,(void *)temp,1);
//	add(&ht_node_3->item_lists,(void *)n_ptr_2,1);
//	
//	temp = malloc(sizeof(int));
//	*temp = 5;
//	add(&n_ptr_3,(void *)temp,1);
//	add(&ht_node_4->item_lists,(void *)n_ptr_3,1);
//
//	/* test two separate inserts */
//	insert_in_hash(ht_node->children,2,(void *)ht_node_2);
//	insert_in_hash(ht_node->children,3,(void *)ht_node_3);
//
//	assert_int_equal(*((int *)((struct node *)((struct hash_tree_node *)
//			get_data_from_hash(ht_node->children,2)->data)->item_lists->data)->data),3);
//	assert_int_equal(*((int *)((struct node *)((struct hash_tree_node *)
//			get_data_from_hash(ht_node->children,3)->data)->item_lists->data)->data),4);
//	
//	/* test inserts into same bucket */ 
//	insert_in_hash(ht_node->children,2,(void *)ht_node_4);
//
//	assert_int_equal(*((int *)((struct node *)((struct hash_tree_node *)
//			get_data_from_hash(ht_node->children,2)->data)->item_lists
//			->data)->data),3);
//	assert_int_equal(*((int *)((struct node *)((struct hash_tree_node *)
//			get_data_from_hash(ht_node->children,2)->next->data)->item_lists
//			->data)->data),5);
//	free_hash_tree_node(&ht_node);
//
//	
//}
//
//void test_add_trans(void **state)
//{
//	struct hash_tree *ht = NULL;
//	init_hash_tree(&ht,2);
//	
//	struct node *int_node = NULL;
//	struct node *int_node_2 = NULL;	
//	uint32_t *temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&int_node,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&int_node,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&int_node,(void *)temp,1);
//	add_trans(&ht,(void *)int_node);
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	add_trans(&ht,(void *)int_node_2);	
//	
//	int_node_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	add_trans(&ht,(void *)int_node_2);
//	
//	int_node_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	add_trans(&ht,(void *)int_node_2);	
//	
//	int_node_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	add_trans(&ht,(void *)int_node_2);
//	
//	print_all_tree(ht->root);	
//	
//	free_hash_tree(ht);
//	
//}
//
//void test_subset(void **state)
//{
//	struct hash_tree *ht = NULL;
//	init_hash_tree(&ht,1);
//	
//	struct node *int_node = NULL;
//	struct node *int_node_2 = NULL;	
//	struct node *trans = NULL;
//	uint32_t *temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&int_node,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&int_node,(void *)temp,1);
//
//	add_trans(&ht,(void *)int_node);
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	
//	add_trans(&ht,(void *)int_node_2);	
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&trans,(void *)temp,1);
//	
//	subset(ht,&trans);
//	print_lists(ht->cand_list_final);
//	free_list(&trans,&free_ints);
//	free_hash_tree(ht);
//}
//
//
//void test_is_subset(void **state)
//{
//	struct node *int_node_2 = NULL;	
//	struct node *trans = NULL;
//	struct node *int_node = NULL;
//	struct node *empty = NULL;
//	uint32_t *temp = NULL;
//	
//	
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&int_node_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&int_node_2,(void *)temp,1);
//	
//	int_node_2 = mergesort(int_node_2,&compare_ints);
//	
//	/* check against empty lists */ 
//	assert_false(is_subset(int_node_2,empty));
//	assert_false(is_subset(empty,int_node_2));
//	assert_false(is_subset(empty,empty));
//	
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&trans,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&trans,(void *)temp,1);
//	
//	trans = mergesort(trans,&compare_ints);
//
//	
//	assert_true(is_subset(trans,int_node_2));
//
//	assert_false(is_subset(int_node_2,trans));
//
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&int_node,(void *)temp,1);
//	
//	assert_true(is_subset(trans,int_node));
//	
//	/* check if trans is a subset of trans */ 
//	assert_true(is_subset(trans,trans));
//	
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&int_node,(void *)temp,1);
//	
//	int_node = mergesort(int_node,&compare_ints);
//	
//	assert_true(is_subset(trans,int_node));
//
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&int_node,(void *)temp,1);
//	int_node = mergesort(int_node,&compare_ints);
//	
//	assert_false(is_subset(trans,int_node));
//	assert_false(is_subset(int_node,trans));	
//
//	free_list(&int_node_2,&free_ints);
//	free_list(&int_node,&free_ints);
//	free_list(&trans,&free_ints);
//
//	
//}
//
//void test_check_minsup(void **state)
//{
//	struct hash_tree *ht = NULL;
//	init_hash_tree(&ht,3);
//	
//	struct hash_tree_node *ht_node = malloc(sizeof(struct hash_tree_node));
//	init_hash_tree_node(ht_node,NULL,leaf,1);
//	
//	struct node *head = NULL;
//	uint32_t *temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&head,(void *)temp,1);
//	add_trans(&ht,head);
//	
//	check_minsup(ht,ht->root,1.1);
//	
//	print_lists(ht->l_k_set);
//	free_list_of_lists(&ht->l_k_set);
//	
//	head = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&head,(void *)temp,1);
//	add_trans(&ht,head);
//	ht->root->item_lists->count = 2;
//	check_minsup(ht,ht->root,2);
//	
//	print_lists(ht->l_k_set);
//	
//	free_hash_tree_node(&ht_node);
//	free_hash_tree(ht);
//}
//
//void test_generate(void **state)
//{
//	struct hash_tree *ht = NULL;
//	struct hash_tree *ht_2 = NULL;
//	init_hash_tree(&ht_2,3);
//	init_hash_tree(&ht,3);
//	
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	struct node *cand_list_final = NULL;
//	uint32_t *temp = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	print_lists(test_2);
//	
//	cand_list_final = generate(&test_2,1,ht);
//	
//	print_all_tree(ht->root);
//	
//	/* test what should become an empty list */ 
//	printf("Cand_list_final: \n");
//	print_lists(cand_list_final);
//	
//	free_hash_tree(ht);
//	free_list_of_lists(&cand_list_final);
//	free_list_of_lists(&test_2);
//
//	test_2 = NULL;
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,0);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *)temp,0);
//	add(&test_2,(void *)test,0);
//	
//	
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,0);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&test,(void *)temp,0);
//	add(&test_2,(void *)test,0);
//	
//	test = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *) temp,0);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&test,(void *)temp,0);
//	add(&test_2,(void *)test,0);
//	
//	print_lists(test_2);
//	
//	cand_list_final = generate(&test_2,1,ht_2);
//	
//	print_all_tree(ht_2->root);
//	
//	printf("cand_trans_list: \n");
//	print_lists(cand_list_final);
//	
//	free_hash_tree(ht_2);
//	free_list_of_lists(&cand_list_final);
//	free_list_of_lists(&test_2);
//}
//
//void test_same_list(void **state)
//{
//	struct node *test;
//	struct node *test_2;
//	
//	test = NULL;
//	uint32_t *temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	
//	test_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&test_2,(void *) temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&test_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&test_2,(void *)temp,1);
//	
//	assert_int_equal(same_list(test,test_2),FALSE);
//	assert_int_equal(same_list(test,test),TRUE);
//	assert_int_equal(same_list(test_2,test_2),TRUE);
//	
//	free_list(&test,&free_ints);
//	free_list(&test_2,&free_ints);
//}
//
//void test_get_subsets_of(void **state)
//{
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	struct node *test_3 = NULL;
//	
//	int32_t *temp = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//
//	test_2 = get_subsets_of(test);
//	
//	print_lists(test_2);
//	
//	temp = malloc(sizeof(int32_t));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	
//	test_3 = get_subsets_of(test);
//	
//	print_lists(test_3);
//	
//	free_list_of_lists(&test_3);
//	free_list_of_lists(&test_2);
//	free_list(&test,&free_ints);
//}
//
//void test_check_item_last(void **state)
//{
//	struct node *head = NULL;
//	uint32_t *temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&head,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&head,(void *)temp,1);
//	
//	struct node *head_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 6;
//	add(&head_2,(void *)temp,1);
//	
//	assert_true(check_item_last(head,head_2)== NULL);
//	
//	
//	
//	free_list(&head_2,&free_ints);
//	head_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 3;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&head_2,(void *)temp,1);
//	
//	struct node *ll = check_item_last(head,head_2);
//	assert_int_equal(*((int *)ll->data),1);
//	assert_int_equal(*((int *)ll->next->data),2);
//	assert_int_equal(*((int *)ll->next->next->data),3);
//	assert_int_equal(*((int *)ll->next->next->next->data),4);
//	assert_int_equal(*((int *)ll->next->next->next->next->data),5);
//	assert_true(ll->next->next->next->next->next == NULL);
//	
//	free_list(&head_2,&free_ints);
//	free_list(&ll,&free_ints);
//	head_2 = NULL;
//	temp = malloc(sizeof(uint32_t));
//	*temp = 1;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 2;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 4;
//	add(&head_2,(void *)temp,1);
//	temp = malloc(sizeof(uint32_t));
//	*temp = 5;
//	add(&head_2,(void *)temp,1);
//	
//	assert_true(check_item_last(head,head_2)==NULL);
//	
//	free_list(&head,&free_ints);
//	free_list(&head_2,&free_ints);
//}
//
//void test_is_inside(void **state)
//{
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	int32_t *temp = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	assert_int_equal(is_inside(test_2,test),TRUE);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	
//	assert_int_equal(is_inside(test_2,test),FALSE);
//	
//	free_list(&test,&free_ints);
//	
//		test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	
//	assert_int_equal(is_inside(test_2,test),FALSE);
//	
//	free_list(&test,&free_ints);
//	free_list_of_lists(&test_2);
//}
//
//void test_remove_list(void **state)
//{
//	struct node *test = NULL;
//	struct node *test_2 = NULL;
//	
//	int32_t *temp = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	
//	
//	/* test deletion from end/mid */ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("Removed: \n");
//	print_lists(test_2);
//	
//	free_list(&test,&free_ints);
//	
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	add(&test_2,(void *)test,1);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 3;
//	add(&test,(void *)temp,1);
//	
//	/* test deletion from beginning */ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("Removed: \n");
//	print_lists(test_2);
//	
//	free_list(&test,&free_ints);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 4;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 5;
//	add(&test,(void *)temp,1);
//	
//	/* test list thats not in list of lists*/ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("Removed: \n");
//	print_lists(test_2);
//	
//	free_list(&test,&free_ints);
//	
//	/* test removing an empty list */ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("After Removal: \n");
//	print_lists(test_2);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	
//	/* test list when none is left after removal */ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("After Removal: \n");
//	print_lists(test_2);
//	
//	free_list(&test,&free_ints);
//	
//	test = NULL;
//	temp = malloc(sizeof(int32_t));
//	*temp = 1;
//	add(&test,(void *) temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 2;
//	add(&test,(void *)temp,1);
//	temp = malloc(sizeof(int32_t));
//	*temp = 8;
//	add(&test,(void *)temp,1);
//	
//	/* test removing from an empty list */ 
//	printf("Original: \n");
//	print_lists(test_2);
//	remove_list(&test_2,test);
//	printf("After Removal: \n");
//	print_lists(test_2);
//	
//	free_list(&test,&free_ints);
//	
//
//	
//	free_list_of_lists(&test_2);
//
//}
//
//
//int main(int argc, char* argv[]) 
//{
//	UnitTest tests[] = 
//	{
//		unit_test(test_apriori),
//		unit_test(test_add_trans),
//		unit_test(test_generate),
//		unit_test(test_free_list),
//		unit_test(test_free_list_of_lists),
//		unit_test(test_parser),
//		unit_test(test_read_file),
//		unit_test(test_get_token_list),
//		unit_test(test_get_len_list),
//		unit_test(test_get_windows),
//		unit_test(test_get_data),
//		unit_test(test_merge_sort),
//		unit_test(test_compare_lists),
//		unit_test(test_get_dynamic_windows),
//		unit_test(test_insert_in_hash),
//		unit_test(test_one_item_sets),
//		unit_test(test_check_inside),
//		unit_test(test_hash),
//		unit_test(test_get_data_from_hash),
//		unit_test(test_subset),
//		unit_test(test_is_subset),
//		unit_test(test_check_minsup),
//		unit_test(test_same_list),
//		unit_test(test_check_item_last),
//		unit_test(test_get_subsets_of),
//		unit_test(test_is_inside),
//		unit_test(test_remove_list)
//		
//	};
//	return run_tests(tests);
//}