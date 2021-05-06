#pragma once
#include "stdio.h"
#include <iostream>
#include <vector>

template <class S> 
void Swap(S temp1, S temp2) {
	S temp3 = temp1;
	temp1 = temp2;
	temp2 = temp3;
}

template <class T>
class TableInterface {
public:
	virtual bool insert(size_t key_, const T& elem) = 0;
	virtual bool erase(size_t key_) = 0;
	virtual std::pair<size_t, T> find(size_t key_) = 0;
	virtual size_t getsize() = 0;
	virtual bool IsEmpty() = 0;
	
};

template<class T, class CellType = std::pair<size_t, T>>
class TableByArray : public TableInterface<T> {
protected:
	std::vector <std::pair<size_t, T> > data;
	size_t size;
public:

	TableByArray() {
		data = std::vector<CellType>();
		size = 0;
	}

	TableByArray(const TableByArray& table_) 
	{
		data = table_.data;
		size = table_.size;
	}

	size_t getSize()
	{
		return size;
	}

	void clear()
	{
		data.clear();
		size = 0;
	}

	bool isEmpty()
	{
		return (size == 0);
	}

	void push(size_t key_, T elem) {
		std::pair<size_t, T> Pair = std::make_pair(key_, elem);
		data.push_back(Pair);
	}

};


template<class T>
class UnorderedTable : public TableByArray<T> {
public:
	UnorderedTable() : TableByArray() {};

	UnorderedTable(const TableByArray& tab) : TableByArray(tab) {};

	bool insert(size_t key, const T& elem){
		bool successful_insertion = false;
		
		for (int i = 0; i < size; i++) {
			if (data[i].first == key) 
				throw "Trying to insert already existing key";
			else {
				std::pair<size_t, T> Pair = std::make_pair(key, elem);
				data.push_back(Pair);
				size++;
				successful_insertion = true;
			}
		}
		
		return successful_insertion;
	}

	bool erase(size_t key_) {
		bool successful_deletion = false;
		for (int i = 0; i < size; i++) {
			if (data[i].first == key_) {
				Swap(data[i], data[size - 1]);
				data.pop_back();
				size--;
				successful_deletion = true;
				break;
			}
		}
		return successful_deletion;
	}

	std::pair<size_t, T> find(size_t key) {
		std::pair<size_t, T> temp = std::make_pair(key, T());
		std::pair<size_t, T> res = std::make_pair(-1, T());
		for (auto iter = data.begin(); iter != data.end(); iter++)
		{
			if (iter->first == key) 
				res = std::make_pair(key, iter->second);
		}
		if(res.first != -1)
			return res;
		else
			throw "Field with this key was not found";
		
	}

	size_t getsize() { return size; };

	bool IsEmpty() { return size == 0;  };

	std::pair<size_t, T> get_pair(size_t index) {
		return data[index];
	}
};

