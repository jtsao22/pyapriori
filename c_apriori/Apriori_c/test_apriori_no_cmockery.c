#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "apriori.h"
#include "linked_list.h"

int main(int argc, char* argv[]) 
{
	int d_flag = 0;
	int c;
	double m_value = .003;
	int t_value = 3;
	int w_value = 3;
	char *o_filename = "outputfile.txt";
	struct node *iter;
	struct node *next;
	
	while((c = getopt(argc,argv,"dm:w:t:o:")) != -1)
	{		
		switch(c)
		{
			case 'd':
				d_flag = 1;
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
	
	printf("d_flag = %i\nm_value = %f\nw_value = %i\nt_value = %i\no_filename: %s\n",d_flag,m_value,w_value,t_value,o_filename);
	
	printf("Non-option argument: %s\n",argv[optind]);	
	
	struct node *freq_list = apriori(m_value,w_value,argv[optind], o_filename,d_flag,t_value);
	
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