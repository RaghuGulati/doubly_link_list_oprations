#include <stdio.h>  
#include <stdlib.h>  
#include<string.h>
typedef double key_type;
#include "sorted_list.h"
typedef int value_type;
#define INSERTED_ORDER 1
#define SORTED_ORDER 2

/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
Sorted_list * map( Sorted_list * old_list_detail, value_type (*f)(value_type)){
	Sorted_list * new_list= (Sorted_list *)malloc(sizeof(Sorted_list));
	struct Node* old_node;

	old_node = old_list_detail->head;
    	while (old_node != NULL) {
        
		value_type value;
		value=(*f)(old_node->value);
		append(new_list,value,old_node->key);
        	old_node = old_node->next;

		
    	}
	return new_list;
	

}

/* function description
 * reduce the values of link list using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type)(value_type) function pointer
 * @param value_type init
 * @param int order specify order while reducing 
 * @return value_type single value after reduce
 */

value_type reduce( Sorted_list * list_detail, value_type (*f)(value_type,value_type),value_type init,int order){
        struct Node* node;
	value_type value = init;
	if(order == INSERTED_ORDER){
        	node = list_detail->head;
        	while (node != NULL) {
    
                	value=(*f)(value,node->value);
                	node = node->next;
        	}
	}
	else if(order ==SORTED_ORDER)
	{      node = list_detail->head_sort;
                while (node != NULL) {

                        value=(*f)(value,node->value);
                        node = node->sort;
                }
	}   
        return value;
}

/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*map_fn)(value_type) function pointer for map
 * @param value_type (*reduce_fn)(value_type)(value_type) function pointer for reduce
 * @param value_type init
 * @param int order specify order while reducing
 * @return value_type return single value.
 */

