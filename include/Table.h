#pragma once
#include "stdio.h"
#include <iostream>

template <class T>
class pair {
	size_t key;
	T value;
};

template <class T>
class TableInterface {
public:
	virtual void insert(size_t key_, const T& elem) = 0;
	virtual void erase(size_t key_) = 0;
	virtual pair find(size_t key_) = 0;
	virtual size_t getsize() = 0;
	virtual bool IsEmpty() = 0;
};



/*
template<class T, class CellType = std::pair<size_t, T>>
class TableByArray: public TableInterface<T> {
protected:
	std::vector<CellType> storage;
	size_t size;
public:

	TableByArray() { 
		storage = std::vector<CellType>();
		size = 0;
	}

	TableByArray(const TableByArray& tab) {
		storage = tab.storage;
		size = tab.size;
	}

	size_t getSize() override {
		return size;
	}

	void clear() override {
	    storage.clear();
		size = 0;
	}

	bool isEmpty() override {
		return (size == 0);
	}
};

template<class T>
class OrderedTable: public TableByArray<T> {
public:
	OrderedTable(): TableByArray() {};
	OrderedTable(const TableByArray& tab): TableByArray(tab) {};
	bool insert(size_t key, const T& elem) override {
		bool successful_insert = false;
		std::pair<size_t, T> pr = std::make_pair(key, elem);
		if (!isEmpty())
		{
			auto low = std::lower_bound(storage.begin(), storage.end(), pr);
			if (low != storage.end())
			{
				if (low->first != key) {
					storage.insert(low, pr);
					++size;
					successful_insert = true;
				}
			}
		}
		else {
			storage.push_back(pr);
			++size;
			successful_insert = true;
		}
		return successful_insert;
	}
	bool erase(size_t key) {
		bool successful_deletion = false;
		std::pair<size_t, T> pr = std::make_pair(key, T());
		auto low = std::lower_bound(storage.begin(), storage.end(), pr);
		if (low != storage.end())
		{
			if (low->first == key)
			{
				storage.erase(low);
				--size;
				successful_deletion = true;
			}
		}
		return successful_deletion;
	}
	std::pair<size_t, T> find(size_t key) override {
		std::pair<size_t, T> pr = std::make_pair(key, T());
		std::pair<size_t, T> res;
		auto low = std::lower_bound(storage.begin(), storage.end(), pr);
		if (low != storage.end())
		{
			if (low->first == key) {
				res = std::make_pair(key, low->second);
			}
			else
				throw std::logic_error("Field with this key was not found");
		}
		else
			throw std::logic_error("Field with this key was not found");
		return res;
	}
};

template<class T>
class UnorderedTable: public TableByArray<T> {
private:
    size_t get_index(size_t key) {
		size_t index = -1;
		for (size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				index = i;
				break;
			}
		}
		return index;	
    }
public:
    UnorderedTable() : TableByArray() {};
    UnorderedTable(const TableByArray& tab) : TableByArray(tab) {};
	bool insert(size_t key, const T& elem) override {
		bool successful_insert;
		if (get_index(key) != -1)
			successful_insert = false;
		else {
			storage.push_back(std::make_pair(key, elem));
			++size;
			successful_insert = true;
		}
		return successful_insert;
	}
    bool erase(size_t key) override {
		bool successful_deletion = false;
		for (size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				storage[i] = storage[size - 1];
				storage.pop_back();
				--size;
				successful_deletion = true;
				break;
			}
		}
		return successful_deletion;
	}
	std::pair<size_t, T> find(size_t key) override {
		bool successful_search = false;
		std::pair<size_t, T> res;
		for (size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				successful_search = true;
				res = std::make_pair(key, storage[i].second);
				break;
			}
		}
		if (!successful_search)
		    throw std::logic_error("Field with this key was not found");
		return res;
	}
};*/