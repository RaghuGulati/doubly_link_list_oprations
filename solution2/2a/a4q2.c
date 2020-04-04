#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
typedef double key_type;
typedef int value_type;
#include "sorted_list.h"

int count_down(int n)
{
	
	if(n ==0){

	printf("%d",n);
		return 0;
	}

	printf("%d, ",n);

	return count_down(n-1);
}



int count_up(int n)
{
	static int count=0;
	if(n ==count){
		
		printf("%d",2*count);
		count=0;
		return 0;
		
	}
	printf("%d, ",2*count);
	count++;
	
	return count_up(n);
}


/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
int  nth( Sorted_list * list,struct Node * node,int n){
	
	if(list->size -1 <n || n<0)
	{
		return 0;
	}

	if(n==0){
		printf("     %0.2f  %d",node->key,node->value);
		return 0;
	}
	
	return nth(list,node->next,n-1);
}

/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
int  nth_sorted( Sorted_list * list, struct Node * node,int n){
	
	if(list->size -1 <n || n<0)
        {
                return 0;
        }



	if(n==0){
		printf("     %0.2f  %d",node->key,node->value);
		return 0;
	}
	
	return nth_sorted(list, node->sort,n-1);
}


/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
int  remove_nth( Sorted_list * list, struct Node * node,int n){
   if(list->size-1 < n || n < 0){
                return 0;
        }
	

	if(n==0){
		struct Node * ptr;
		 ptr =node;
             value_type   deleted_Node_Value=node->value;
             key_type   deleted_Node_Key=node->key;
                //update head_sort
                if(node->prev_sorted != NULL && node->sort != NULL){
                        node->prev_sorted->sort=node->sort;
                        node->sort->prev_sorted= node->prev_sorted;
                }
                else  if( node->prev_sorted == NULL && node->sort != NULL)
                {
                        node->sort->prev_sorted= NULL;
                        list->head_sort=list->head_sort->sort;
                }
                else  if(node->prev_sorted != NULL && node->sort == NULL)
                {
                        node->prev_sorted->sort=NULL;
                        list->tails_sort=node->prev_sorted;
                }
		else if(node->next==NULL && node->prev== NULL)
		{
			list->head= NULL;
	                list->head_sort=NULL;
        	        list->tails=NULL;
                	list->tails_sort=NULL;

		}
                //update head



                if(node->prev != NULL && node->next != NULL){
                        node->prev->next=node->next;
                        node->next->prev=node->prev;
                }
                else if(node->prev == NULL && node->next != NULL)
                {
                        node->next->prev=NULL;
                        list->head=list->head->next;
                }
                else if(node->next ==NULL && node->prev != NULL)
                {
                        node->prev->next = NULL;
                        list->tails=list->tails->prev;
                }
		else if(node->next ==NULL && node->prev==NULL)
		{
			list->head_sort= NULL;
	                list->head=NULL;
        	        list->tails=NULL;
                	list->tails_sort=NULL;

		}
		list->size=list->size-1;			

                free(ptr);

		printf("     %0.2f  %d",deleted_Node_Key,deleted_Node_Value);
		return 0;
	}
	
	return remove_nth(list,node->next,n-1);
}


/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
int  remove_nth_sorted( Sorted_list * list, struct Node * node,int n){
	 if(list->size-1 < n || n < 0){
                return 0;
        }
	

	if(n==0){
		struct Node * ptr;
		 ptr =node;
             value_type   deleted_Node_Value=node->value;
             key_type   deleted_Node_Key=node->key;
                //update head_sort
                if(node->prev_sorted != NULL && node->sort != NULL){
                        node->prev_sorted->sort=node->sort;
                        node->sort->prev_sorted= node->prev_sorted;
                }
                else  if( node->prev_sorted == NULL && node->sort != NULL)
                {
                        node->sort->prev_sorted= NULL;
                        list->head_sort=list->head_sort->sort;
                }
                else  if(node->prev_sorted != NULL && node->sort == NULL)
                {
                        node->prev_sorted->sort=NULL;
                        list->tails_sort=node->prev_sorted;
                }
		else if(node->next==NULL && node->prev== NULL)
		{
			list->head= NULL;
	                list->head_sort=NULL;
        	        list->tails=NULL;
                	list->tails_sort=NULL;

		}
                //update head



                if(node->prev != NULL && node->next != NULL){
                        node->prev->next=node->next;
                        node->next->prev=node->prev;
                }
                else if(node->prev == NULL && node->next != NULL)
                {
                        node->next->prev=NULL;
                        list->head=list->head->next;
                }
                else if(node->next ==NULL && node->prev != NULL)
                {
                        node->prev->next = NULL;
                        list->tails=list->tails->prev;
                }
		else if(node->next ==NULL && node->prev==NULL)
		{
			list->head_sort= NULL;
	                list->head=NULL;
        	        list->tails=NULL;
                	list->tails_sort=NULL;

		}
		list->size=list->size-1;			

                free(ptr);

		printf("     %0.2f  %d",deleted_Node_Key,deleted_Node_Value);
		return 0;
	}
	
	return remove_nth_sorted(list,node->sort,n-1);
}






