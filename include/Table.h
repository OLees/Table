#pragma once
#include "stdio.h"
#include "fstream"
#include "string"
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
	virtual void fileprint() = 0; //проверка функции
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





int HashFunctionMain(const int key, int table_size)
{
    int hash_result = 0;
    for (int i = 0; i < 100; ++i)
    {
        hash_result = (key * hash_result + i) % table_size;
    }
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
}

struct HashFunction1
{
    int operator()(const int key, int table_size) const
    {
        return HashFunctionMain(table_size, table_size - 1);
    }
};

struct HashFunction2
{
    int operator()(const int key, int table_size) const
    {
        return HashFunctionMain(table_size, table_size + 1);
    }
};

template <class T, class THash1 = HashFunction1, class THash2 = HashFunction2>
class HashTable
{
    static const int default_size = 8; // начальный размер таблицы
    const double rehash_size = 0.75; //constexpr static  коэф-т, при котором произойдет увеличение таблицы
    struct Node
    {
        T value;
        bool state; //значение элемента - существует(true)/удален(false)
        Node(const T& value_) : value(value_), state(true) {}
    };
    Node** arr;   //в массиве будут хранится структуры Node*
    int size;  //сколько элементов сейчас в массиве (без учета удаленных)
    int buffer_size;  //сколько памяти выделено под хранение нашей таблицы
    int size_of_non_nullptr;  //сколько элементов сейчас в массиве (с учетом удаленных)

    void Resize()
    {
        int past_buffer_size = buffer_size;
        buffer_size *= 2;
        size_of_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(arr, arr2);
        for (int i = 0; i < past_buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state) //проверка на наличие и добавление
                insert(arr2[i]->value);
        }
        for (int i = 0; i < past_buffer_size; ++i) //удаление предыдущего массива
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void Rehash()
    {
        size_of_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(arr, arr2);
        for (int i = 0; i < buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                insert(arr2[i]->value);
        }
        for (int i = 0; i < buffer_size; ++i)//удаление предыдущего массива
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

public:
    HashTable()
    {
        buffer_size = default_size;
        size = 0;
        size_of_non_nullptr = 0;
        arr = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr[i] = nullptr;
    }
    ~HashTable()
    {
        for (int i = 0; i < buffer_size; ++i)
            if (arr[i])
                delete arr[i];
        delete[] arr;
    }
    bool insert(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())//
    {
        if (size + 1 > int(rehash_size * buffer_size))
            Resize();
        else if (size_of_non_nullptr > 2 * size)
            Rehash();  //происходит рехеш, так как слишком много удаленных элементов
        int h1 = hash1(value, buffer_size);
        int h2 = hash2(value, buffer_size);
        int i = 0;
        int first_deleted = -1; //запоминаем первый подходящий (удаленный) элемент
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->value == value && arr[h1]->state)
                return false;  //такой элемент уже есть, а значит его нельзя вставлять повторно
            if (!arr[h1]->state && first_deleted == -1)  //находим место для нового элемента
                first_deleted = h1;
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        if (first_deleted == -1)  //если не нашлось подходящего места, создаем новый Node
        {
            arr[h1] = new Node(value);
            ++size_of_non_nullptr;  //так как мы заполнили один пробел, не забываем записать, что это место теперь занято
        }
        else
        {
            arr[first_deleted]->value = value;
            arr[first_deleted]->state = true;
        }
        ++size;  //и в любом случае увеличиваем количество элементов
        return true;
    }
    bool erase(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
    {
        int h1 = hash1(value, buffer_size);
        int h2 = hash2(value, buffer_size);
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->value == value && arr[h1]->state)
            {
                arr[h1]->state = false;
                --size;
                return true;
            }
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        return false;
    }
    bool find(const T& value, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
    {
        int h1 = hash1(value, buffer_size); //значение, отвечающее за начальную позицию
        int h2 = hash2(value, buffer_size); //значение, ответственное за "шаг" по таблице
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->value == value && arr[h1]->state)
                return true;
            h1 = (h1 + h2) % buffer_size;
            ++i; //если i >=  buffer_size, значит обошлись все ячейки, именно для этого считаем i, иначе все могло бы зациклиться
        }
        return false;
    }
};