value_type map_reduce( Sorted_list * list_detail, value_type (*map_fn)(value_type), value_type (*reduce_fn)(value_type,value_type),value_type init,int order){
        struct Node* node;
        value_type value = init;
        if(order == INSERTED_ORDER){
                node = list_detail->head;
                while (node != NULL) {
			value_type tempvalue;
    			tempvalue=(*map_fn)(node->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node = node->next;
                }
        }
        else if(order ==SORTED_ORDER)
        {      node = list_detail->head_sort;
                while (node != NULL) {
			value_type tempvalue;
                        tempvalue=(*map_fn)(node->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node = node->sort;
                }
        }
        return value;
}
/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * first Sorted_list pointer 
 * @param Sorted_list * second Sorted_list pointer
 * @param value_type (*map_fn)(value_type) function pointer for map
 * @param int order specify order while reducing
 * @return value_type * return array of value_type.
 */

value_type * map_2_array( Sorted_list * list1,Sorted_list * list2, value_type (*map_fn)(value_type,value_type),int order){
        if(list2->size != list1->size)
		return NULL;

	struct Node* node1,*node2;
	value_type value ;
 value_type * array=(value_type*)malloc(sizeof(value_type)*list1->size);
	if(order == INSERTED_ORDER){
        	node1 = list1->head;
		node2= list2->head;
		
        	while (node1 != NULL && node2 != NULL) {
    
                	value=(*map_fn)(node1->value,node2->value);
                	//array[counter]=value;
			
                	*array=value;
			//counter++;
			array++;
			node1 = node1->next;
			node2= node2->next;
        	}
	}
	else if(order ==SORTED_ORDER)
	{      node1 = list1->head_sort;
	      node2 = list2->head_sort;
                while (node1 != NULL && node2 != NULL) {

                        
                        value=(*map_fn)(node1->value,node2->value);
			//array[counter]=value;
			
                	*array=value;
			array++;
			//counter++;
                        node1 = node1->sort;
                        node2 = node2->sort;
                }
	}   

        return --array;
}

/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * first Sorted_list pointer
 * @param Sorted_list * second Sorted_list pointer
 * @param value_type (*map_fn)(value_type) function pointer for map
 * @param value_type (*reduce_fn)(value_type)(value_type) function pointer for reduce
 * @param value_type init
 * @param int order specify order while reducing
 * @return value_type return single value.
 */

value_type  map_2_reduce( Sorted_list * list1,Sorted_list * list2, value_type (*map_fn)(value_type,value_type),value_type (*reduce_fn)(value_type,value_type),value_type init,int order){


       	struct Node* node1,*node2;
        value_type value = init;
        if(order == INSERTED_ORDER){
                node1 = list1->head;
		node2= list2->head;

                while (node1 != NULL && node2 != NULL) {
			value_type tempvalue;
                        tempvalue=(*map_fn)(node1->value,node2->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node1 = node1->next;

                        node2 = node2->next;
                }
        }
        else if(order ==SORTED_ORDER)
        {
                node1 = list1->head;
		node2= list2->head;

                while (node1 != NULL && node2 != NULL) {
			value_type tempvalue;
                        tempvalue=(*map_fn)(node1->value,node2->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node1 = node1->next;

                        node2 = node2->next;
                }
        }

	return value; 
}
//need to remove add2 fn after all completion
value_type add2(value_type x)
{
	return x+2;
}

/* function description
 * function to add 2 numbers (used to pass as function pointer)
 * @param value_type first number
 * @param value_type second number
 * @return value_type return sum of numbers.
 */

value_type add_2_number(value_type x,value_type y)
{
	return x+y;
}

/* function description
 * function to subtract 2 numbers (used to pass as function pointer)
 * @param value_type first number
 * @param value_type second number
 * @return value_type return diffrence of numbers.
 */

value_type subtract_2_number(value_type x,value_type y)
{
	return x-y;
}

/* function description
 * function to square a number used to pass as function pointer
 * @param value_type  number
 * @return value_type return square of number.
 */

value_type square_Of_A_Number(value_type x)
{
	return x*x;
}

/* function description
 * function to square second argument then add square to first argument used to pass as function pointer
 * @param value_type first number
 * @param value_type second number
 * @return value_type return sum of number after square of second argument.
 */

value_type square_and_add_number(value_type x,value_type y)
{
	return x + square_Of_A_Number(y);
}

value_type sum(Sorted_list * list,int order){
   return reduce(list,add_2_number,0,order);

}

/* function description
 * print array
 * @param value_type * arr arr to print
 * @param int size size of array
 * @return void.
 */

void print_array(value_type * arr, int size){

    	for(int z=0;z<size;z++){
            printf("\n     %d",*arr);
            arr--;
    	}

}

/* function description
 *takes two sorted lists of the same size, returns NULL if the sizes are different
 *produces an array whose values are the differences of the values in the sorted lists args
 *third argument that can be set to SORTED_ORDER or INSERTED_ORDER 
 *in order to follow the appropriate links.
 * @param Sorted_list * list1 
 * @param Sorted_list * list2
 * @param int order
 * @return value_type * pointer to array of diffrence.
 */

value_type * diff (Sorted_list * list1,Sorted_list *list2, int order)
{
	if(list1->size != list2->size)
	{ return NULL;}
	
	return map_2_array(list1,list2,subtract_2_number,order);
}
/* function description
 * takes a sorted list and produces a new sorted list whose value at a node equals 
 * the original value (not key) squared
 * @param Sorted_list * list
 * @return Sorted_list * return pointer to new Sorted_list
 */


Sorted_list * square(Sorted_list *list)
{
	return map(list,square_Of_A_Number);
}



/* function description
 * takes two sorted lists of the same size
 *returns NULL if the sizes are different produces a value computed as follows:
 * 1. at each node position, take the difference between the values
 * 2. square the resulting difference
 * 3. sum across all nodes into a single result
 * third argument that can be set to SORTED_ORDER or INSERTED_ORDER
 * in order to follow the appropriate links
 * @param Sorted_list * list1
 * @param Sorted_list * list2
 * @param int order
 * @return void * because we need to return NULL if size of link lists is different .
 */
void * sum_of_sq_diff(Sorted_list *list1,Sorted_list* list2,int order)
{
	  if(list1->size != list2->size)
	        { return NULL;}
	  printf("%d\n",map_2_reduce(list1,list2,subtract_2_number,square_and_add_number,0,order));
	
	  return (void *)1;	//help to remove warning "control reaches end of non-void function"
}

void printList_square(Sorted_list * list_detail)  
{  
    struct Node* node;
    
    node = list_detail->head;
    while (node != NULL) {  
        printf("     %d\n", node->value);  
        node = node->next; 
    }

}

/* Main function of the program*/
int main( int argc, char *argv[] )  
{  
	   /* initilizing head and head_sort for the linked list */
    Sorted_list * list[10];// = (Sorted_list *)malloc(sizeof(Sorted_list));
    int i = 0;    
 
    while(i<10){
    	list[i] = (Sorted_list *)malloc(sizeof(Sorted_list));
	list[i]->head=NULL;
    	list[i]->head_sort=NULL;
    	list[i]->tails=NULL;
    	list[i]->tails_sort=NULL;
	i++;
    }

    char commands[50][50];
    value_type value;
    key_type key;
    int j = 0;
    char *a;
    i = 0;
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
	char *cmd = strtok(a, "|");
	int n;
		if(strcmp(cmd,"rem_first")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_first(list[n], &value, &key);
			printf("rem_first|%d:%0.3f %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_last")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_first(list[n], &value, &key);
			printf("rem_last|%d: %0.3f %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_small")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_smallest_key(list[n], &value, &key);
			printf("rem_small|%d:%0.3f %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_large")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			remove_largest_key(list[n],&value,&key);
			printf("rem_large|%d:%0.3f %d\n",n, key, value);
		}
		else if(strcmp(cmd,"print_all")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			print_list_all(list[n]);
		}
		else if(strcmp(cmd,"print_sort")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			print_list_sort(list[n]);
		}
	
		else if((cmd[0] == 'p')){
			key_type tempk;
		        value_type tempv;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%lf", &tempk);

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			
			printf("p|%d:        %0.2f  %d\n",n, tempk, tempv);
			push(list[n], tempv, tempk);
		}

		else if((cmd[0] == 'a')){
			key_type tempk;
		        value_type tempv;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%lf", &tempk);

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			
			printf("a|%d:        %0.2f  %d\n",n, tempk, tempv);
			append(list[n], tempv, tempk);
		}

		else if(strcmp(cmd, "size")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	

			printf("size|%d:     List size = %d\n",n, list[n]->size);
		}

		else if(strcmp(cmd, "empty")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	

			empty_list(list[n]);
			printf("empty|%d:    size = %d\n",n, list[n]->size);

		}
		else if(strcmp(cmd, "sum")==0){
			value_type sum_val;

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");

			if(strcmp(cmd, "SORTED_ORDER") == 0){
				sum_val = sum(list[n],SORTED_ORDER);
			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				sum_val = sum(list[n],INSERTED_ORDER);
			}

			printf("sum:        list = %d, result = %d\n",n, sum_val);

		}

		else if(strcmp(cmd, "square")==0){
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);
			printf("square:     list = %d\n",n);	
			printList_square(square(list[n]));
		}

		else if(strcmp(cmd, "diff")==0){
			int m;
			cmd = strtok(NULL, ":");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &m);
			cmd = strtok(NULL, "\0");
			value_type * arr_ptr;
			printf("diff:       list1 = %d, list2 = %d", n, m);
			if(strcmp(cmd, "SORTED_ORDER") == 0){
				arr_ptr=diff(list[n],list[m],SORTED_ORDER);
				if(arr_ptr != NULL){
				print_array(diff(list[n],list[m],SORTED_ORDER),list[m]->size);
				} else{
                                        printf("\nEntered  lists are of different size");
                                }

			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				arr_ptr=diff(list[n],list[m],INSERTED_ORDER);
				if(arr_ptr !=NULL){
				print_array(diff(list[n],list[m],INSERTED_ORDER),list[m]->size);
				}
				else{
					printf("\nEntered  lists are of different size");
				}

			}
	
		}

		else if(strcmp(cmd, "sum_sq_d")==0){
			int m;
			cmd = strtok(NULL, ":");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &m);
			cmd = strtok(NULL, "\0");
			
			if(strcmp(cmd, "SORTED_ORDER") == 0){
				printf("\nsum_sq_d:   list1 = %d, list2 = %d, result = ",n,m);
				sum_of_sq_diff(list[n],list[m],SORTED_ORDER);
			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				printf("\nsum_sq_d:   list1 = %d, list2 = %d, result = ",n,m);
				sum_of_sq_diff(list[n],list[m],INSERTED_ORDER);
			}
	
		}

	j++;
    }
    //distroy array of list 
    int z=0;
	while(z<10){
		destroy_list(list[z]);		
		z++;
	}
    return 0;  
}  
