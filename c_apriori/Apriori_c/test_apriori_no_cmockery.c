#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "apriori.h"
#include "linked_list.h"

int main(int argc, char* argv[]) 
{
	
	int c;
	double m_value = .003;
	int d_value = -1;
	int t_value = 3;
	int w_value = 0;
	char *o_filename = "outputfile.txt";
	struct node *iter;
	struct node *next;
	while((c = getopt(argc,argv,"d:m:w:t:o:")) != -1)
	{		
		switch(c)
		{
			case 'd':
				d_value = atoi(optarg);
				break;
			case 'm':
				m_value = atof(optarg);
				break;
			case 'w':
				w_value = atoi(optarg);
				break;
			case 't': 
				t_value = atoi(optarg);
				break;
			case 'o':
				o_filename = optarg;
				break;
			default:
				break;
		}
	}
	
	
	
	printf("d_value = %i\nm_value = %f\nw_value = %i\nt_value = %i\no_filename: %s\n",d_value,m_value,w_value,t_value,o_filename);
	
	printf("Non-option argument: %s\n",argv[optind]);	
	
	int counter = 0;
	int index;
	for (index = optind; index < argc; index++)
	{
    	counter += 1;
	}
   	if(counter > 1)
   	{
   		printf("ERROR: Incorrect Amount of Arguments\n");
   		exit(0);
   	}
   	
   	if(m_value < 0.0 || m_value > 1.0)
   	{
   		printf("ERROR: Minsup is a percentage and must be between 0 and 1\n");
   		exit(0); 
   	}
   	
   	if(d_value < 0 && w_value == 0)
   		w_value = 5;
   	else if(d_value >= 0 && w_value > 0)
   	{
   		printf("ERROR: Dynamic Windowing and Window Size are mutually exclusive\n");
   		exit(0);
   	}
   	  	
	struct node *freq_list = apriori(m_value,w_value,argv[optind], o_filename,d_value,t_value);

	iter = freq_list;
	while(iter != NULL)
	{
		next = iter->next;
		print_lists((struct node *)iter->data);
		
		free_list_of_lists((struct node **)&iter->data);
		free(iter);
		
		iter = next;
	}
	
	return 0;
}