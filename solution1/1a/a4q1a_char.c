#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
typedef int key_type;
typedef char value_type[80];
  
// A linked list node  
struct Node {  
    value_type value;
    key_type key;
    struct Node* prev;
    struct Node* next;
    struct Node* prev_sorted;
    struct Node* sort;
};  

//Sorted_list data type
typedef struct {
    struct Node* head;
    struct Node* head_sort;
    struct Node* tails;
    struct Node* tails_sort;
    int size ;//store the node count
}Sorted_list;

//size function to calculate the size of linked list
int size(Sorted_list * list_detail) {
   int length = 0;
   struct Node *current;
	
   for(current = list_detail->head; current != NULL; current = current->next){
      length++;
   }
	
   return length;
}
void print_list_all(Sorted_list * list_detail);

/*push function to add the node to the head of the list*/
int push(Sorted_list * list_detail, value_type value, key_type  key)  
{  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    strcpy(new_node->value , *(&value));
    new_node->key = key;
  
    new_node->next = list_detail->head;
    new_node->prev = NULL;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;

    if (list_detail->head == NULL){
        list_detail->head = new_node;
	list_detail->tails=new_node;
    }

    else{
	    list_detail->head->prev = new_node;
    }
	
    if(list_detail->head_sort == NULL){
	    list_detail->head_sort = new_node;
	    list_detail->tails_sort=new_node;
    }

    else { 
	    if (list_detail->head_sort->key >= new_node->key) {
	        new_node->sort = list_detail->head_sort;
	        new_node->sort->prev_sorted = new_node;
	        list_detail->head_sort = new_node;
	    }

	    else {
	        current = list_detail->head_sort;
		struct Node* previous=(struct Node*)malloc(sizeof(struct Node));
	        // locate the node after which the new node is to be inserted
	        while (current != NULL && current->key <= new_node->key){
		    previous=current;

	            current =current->sort;
		    if(current == NULL){
			    break;
		    }
		}
	        /* Make the appropriate links */
	        new_node->sort = current;
	        // if the new node is not inserted at the end of the list
	        if (current != NULL){
			
	            	new_node->prev_sorted=current->prev_sorted;
			current->prev_sorted = new_node;
			//new_node->prev_sorted->sort=new_node;
			previous->sort=new_node;
		}else{
			new_node->prev_sorted=previous;
			previous->sort=new_node;
			list_detail->tails_sort=new_node;

		}
		
	        //current->sort = new_node;
	        //new_node->prev_sorted = current;
		//current->sort =new_node;
		
	    }
    }
    list_detail->head = new_node;
    list_detail->size += 1;
    return 1;
} 

int append(Sorted_list * list_detail, value_type  value, key_type  key){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    strcpy(new_node->value , *(&value));
    new_node->key = key;
  
    new_node->next = NULL;
    new_node->prev = list_detail->tails;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;
    
    if (list_detail->tails == NULL){
        list_detail->head = new_node;
	list_detail->tails = new_node;
    }

    else{
	    list_detail->tails->next = new_node;
    }
	
    if(list_detail->tails_sort == NULL){
	    list_detail->head_sort = new_node;
	    list_detail->tails_sort = new_node;
    }

    else { 
	    if (list_detail->head_sort->key >= new_node->key) {
	        new_node->sort = list_detail->head_sort;
	        new_node->sort->prev_sorted = new_node;
	        list_detail->head_sort = new_node;
	    }

	    else {
	        current = list_detail->head_sort;
		struct Node* previous=(struct Node*)malloc(sizeof(struct Node));
	        // locate the node after which the new node is to be inserted
	        while (current != NULL && current->key <= new_node->key){
		    previous=current;

	            current =current->sort;
		    if(current == NULL){
			    break;
		    }
		}
	        /* Make the appropriate links */
	        new_node->sort = current;
	        // if the new node is not inserted at the end of the list
	        if (current != NULL){
	            	new_node->prev_sorted=current->prev_sorted;
			current->prev_sorted = new_node;
			//new_node->prev_sorted->sort=new_node;
			previous->sort=new_node;
		}else{
			new_node->prev_sorted=previous;
			previous->sort=new_node;
			list_detail->tails_sort=new_node;

		}
		
	        //current->sort = new_node;
	        //new_node->prev_sorted = current;
		//current->sort =new_node;
		
	    }
    }
    list_detail->tails = new_node;
    list_detail->size += 1;   
    return 1;
}


