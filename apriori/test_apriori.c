#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmockery.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "apriori.h"
#include "linked_list.h"


void test_parser(void **state) 
{
	assert_int_equal(parser("test.dat",3,FALSE), 1);

}

void test_get_token_list(void **state)
{
	// Test file w/ 1 2 3 4 on same line
	
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);

	assert_int_equal(*((int *)check->data),1);
	check = check->next;
	assert_int_equal(*((int *)check->data),2);
	check = check->next;
	assert_int_equal(*((int *)check->data),3);
	check = check->next;
	assert_int_equal(*((int *)check->data),4);
	check = check->next;
	assert_true(check == NULL);
	
	fclose(f);
	free_list(&check);
	
	// test file w/ string input
//	f = read_file("test1.dat");
//	check = get_token_list(f);
//	
//	assert_string_equal(check->data,"hello");
//	check = check->next;
//	assert_string_equal(check->data,"this");
//	check = check->next;
//	assert_string_equal(check->data,"is");
//	check = check->next;
//	assert_string_equal(check->data,"a");
//	check = check->next;
//	assert_string_equal(check->data,"test");
//	check = check->next;
//	assert_true(check == NULL);
}



void test_read_file(void **state) 
{
	assert_true(read_file("random.dat") == NULL);	
	assert_true(read_file("test.dat") !=NULL);
}

void test_get_len_list(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	assert_int_equal(get_len_list(check),4);
	f = read_file("test1.dat");
	check = get_token_list(f);
	assert_int_equal(get_len_list(check),5);
		
}

void test_get_windows(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	struct node* list_of_parses = get_windows(check,3);
	//print_nodes(list_of_parses);
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

	free_list(&check);
}

void test_merge_sort(void **state)
{
	struct node * test = NULL;
	int * temp = malloc(sizeof(int));
	*temp = 1;
	add(&test,(void *) temp);
	//test mergesort on one item
	mergesort(test);
	assert_int_equal(*((int *)get_data(test,0)),1);
	temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp);
	//test mergesort on three items
	mergesort(test);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),4);
	temp = malloc(sizeof(int));
	*temp = 55;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 3;
	add(&test,(void *)temp);
	//mergesort on 5 items
	mergesort(test);
	assert_int_equal(*((int *)get_data(test,0)),1);
	assert_int_equal(*((int *)get_data(test,1)),2);
	assert_int_equal(*((int *)get_data(test,2)),3);
	assert_int_equal(*((int *)get_data(test,3)),4);
	assert_int_equal(*((int *)get_data(test,4)),55);
	
}
	

void test_free_list(void **state)
{
	struct node * test = NULL;
	int *temp = malloc(sizeof(int));
	*temp = 4;
	add(&test,(void *)temp);
	temp = malloc(sizeof(int));
	*temp = 2;
	add(&test,(void *)temp);
	assert_int_equal(*((int *)get_data(test,0)),4);
	assert_int_equal(*((int *)get_data(test,1)),2);
	free_list(&test);
	assert_true(test == NULL);
	
	
}



int main(int argc, char* argv[]) 
{
	UnitTest tests[] = 
	{
		unit_test(test_parser),
		unit_test(test_read_file),
		unit_test(test_get_token_list),
		unit_test(test_get_len_list),
		unit_test(test_get_windows),
		unit_test(test_get_data),
		unit_test(test_merge_sort),
		unit_test(test_free_list)
		
	};
	return run_tests(tests);
}