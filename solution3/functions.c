#include <stdio.h>  
#include <stdlib.h>  
#include<string.h>
#include "sorted_list.h"
#define INSERTED_ORDER 1
#define SORTED_ORDER 2

/* function description
 * filter the values using function pointer and recusion.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) test function pointer
 * @return Sorted_list pointer of new link list with filtered values.
 */
Sorted_list * filter( Sorted_list * old_list_detail, int  (*f)(value_type)){
	Sorted_list * temp= (Sorted_list *)malloc(sizeof(Sorted_list));

	Sorted_list * new_list;
	temp->head=old_list_detail->head;

        if(temp->head == NULL){
		 new_list=(Sorted_list *)malloc(sizeof(Sorted_list));
		return new_list;
	}
	else{
		temp->head=temp->head->next;
		new_list= filter(temp,*f);
	}


	struct Node* node=old_list_detail->head;
	if((*f)(node->value))
	{
			append(new_list,node->value,node->key);		
	}
	free(temp);
	return new_list;


}


/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*f)(value_type) function pointer
 * @return Sorted_list pointer of new link list.
 */
Sorted_list * map( Sorted_list * old_list_detail, value_type (*f)(value_type)){
	Sorted_list * new_list= (Sorted_list *)malloc(sizeof(Sorted_list));
	struct Node* old_node;

	//new_list->size=old_list_detail->size;
	old_node = old_list_detail->head;
        //printf("print_all:  Insertion Order \n");
    	while (old_node != NULL) {
        
		//struct Node * new_node=(Node*)malloc(sizeof(struct Node));
		//	printf("     %d  %d\n", node->key, node->value);
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
 * @param int (*f)(value_type* ,value_type*,value_type *) function pointer
 * @param value_type init
 * @param int order specify order while reducing 
 * @return value_type single value after reduce
 */

value_type reduce( Sorted_list * list_detail, int (*f)(value_type *,value_type *,value_type *),value_type init,int order){
        struct Node* node;
	value_type value = init;
	if(order == INSERTED_ORDER){
        	node = list_detail->head;
        	while (node != NULL) {
    
                	(*f)(&value,&value,&node->value);
                	node = node->next;
        	}
	}
	else if(order ==SORTED_ORDER)
	{      node = list_detail->head_sort;
                while (node != NULL) {

                       if(!(*f)(&value,&value,&node->value))
                        {
                                value.num=0;
                                value.denom=0;
                                return value;//it will be used to print overflow/underflow condition
                        }

                        node = node->sort;
                }
	}   
	return value; 
}
/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * Sorted_list pointer
 * @param value_type (*map_fn)(value_type) function pointer for map
 * @param value_type (*reduce_fn)(value_type,value_type) function pointer for reduce
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
 * @param value_type (*reduce_fn)(value_type,value_type) function pointer for reduce
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


