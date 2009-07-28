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

	assert_int_equal(check->data,1);
	check = check->next;
	assert_int_equal(check->data,2);
	check = check->next;
	assert_int_equal(check->data,3);
	check = check->next;
	assert_int_equal(check->data,4);
	check = check->next;
	assert_true(check == NULL);
	
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
	struct node** list_of_parses = get_windows(check,3);
	//assert_string_equal(*(*list_of_parses)->data,"1");
	
	
}

void test_get_data(void **state)
{
	FILE *f = read_file("test.dat");
	struct node* check = get_token_list(f);
	assert_true(get_data(check,0)==1);
	assert_true(get_data(check,1)==2);
	assert_true(get_data(check,2)==3);
	assert_true(get_data(check,3)==4);
	//assert_false(get_data(check,4)==4);
	
}

void test_merge_sort(void **state)
{
	struct node * test = NULL;
	char f[40];
	add(&test,1);
	add(&test,4);
	add(&test,2);
	add(&test,5);
	add(&test,3);
	//print_nodes(test);
	//printf("%i",get_data(test,0));
	mergesort(test);
	printf("print nodes: ");
	print_nodes(test);
	//sprintf(f,"%i",get_data(test,0));
	printf("End list: %s", f);
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
		unit_test(test_merge_sort)
		
	};
	return run_tests(tests);
}