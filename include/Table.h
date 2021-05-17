#pragma once
#include "stdio.h"
#include "fstream"
#include <iostream>
#include <vector>


template <class T>
class TableInterface {
public:
	virtual bool insert(size_t key_, const T& elem) = 0;
	virtual bool erase(size_t key_) = 0;
	virtual std::pair<size_t, T> find(size_t key_) = 0;
	virtual size_t getsize() = 0;
	virtual bool IsEmpty() = 0;
	virtual void print() = 0;
	virtual void fileprint() = 0;
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

	void print() {
		for (auto& s : data) {
			std::cout << "(" << s.first << ", " << s.second << ")" << std::endl;
		}
	}

	void fileprint() {
		std::ofstream file;
		file.open("D:/Daniil/Univer/A&DS/file.csv");
		for (auto& s : data) {
			file << "(" << s.first << ", " << s.second << ")" << std::endl;
		}
		file.close();
	}
};


template<class T>
class UnorderedTable : public TableByArray<T> {
public:
	UnorderedTable() : TableByArray() {};

	UnorderedTable(const TableByArray& tab) : TableByArray(tab) {};

	bool insert(size_t key, const T& elem){
		for (auto& s : data) {
			if (s.first == key)
				throw "Trying to insert already existing key";
		}
	
		std::pair<size_t, T> Pair = std::make_pair(key, elem);
		data.push_back(Pair);
		size++;

		return true;
	}

	bool erase(size_t key_) {
		bool successful_deletion = false;
		for (int i = 0; i < size; i++) {
			if (data[i].first == key_) {
				std::swap(data[i], data[size - 1]);
				data.pop_back();
				size--;
				successful_deletion = true;
				break;
			}
		}
		return successful_deletion;
	}

	std::pair<size_t, T> find(size_t key) {
		for (auto iter = data.begin(); iter != data.end(); iter++)
		{
			if (iter->first == key) {
				return std::make_pair(key, iter->second);
			}
		}
		throw "Field with this key was not found";
		
	}

	size_t getsize() { return size; };

	bool IsEmpty() { return size == 0;  };
};

template<class T>
class OrderedTable : public TableByArray<T> {
public:
	OrderedTable() : TableByArray() {};

	OrderedTable(const TableByArray& tab) : TableByArray(tab) {};

	bool insert(size_t key, const T& elem) {
		for (auto& s : data) {				
			if (s.first == key)
				throw "Trying to insert already existing key";
		}
		std::pair<size_t, T> Pair = std::make_pair(key, elem);
		auto low = lower_bound(data.begin(), data.end(), Pair);	
		data.insert(low, Pair);	
		size++;
		return true;
	};

	bool erase(size_t key_) {
		bool successful_deletion = false;
		int i = 0;
		for (i; i < size; i++) {
			if (data[i].first == key_) {
				successful_deletion = true;
				break;
			}
		}
		if (successful_deletion) {
			for (; i < size - 1; i++)
				data[i] = data[i + 1];
			data.pop_back();
			size--;
		}
		else throw "Cant delete not existing element";	
		
		return successful_deletion;
	};

	std::pair<size_t, T> find(size_t key_) {
		int left = -1, right = size, temp;
		while (left < right - 1) {
			temp = (left + right) / 2;
			if (data[temp].first < key_)
				left = temp;
			else
				right = temp;
		}
		if (data[right].first == key_) return data[right];
		else throw "Field with this key was not found";
	};

	size_t getsize() { return size; };

	bool IsEmpty() { return size == 0; };
};





