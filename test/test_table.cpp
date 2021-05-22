#include "stdio.h"
#include "Table.h"
#include "iostream"
#include <string>
#include <vector>

#include <gtest.h>


TEST(UnordTable, can_create_empty_class) {
	ASSERT_NO_THROW(UnorderedTable<int> Tab);
}

TEST(UnordTable, can_insert_1) {
	UnorderedTable<int> Tab;
	ASSERT_NO_THROW(Tab.insert(1, 4));
}

TEST(UnordTable, can_insert_2) {
	UnorderedTable<int> Tab;
	int a = 5;
	ASSERT_NO_THROW(Tab.insert(1, a));
}

TEST(UnordTable, cant_insert_existing_elem) {
	UnorderedTable<int> Tab;
	Tab.insert(1, 4);
	ASSERT_ANY_THROW(Tab.insert(1, 3));
}

TEST(UnordTable, can_delete) {
	UnorderedTable<int> Tab;
	Tab.insert(1, 5);
	ASSERT_NO_THROW(Tab.erase(1));
}

TEST(UnordTable, can_delete_properly) {
	UnorderedTable<int> Tab;
	Tab.push(1, 5);
	Tab.push(2, 6);
	Tab.push(3, 7);
	Tab.erase(1);
	//try {
	//	Tab.find(3); }
	//catch (const char* message) {
	//	std::cout << message << std::endl; }
	EXPECT_EQ(Tab.find(3).second, 7);
}


TEST(OrderedTble, can_create_empty_class) {
	ASSERT_NO_THROW(OrderedTable<int> Tab);
}

TEST(OrderedTable, can_insert_without_crash) {
	OrderedTable<int> Tab;
	ASSERT_NO_THROW(Tab.insert(3, 7));
}

TEST(OrderedTable, cant_insert_existing_key) {
	OrderedTable<int> Tab;
	Tab.insert(3, 6);
	ASSERT_ANY_THROW(Tab.insert(3, 7));
}

TEST(OrderedTable, can_insert_properly) {
	OrderedTable<int> Tab;
	Tab.insert(3, 7);
	Tab.insert(2, 8);
	Tab.insert(4, 5);
	Tab.insert(1, 2);
	Tab.print();
	//Tab.fileprint();
}

TEST(OrderedTable, can_find_1) {
	OrderedTable<int> Tab;
	Tab.insert(3, 7);
	Tab.insert(2, 8);
	Tab.insert(4, 5);
	Tab.insert(1, 2);
	ASSERT_NO_THROW(Tab.find(2));
}

TEST(OrderedTable, can_find_2) {
	OrderedTable<int> Tab;
	Tab.insert(3, 7);
	Tab.insert(2, 8);
	Tab.insert(4, 5);
	Tab.insert(1, 2);
	std::pair<size_t, int> temp = Tab.find(2);
	EXPECT_EQ(temp.second, 8);
}

TEST(OrderedTable, can_delete_and_insert_consistently) {
	OrderedTable<int> Tab;
	Tab.insert(3, 7);
	Tab.insert(2, 8);
	Tab.insert(4, 5);
	Tab.insert(1, 2);
	Tab.print();
	Tab.erase(2);
	std::cout << "After deletion of key 2:" << std::endl;
	Tab.print();
	std::cout << "After adding key 10 and 2:" << std::endl;
	Tab.insert(2, 2);
	Tab.insert(10, 2);
	Tab.print();
	EXPECT_EQ(Tab.getsize(), 5);
	
}


TEST(HashTable, can_create_empty_class) {
	ASSERT_NO_THROW(HashTable<int> Tab);
}

TEST(HashTable, can_insert_1) {
	HashTable<double> Tab;
	ASSERT_NO_THROW(Tab.insert(1.6));
}

TEST(HashTable, can_insert_2) {
	HashTable<int> Tab;
	ASSERT_NO_THROW(Tab.insert(55));
}

TEST(HashTable, can_insert_3) {
	HashTable<int> Tab;
	Tab.insert(55);
	Tab.insert(55);
	ASSERT_NO_THROW(Tab.insert(55));
}

TEST(HashTable, can_find_1) {
	HashTable<int> Tab;
	Tab.insert(3);
	Tab.insert(1);
	Tab.insert(3);
	Tab.insert(1);

	EXPECT_EQ(Tab.find(3), true);
}

TEST(HashTable, can_find_2) {
	HashTable<int> Tab;
	Tab.insert(3);
	Tab.insert(1);
	Tab.insert(3);
	Tab.insert(1);

	EXPECT_EQ(Tab.find(2), false);
}

TEST(HashTable, can_erase_1) {
	HashTable<int> Tab;
	Tab.insert(3);
	Tab.insert(1);
	Tab.insert(3);
	Tab.insert(1);

	EXPECT_EQ(Tab.erase(3), true);
}

TEST(HashTable, can_erase_2) {
	HashTable<int> Tab;
	Tab.insert(3);
	Tab.insert(1);
	Tab.insert(3);
	Tab.insert(1);

	EXPECT_EQ(Tab.erase(2), false);
}