//Function to print the list according to insertion order as well as key sort order
void print_list_all(Sorted_list * list_detail)  
{  
    struct Node* node;
    
    node = list_detail->head;
    printf("print_all:  Insertion Order \n");
    while (node != NULL) {  
        printf("     %d  %s\n", node->key, node->value);  
        node = node->next; 
    }

}

void print_list_sort(Sorted_list * list_detail){
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
	
    printf("print_all:  Key Sort Order  \n");
    n2 = list_detail->head_sort;
    while (n2 != NULL) {  
        printf("     %d  %s\n", n2->key, n2->value);  
        n2 = n2->sort; 
    }

}
/*
 *function to remove first node
 *@param Sorted_list *
 *@param value_type
 *@param key_type *
 */

int remove_first(Sorted_list * list_detail,value_type * value, key_type * key)
{
	struct Node *ptr;
	value_type deleted_Node_Value;
        key_type 	deleted_Node_Key;
	if(list_detail->head == NULL){
		return 0;
		//printf("\n UNDERFLOW");
	}
	else if(list_detail->head->next==NULL && list_detail->head->prev== NULL ){
		strcpy(deleted_Node_Value,list_detail->head->value);
		deleted_Node_Key=list_detail->head->key;
		//onlt one element in list
		list_detail->head= NULL;
		list_detail->head_sort=NULL;
		list_detail->tails=NULL;
		list_detail->tails_sort=NULL;
		free(list_detail->head);
		//printf("\nNode deleted\n");
	}
	else{
		ptr =list_detail->head;
		strcpy(deleted_Node_Value,list_detail->head->value);
                deleted_Node_Key=list_detail->head->key;
		//update head_sort
		if(list_detail->head->prev_sorted != NULL && list_detail->head->sort != NULL){//if head and head_sort are same
			list_detail->head->prev_sorted->sort=list_detail->head->sort;
		        list_detail->head->sort->prev_sorted=list_detail->head->prev_sorted;
		}
		else  if(list_detail->head->prev_sorted == NULL && list_detail->head->sort != NULL)
		{
			list_detail->head->sort->prev_sorted= NULL;
			list_detail->head_sort=list_detail->head_sort->sort;
		}
		else  if(list_detail->head->prev_sorted != NULL && list_detail->head->sort == NULL)
		{
			list_detail->head->prev_sorted->sort=NULL;
			list_detail->tails_sort=list_detail->tails_sort->prev_sorted;
		}
		//update head
                list_detail->head=list_detail->head->next;
		list_detail->head->prev=NULL;
		free(ptr);
	}
	list_detail->size--;
	strcpy(*value,deleted_Node_Value);
	*key=deleted_Node_Key;
	return 1;
}
/*
 *function to remove last  node
 *@param Sorted_list *
 *@param value_type
 *@param key_type *
 */
