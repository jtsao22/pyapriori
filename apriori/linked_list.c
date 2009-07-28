#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int add(struct node **n, int d)
{
	//add a node to linked list
	if(*n == NULL)
	{
		if((*n = malloc(sizeof(struct node)))==NULL)
		{
			printf("Memory allocation error");
			return 0;
		}
		(*n)->next = NULL;
		(*n)->data = d;
		
	}
	else
	{
		add(&((*n)->next),d);	
	}
	return 1;
	
}

void print_nodes(struct node *n)
{
	//print the node data in the linked list
	while(n!= NULL)
	{
		printf("%i",n->data);
		n = n->next;
	}
	
	
}

int get_len_list(struct node *n)
{
	int len = 0;
	while(n != NULL)
	{
		len += 1;
		n = n->next;
	}
	return len;		
}

int get_data(struct node *n, int index)
{
	int count = 0;
	while(n != NULL)
	{
		if(count == index)
			return n->data;
		count += 1;
		n = n->next; 	
	}

	// Functions that call this function will only call
	// this function if they know the data is in the list
	// Thus, this line should not be outputted and is here
	// in case there's an error. 	
	printf("Error: Could not find data");
	return 0;
}

//void merge(struct node* t_1, struct node *t_2, int count1, int count2)
//{
//	
//	int i,i1,i2,k;
//	i=i1 = i2 = k = 0;
//	struct node * temp = NULL;
//	
//	while((i1<count1) && (i2<count2))
//	{
//		
//		while((i1<count1) && (get_data(t_1,i1))<= (get_data(t_2,i2)))
//	  	{
//	  		printf("added left: %i\n",get_data(t_1,i1));
//	    	add(&temp,get_data(t_1,i1));
//	    	i++;
//	    	i1++;
//	  	}
//	  	if (i1<count1)
//	  	{
//	   	 	while((i2<count2) && (get_data(t_2,i2)<=(get_data(t_1,i1))))
//	   	 	{
//	   	 		printf("added right: %i\n",get_data(t_2,i2));
//	   	  		add(&temp,get_data(t_2,i2));
//	   	  		i++;
//	   	  		i2++;
//	   	 	}
//	  	}
//	}
//	printf("\nprint nodes left: \n");
//	print_nodes(t_1);
//	printf("\nprint nodes right: ");
//	print_nodes(t_2);
//	printf("\n");
//	
//	
//	struct node *iter1 = temp;
//	struct node *iter2 = t_1;
//	k = 0;
//	while(k < i1-1)
//	{
//		iter2 = iter2->next;
//		k++;
//	}
//	k = 0;
//	printf("%i", iter1->data);
//	while(k < i-1)
//	{
//		iter1 = iter1->next;
//		k++;
//	}
//	
//	printf("%i\n", iter1->data);
//	
//	//memcpy(iter1,iter2,(count1-i1)*sizeof(struct node));
//	
//	
//	k = i1;
//	while(iter2 != NULL && count1-k > 0)
//	{
//		iter1 = iter2;
//		printf("iter1-> data: %i\n", iter1->data);
//		iter1 = iter1->next;
//		iter2 = iter2->next;
//		k++;
//	}
//	
//	print_nodes(iter2);
//	
//	//memcpy(temp+i,t_1+i1,(count1-i1)*sizeof(struct node));
//	iter1 = t_1;
//	iter2 = temp;
//	while(iter2 != NULL)
//	{
//		iter1 = iter2;
//		iter1 = iter1->next;
//		iter2 = iter2->next;
//	}
//	//memcpy(t_1,temp,count1*sizeof(struct node));
//	
//	iter1 = temp;
//	iter2 = t_2+i2;
//	while(iter2 != NULL)
//	{
//		iter1 = iter2;
//		iter1 = iter1->next;
//		iter2 = iter2->next;
//	}
//	
//	//memcpy(temp+i,t_2+i2,(count2-i2)*sizeof(struct node));
//	
//
////	iter1 = t_2;
////	iter2 = temp+count1;
////	while(iter2 != NULL)
////	{
////		iter1 = iter2;
////		iter1 = iter1->next;
////		iter2 = iter2->next;
////	}
//	
//	
//	//t_2->data = (temp+count1)->data;
//	//memcpy(t_2,temp+count1,count2*sizeof(struct node));
//	
//	
//	free(temp);
//
//}
//
//
//void merge_sort(struct node * token_list, int count)
//{
//	int k = 0;
//	struct node *temp_list = token_list;
//	if (count == 1)
//		return;
//	
//	merge_sort(token_list,count/2);
//	while(k <= count/2)
//	{
//		temp_list = temp_list->next;
//		k++;
//	}
//	merge_sort(temp_list, (count + 1)/2);
//	merge(token_list,temp_list,count/2,(count+1)/2);	
//}

/* merge the lists.. */
struct node *merge(struct node *head_one, struct node *head_two) {
 struct node *head_three;

 if(head_one == NULL) 
  return head_two;

 if(head_two == NULL) 
  return head_one;

 if(head_one->data < head_two->data) {
  head_three = head_one;
  head_three->next = merge(head_one->next, head_two);
 } else {
  head_three = head_two;
  head_three->next = merge(head_one, head_two->next);
 }

 return head_three;
}



struct node *mergesort(struct node *head) {
 struct node *head_one;
 struct node *head_two;

 if((head == NULL) || (head->next == NULL)) 
  return head;

 head_one = head;
 head_two = head->next;
 while((head_two != NULL) && (head_two->next != NULL)) {
  head = head->next;
  head_two = head->next->next;
 }
 head_two = head->next;
 head->next = NULL;

 return merge(mergesort(head_one), mergesort(head_two));
}


