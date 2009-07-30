#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmockery.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "apriori.h"
#include "linked_list.h"

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

void test_parser(void **state) 
{
	struct node *list = parser("test.dat",3,FALSE);
	free_list_of_lists(&list);
	
}

void test_get_token_list(void **state)
{
	// Test file w/ 1 2 3 4 on same line
	
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);

//	assert_int_equal(*((int *)check->data),1);
//	check = check->next;
//	assert_int_equal(*((int *)check->data),2);
//	check = check->next;
//	assert_int_equal(*((int *)check->data),3);
//	check = check->next;
//	assert_int_equal(*((int *)check->data),4);
//	check = check->next;
//	assert_true(check == NULL);
//	
	
	free_list(&check);
	fclose(f);

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
	assert_int_equal(get_len_list(check),5);
	free_list(&check);
		
}

void test_get_windows(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	struct node* list_of_parses = get_windows(check,3);
	//print_nodes(list_of_parses);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,0)),0))),1);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,0)),1))),2);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,0)),2))),3);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,0)),3))),-3);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,1)),-1))),-3);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,1)),0))),2);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,1)),1))),3);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,1)),2))),4);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,1)),3))),-3);
	assert_int_equal(*((int *)(get_data((struct node *)(get_data(list_of_parses,2)),2))),-3);
	assert_int_equal(*((int *)(get_data(list_of_parses,2))),-3);
	free_list(&check);
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
	//assert_true(*((int *)get_data(check,4))==-3);
	fclose(f);
	free_list(&check);
}

void test_merge_sort(void **state)
{
	struct node *test = NULL;
	struct node *test_2 = NULL;
	int * temp = malloc(sizeof(int));
	*temp = 1;
	add(&test,(void *) temp);
	//test mergesort on one item (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp);
	//test mergesort on three items (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),4);
	temp = malloc(sizeof(int));
	*temp = 55;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 3;
	add(&test,(void *)temp);
	//mergesort on 5 items (ints)
	mergesort(test,&compare_ints);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),3);
	assert_int_equal(*((int *)get_data(test,3)),4);
	assert_int_equal(*((int *)get_data(test,4)),55);
	//test mergesort on lists
	add(&test_2,(void *)test);
	test = NULL;
	temp = malloc(sizeof(int));
	*temp = 1;
	add(&test,(void *) temp);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 5;
	add(&test,(void *)temp);
	add(&test_2,(void *)test);
	test_2 = mergesort(test_2,&compare_lists);
	
	print_lists(test_2);
	
	
	
	
	
}
	

void test_free_list(void **state)
{
	struct node *test = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp);
	free_list(&test);
//	temp = malloc(sizeof(int));
//	*temp = 2;
//	add(&test,(void *)temp);
//	assert_int_equal(*((int *)get_data(test,0)),4);
//	assert_int_equal(*((int *)get_data(test,1)),2);
//	free_list(&test);
//	assert_true(test == NULL);
//	
	
}

void test_free_list_of_lists(void **state)
{
	struct node *test = NULL;
	struct node *test_2 = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp);
	
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp);
	
	assert_int_equal(*((int *)get_data(test,0)),4);
	assert_int_equal(*((int *)get_data(test,1)),2);
	
	add(&test_2, (void *)test);
	
	free_list_of_lists(&test_2);
	//free_list(&test);
//	temp = NULL;
//	temp = malloc(sizeof(int));
//	*temp = 3;
//	add(&test,(void *)temp);
//	temp = malloc(sizeof(int));
//	*temp = 4;
//	add(&test,(void *)temp);
//	assert_int_equal(*((int *)get_data(test,0)),3);
//	assert_int_equal(*((int *)get_data(test,1)),4);
//	add(&test_2, (void *)test);

	
	
}

void test_compare_lists(void **state)
{
	struct node *test_1 = NULL;
	struct node *test_2 = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_1,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test_1,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 1;
	add(&test_2,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_2,(void *)temp);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),1);
	free_list(&test_2);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_2,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 5;
	add(&test_2,(void *)temp);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),-1);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_1),0);
	assert_int_equal(compare_lists((void *)test_2,(void *)test_2),0);
	free_list(&test_2);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test_2,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test_2,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 3;
	add(&test_2,(void *)temp);
	assert_int_equal(compare_lists((void *)test_1,(void *)test_2),-1);
}


int main(int argc, char* argv[]) 
{
	UnitTest tests[] = 
	{
		unit_test(test_free_list),
//		unit_test(test_parser),
//		unit_test(test_read_file),
//		unit_test(test_get_token_list),
//		unit_test(test_get_len_list),
//		unit_test(test_get_windows),
//		unit_test(test_get_data),
//		unit_test(test_merge_sort),
//		
//		unit_test(test_free_list_of_lists),
//		unit_test(test_compare_lists)
		
	};
	return run_tests(tests);
}