/* Main function of the program*/
int main( int argc, char *argv[] )  
{  
    /* initilizing head and head_sort for the linked list */
    Sorted_list * list_detail=(Sorted_list *)malloc(sizeof(Sorted_list));
    list_detail->head=NULL;
    list_detail->head_sort=NULL;
    list_detail->tails=NULL;
    list_detail->tails_sort=NULL;
    int i = 0;    
    char commands[50][50];
    value_type value;
    key_type key;
    int j = 0;
    char *a;

    if(argc == 1){
    	printf("input commands. press ctrl+D to stop entering inputs\n");
	char *input_string;
                size_t input_string_length = 50;
                input_string = (char *) malloc(input_string_length);

                while(getline(&input_string, &input_string_length, stdin) != -1)
                {
                        input_string[strcspn(input_string, "\n")] = 0;
			strcpy(commands[i], input_string);
			i++;
		}
    }

    else if(argc > 2){
    	printf("Too many arguments supplied");
    }
    else{
        FILE *fp;
	fp = fopen(argv[1],"r");

	while(fgets(commands[i],50, fp) != NULL) {
	        commands[i][strlen(commands[i]) -1] = '\0';
		i++;
	}
    }

    while(j<i){
	a = commands[j];
	int n;
	char *cmd = strtok(a, " ");
		if(strcmp(a,"rem_first")==0){
			remove_first(list_detail, &value, &key);
			printf("rem_first:  %0.3f %d \n", key, value);
		}
		else if(strcmp(a,"rem_last")==0){
			remove_last(list_detail, &value, &key);
			printf("rem_last:   %0.3f %d \n", key, value);

		}
		else if(strcmp(a,"rem_small")==0){
			remove_smallest_key(list_detail,&value,&key);
			printf("rem_small:  %0.3f %d\n", key, value);
		}
		else if(strcmp(a,"rem_large")==0){
			remove_largest_key(list_detail,&value,&key);
			printf("rem_large:  %0.3f %d\n", key, value);
		}
		else if(strcmp(a,"print_all")==0){
			print_list_all(list_detail);
		}
		else if(strcmp(a,"print_sort")==0){
			print_list_sort(list_detail);
		}
	
		else if((a[0] == 'p')){
			key_type tempk;
		        value_type tempv;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%lf", &tempk);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			printf("p:          %0.2f  %d\n",tempk, tempv);
			push(list_detail, tempv, tempk);
		}

		else if((a[0] == 'a')){
			key_type tempk;
		        value_type tempv;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%lf", &tempk);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			printf("a:          %0.2f  %d\n",tempk, tempv);
			append(list_detail, tempv, tempk);
		}

		else if(strcmp(a, "size")==0){
			printf("size:       List size = %d\n", list_detail->size);
		}

		else if(strcmp(a, "empty")==0){
			empty_list(list_detail);
			printf("empty:      size = %d\n", list_detail->size);

		}

		else if(strcmp(cmd, "count_up") == 0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			//printf("count_up %d\n", n);
			printf("count_up from 0 to %d\n     ", 2*n);
			count_up(n);
			printf("\n");

		}

		else if(strcmp(cmd, "count_down") == 0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
//			printf("count_up %d\n", n);
			printf("count_down from 0 to %d\n     ", n);
			count_down(n);
			printf("\n");
		}

		else if(strcmp(cmd, "nth") == 0){
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, "\0");
//			printf("nth %d, %s\n", n, cmd);
			if(strcmp(cmd, "INSERTED_ORDER")==0){
				printf("nth:        n = %d, %s\n", n, cmd);
				nth(list_detail, list_detail->head,n);
				printf("\n");
			}
			else if(strcmp(cmd, "SORTED_ORDER")==0){
				printf("nth:        n = %d, %s\n", n, cmd);
				nth_sorted(list_detail, list_detail->head_sort,n);
				printf("\n");

			}
		}

		else if(strcmp(cmd, "remove_nth") == 0){
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, "\0");
			if(strcmp(cmd, "INSERTED_ORDER")==0){
				printf("remove_nth: n = %d, %s\n", n, cmd);
				remove_nth(list_detail, list_detail->head,n);
				printf("\n");
			}
			else if(strcmp(cmd, "SORTED_ORDER")==0){
				printf("remove_nth: n = %d, %s\n", n, cmd);
				remove_nth_sorted(list_detail, list_detail->head_sort,n);
				printf("\n");

			}

		
		}
	j++;
    }
   destroy_list(list_detail);

    return 0;  
}  