int remove_last(Sorted_list * list_detail,value_type * value, key_type * key)
{
        struct Node *ptr;
        value_type deleted_Node_Value;
        key_type   deleted_Node_Key;
        if(list_detail->tails == NULL){
               return 0;
		//  printf("\n UNDERFLOW");
        }
        else if(list_detail->tails->prev==NULL && list_detail->tails->next== NULL){
                strcpy(deleted_Node_Value,list_detail->tails->value);
                deleted_Node_Key=list_detail->tails->key;
                //onlt one element in list
                list_detail->tails= NULL;
                list_detail->tails_sort=NULL;
                list_detail->head=NULL;
                list_detail->head_sort=NULL;
                free(list_detail->tails);
               // printf("\nNode deleted\n");
        }
        else{
                ptr =list_detail->tails;
                strcpy(deleted_Node_Value,list_detail->tails->value);
                deleted_Node_Key=list_detail->tails->key;
                //update tails_sort
		if(list_detail->tails->sort != NULL && list_detail->tails->prev_sorted != NULL){// check tails and tails_sort are same
                
			list_detail->tails->sort->prev_sorted=list_detail->tails->prev_sorted;
			list_detail->tails->prev_sorted->sort=list_detail->tails->sort;
		}
		else if (list_detail->tails->sort ==NULL && list_detail->tails->prev_sorted != NULL)
		{
			list_detail->tails->prev_sorted->sort=NULL;
			list_detail->tails_sort=list_detail->tails_sort->prev_sorted;
		}
		else if(list_detail->tails->prev_sorted ==NULL && list_detail->tails->sort !=NULL)
		{
			list_detail->tails->sort->prev_sorted=NULL;
			list_detail->head_sort=list_detail->head_sort->sort;
		}

		
                //update tails
                list_detail->tails=list_detail->tails->prev;
                list_detail->tails->next=NULL;
                free(ptr);
        }
	list_detail->size--;
        strcpy(*value,deleted_Node_Value);
        *key=deleted_Node_Key;
        return 1;
}

/*
 *function to remove node having smallest value
 *@param Sorted_list *
 *@param value_type
 *@param key_type *
 */
int remove_smallest_key(Sorted_list * list_detail,value_type * value, key_type * key)
{
	struct Node *ptr;
	value_type deleted_Node_Value;
        key_type 	deleted_Node_Key;
	if(list_detail->head_sort == NULL){
		return 0;
	}
	else if(list_detail->head_sort->sort==NULL){
		strcpy(deleted_Node_Value,list_detail->head_sort->value);
		deleted_Node_Key=list_detail->head_sort->key;
		//onlt one element in list
		list_detail->head_sort= NULL;
		list_detail->head=NULL;
		list_detail->tails=NULL;
		list_detail->tails_sort=NULL;
		free(list_detail->head_sort);
	//	printf("\nNode deleted\n");
	}
	else{
		ptr =list_detail->head_sort;
		strcpy(deleted_Node_Value,list_detail->head_sort->value);
                deleted_Node_Key=list_detail->head_sort->key;
		//update head
		if(list_detail->head_sort->next != NULL)
		{
			list_detail->head_sort->next->prev=list_detail->head_sort->prev;
		}
		

		if(list_detail->head_sort->prev != NULL && list_detail->head_sort->next != NULL){//check head and head_sort are same
			list_detail->head_sort->prev->next=list_detail->head_sort->next;
			list_detail->head_sort->next->prev=list_detail->head_sort->prev;
		}
		else if(list_detail->head_sort->prev == NULL && list_detail->head_sort->next != NULL)
		{
			list_detail->head_sort->next->prev=NULL;
			list_detail->head=list_detail->head->next;
		}
		else if(list_detail->head_sort->next ==NULL && list_detail->head_sort->prev != NULL)
		{
			list_detail->head_sort->prev->next = NULL;
			list_detail->tails=list_detail->tails->prev;
		}
		
		
		//update head_sort
                list_detail->head_sort=list_detail->head_sort->sort;
		list_detail->head_sort->prev_sorted=NULL;
		free(ptr);
	}
	list_detail->size--;
	strcpy(*value,deleted_Node_Value);
	*key=deleted_Node_Key;
	return 1;
}

/*
 *function to remove node having largest key
 *@param Sorted_list *
 *@param value_type
 *@param key_type *
 */
