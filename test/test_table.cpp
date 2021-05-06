#include "stdio.h"
#include "Table.h"
#include "iostream"
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
