#pragma once
#include "Iterator.h"
#include "List.h"
#include "Array.h"
#include "LinkedList.h"
#include <iostream>
template<class T>
class HashTableIterator;

template <class T>
class HashTable : public List<T>
{
protected:
	// число болков; предаставл€ют размер таблицы
	int numBuckets;

	//хеш-таблица есть массив св€занных списков
	Array<LinkedList<T>> buckets;

	// хеш функци€ и адрес элемента данных
	// к которому обращались последний раз
	unsigned long (*hf)(T);
	T* current;

public:

	// конструтор копировани€
	HashTable(HashTable<T> &hashTable) {
		numBuckets = hashTable.numBuckets;
		buckets = hashTable.buckets;
		hf = hashTable.hf;
	}

	// конструктор с параметрами, включающими
	// размер таблицы и хеш-функцию
	HashTable(int nbucket, unsigned long (*hashf)(T));
	// методы обработки списков
	virtual void Insert(const T& key);
	virtual int Find(const T& key);
	virtual void Delete(const T& key);
	virtual void ClearList();
	void Update(const T& key);

	//дружественный итератор, имеющий доступ к
	// данным-членам

	friend class HashTableIterator<T>;
};

template<class T>
void HashTable<T>::Insert(const T& key) {

	// hashval - индекс блока (св€занного списка)
	int hashval = int(hf(key) % numBuckets);

	// lst - псведоним дл€ buckets[hashval].
	// помогает обойтись без индексов
	LinkedList<T>& lst = buckets[hashval];
	if (!lst.ListEmpty() ) {
		for (lst.Reset(); !lst.EndOfList(); lst.Next())
			// если ключ совпал, обновить данные и выйти
			if (lst.Data() == key)
			{
				current = &lst.Data();
				return;
			}
	}
	lst.InsertRear(key);
	current = &lst.Data();
}

template <class T>
int HashTable<T>::Find(const T& key)
	{
	// вычислить значение хеш-функции и установить lst
	// на начало соотвествующего св€занного списка
	int hashval = int(hf(key) % numBuckets);
	LinkedList<T>& lst = buckets[hashval];

	// просматривать узлы св€заного списка в поиска key
	for (lst.Reset(); !lst.EndOfList(); lst.Next())
		if (lst.Data() == key)
		{
			current = &lst.Data();
			return 1;					// вернуть true
		}
	return 0;						// иначе вернуть false
}

template <class T>
void HashTable<T>::Delete(const T& key)
{
	int hashval = int(hf(key) % numBuckets);
	LinkedList<T>& lst = buckets[hashval];
	lst.Reset();
	while (!lst.EndOfList()) {
		if (lst.Data() == key) {
			lst.DeleteAt();
			return;
		}
		else
		lst.Next();
	}
	cout << "≈лемента нет в списке!";
}

// очищение списка по ключу одного из элементов списка
template<class T>
void HashTable<T>::ClearList() {
	int hashval = int(hf(*current) % numBuckets);
	LinkedList<T>& lst = buckets[hashval];		//лист блока
	lst.ClearList();			// очищение листа
}

template <class T>
void HashTable<T>::Update(const T& key) {
	int hashval = int(hf(key) % numBuckets);		// индекс блока
	LinkedList<T>& lst = buckets[hashval];		//лист блока
	for (lst.Reset(0); !lst.EndOfList(); lst.Next())
	{
		if (lst.Data() == key)
		{
			current = &lst.Data();
			lst.Data() = key;
			return;
		}
	}
}

template<class T>
HashTable<T>::HashTable(int nbucket, unsigned long (*hashf)(T)) : List<T>(), numBuckets{ nbucket }, hf{ hashf }, buckets{nbucket}{
	current = NULL;
}