int remove_largest_key(Sorted_list * list_detail,value_type * value, key_type * key)
{
        struct Node *ptr;
        value_type deleted_Node_Value;
        key_type   deleted_Node_Key;
        if(list_detail->tails_sort == NULL){
               return 0;
		// printf("\n UNDERFLOW");
        }
        else if(list_detail->tails_sort->prev_sorted ==NULL && list_detail->tails_sort->sort ==NULL ){
               strcpy( deleted_Node_Value,list_detail->tails_sort->value);
                deleted_Node_Key=list_detail->tails_sort->key;
                //onlt one element in list
                list_detail->tails= NULL;
                list_detail->tails_sort=NULL;
                list_detail->head=NULL;
                list_detail->head_sort=NULL;
                free(list_detail->tails_sort);
                printf("\nNode deleted\n");
        }
        else{
                ptr =list_detail->tails_sort;
                strcpy(deleted_Node_Value,list_detail->tails_sort->value);
                deleted_Node_Key=list_detail->tails_sort->key;
                //update tails
                if(list_detail->tails_sort->next != NULL && list_detail->tails_sort->prev != NULL){//  check  tails and tails_sort are same

                        list_detail->tails_sort->next->prev=list_detail->tails_sort->prev;
                       	list_detail->tails_sort->prev->next=list_detail->tails_sort->next;
                }
		else if(list_detail->tails_sort->next == NULL && list_detail->tails_sort->prev != NULL)
		{
			list_detail->tails_sort->prev->next=NULL;
			list_detail->tails= list_detail->tails->prev;
		}
		else if(list_detail->tails_sort->next != NULL && list_detail->tails_sort->prev == NULL)
		{
			list_detail->tails_sort->next->prev=NULL;
			list_detail->head=list_detail->head->next;
		}


                //update tails_sort
                list_detail->tails_sort=list_detail->tails_sort->prev_sorted;
                list_detail->tails_sort->sort=NULL;
                free(ptr);
        }
	list_detail->size--;
        strcpy(*value,deleted_Node_Value);
        *key=deleted_Node_Key;
        return 1;
}


void empty_list(Sorted_list * list_detail){
	struct Node* current = list_detail->head;
	struct Node* nxt = (struct Node *)malloc(sizeof(struct Node *));

	while(current!= NULL){
		nxt = current->next;
		free(current);
		current = nxt;
	}

	list_detail->head = NULL;
	list_detail->head_sort = NULL;
	list_detail->size=0;
}
	
void destroy_list(Sorted_list * list_detail){
	struct Node* current = list_detail->head;
	struct Node* nxt = (struct Node *)malloc(sizeof(struct Node *));

	while(current!= NULL){
		nxt = current->next;
		free(current);
		current = nxt;
	}

	list_detail->head = NULL;
	list_detail->head_sort = NULL;
	free(list_detail);
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
		if(strcmp(a,"rem_first")==0){
			remove_first(list_detail, &value, &key);
			printf("rem_first:  %d %s \n", key, value);
		}
		else if(strcmp(a,"rem_last")==0){
			remove_last(list_detail, &value, &key);
			printf("rem_last:   %d %s \n", key, value);

		}
		else if(strcmp(a,"rem_small")==0){
			remove_smallest_key(list_detail,&value,&key);
			printf("rem_small:  %d %s\n", key, value);
		}
		else if(strcmp(a,"rem_large")==0){
			remove_largest_key(list_detail,&value,&key);
			printf("rem_large:  %d %s\n", key, value);
		}
		else if(strcmp(a,"print_all")==0){
			print_list_all(list_detail);
		}
		else if(strcmp(a,"print_sort")==0){
			print_list_sort(list_detail);
		}
	
		else if((a[0] == 'p')){
			int tempk;
			char *p = strtok_r(a," ",&a);
			p = strtok_r(a, "\0", &a);
			if(strlen(p) >= 80){
				printf("lenth limit of string exceeded");
			}
			tempk = strlen(p);
			printf("p:          %s\n",p);
			push(list_detail, p, tempk);
		}

		else if((a[0] == 'a')){
			int tempk;
			char *s;
			s = a;
			char *p = strtok(s," ");
			p = strtok(NULL, "\0");
			printf("a:          %s\n",p);
			tempk = strlen(p);
			append(list_detail, p, tempk);
		}

		else if(strcmp(a, "size")==0){
			printf("size:       List size = %d\n", list_detail->size);
		}

		else if(strcmp(a, "empty")==0){
			empty_list(list_detail);
			printf("empty:      size = %d\n", list_detail->size);

		}
	j++;
    }
    destroy_list(list_detail);

    return 0;  
}  
