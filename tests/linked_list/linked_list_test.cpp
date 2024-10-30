#include <gtest/gtest.h>

extern "C"{
	#include <LinkedList.h>
}

TEST(LinkedListTest,CreatingEmptyList){
	ListPtr empty_list;
	empty_list = create_list();	
	
	ASSERT_TRUE(empty_list->head == nullptr);	
	ASSERT_TRUE(empty_list->tail == nullptr);	
	ASSERT_TRUE(empty_list->size == 0);
}

TEST(LinkedListTest,InsertingFirstNode_ValidInputs){
	ListPtr list1;
	list1 = create_list();	

	// Check that the size is incremented correctly and the data hold by the inserted node too
	ASSERT_TRUE(insert_first(list1, 20) == 1);
	ASSERT_TRUE( ( list1 -> size ) == 1);
	ASSERT_TRUE((list1->head)-> data == 20);

	ASSERT_TRUE(insert_first(list1, 30) == 1);
	ASSERT_TRUE( ( list1 -> size ) == 2);

	// Check that the nodes have the correct order 	
	NodePtr tempPtr = (list1->head)-> next ;
	ASSERT_TRUE((list1->head)-> data == 30);
	ASSERT_TRUE(tempPtr-> data == 20);
}

TEST(LinkedListTest,InsertingFirstNode_NullList){

	ASSERT_TRUE(insert_first(nullptr, 20) == -1);

}

TEST(LinkedListTest,InsertingFirstNode_EmptyList){
	ListPtr list2;
	list2 = create_list();	
	
	ASSERT_TRUE(insert_first(list2, 20) == 1);
	ASSERT_TRUE(list2->head == list2->tail);
}

TEST(LinkedListTest,InsertingLastNode_PopulatedList){
	ListPtr list2;
	list2 = create_list();	
	insert_first(list2,100);
	insert_first(list2,100);
	insert_first(list2,100);
	insert_first(list2,100);

	ASSERT_TRUE(insert_last(list2,-10));
	ASSERT_TRUE( ( list2->tail )-> data == -10);
}

TEST(LinkedListTest,InsertingLastNode_NullList){

	ASSERT_TRUE(insert_last(nullptr, 20) == -1);

}

TEST(LinkedListTest,InsertingLastNode_LastAsFirst){
	ListPtr list2;
	list2 = create_list();	

	ASSERT_TRUE(insert_last(list2,-10));
	ASSERT_TRUE( ( list2->tail )-> data == -10);
	ASSERT_TRUE( ( list2->tail ) == ( list2->head ));
}

TEST(LinkedListTest,GettingNode_ValidInput){
      ListPtr list4;
      list4 = create_list();	
      insert_first(list4,10);
      insert_first(list4,20);
      insert_first(list4,30);
      
      ASSERT_TRUE( ( ( get_node(list4,0) ) -> data ) == 30);
      ASSERT_TRUE( ( ( get_node(list4,1) ) -> data ) == 20);
      ASSERT_TRUE( ( ( get_node(list4,2) ) -> data ) == 10);
}

TEST(LinkedListTest,GettingNode_NullList){
      EXPECT_EQ(  get_node(nullptr,0) ,  nullptr);
}

TEST(LinkedListTest,GettingNode_NegativeIndex){
     	ListPtr list5 = create_list(); 
	EXPECT_EQ(  get_node(list5,-10) , nullptr);
}

TEST(LinkedListTest,GettingNode_EmptyNode){
      	ListPtr list5;
      	list5 = create_list();	
      	insert_first(list5,10);
	
	EXPECT_EQ(  get_node(list5,1) ,  nullptr);
}

TEST(LinkedListTest,DeletingFirstNode_ValidInputs){
        ListPtr list;
     	list = create_list();	
      	insert_first(list,30);
      	insert_first(list,10);
	
	ASSERT_TRUE( remove_first(list) == 1 );
	ASSERT_TRUE( ( list->head )-> data == 30 );
}

TEST(LinkedListTest,DeletingFirstNode_EmptyList){
        ListPtr list;
     	list = create_list();	
	
	ASSERT_TRUE( remove_first(list) == -1 );
}

TEST(LinkedListTest,DeletingFirstNode_NullList){
	ASSERT_TRUE( remove_first(NULL) == -1 );
}

TEST(LinkedListTest,DeletingLastNode_ValidInputs){
        ListPtr list;
     	list = create_list();	
      	insert_first(list,30);
      	insert_first(list,10);
	
	ASSERT_TRUE( remove_last(list) == 1 );
	ASSERT_TRUE( ( list->head )-> data == 10 );
}

TEST(LinkedListTest,DeletingLastNode_EmptyList){
        ListPtr list;
     	list = create_list();	
	
	ASSERT_TRUE( remove_last(list) == -1 );
}

TEST(LinkedListTest,DeletingLastNode_NullList){
	ASSERT_TRUE( remove_last(NULL) == -1 );
}
