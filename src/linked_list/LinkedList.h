#ifndef LINKED_LIST_H
#define LINKED_LIST_H

	#include <stdbool.h>	
	#include <stdint.h>

	/*--------------- TYPEDEF's ---------------*/
	typedef int Data;	
	
	struct node{
		Data data;
		struct node *next;
	};
		
	struct list{
		struct node *head;
		uint16_t size;
		struct node *tail;
	};

	typedef struct node Node;
	typedef struct list List;

	typedef struct node* NodePtr;
	typedef struct list* ListPtr;

	/*--------------- METHODS ---------------*/
	ListPtr create_list();	
	int insert_first(ListPtr list_ptr, Data data );
	int insert_last(ListPtr list_ptr, Data data );
	
	NodePtr get_node(ListPtr list_ptr ,int index);	
	
	int remove_first(ListPtr list_ptr);
	int remove_last(ListPtr list_ptr);

	//void sort(List *list);
	//void printList();
#endif
