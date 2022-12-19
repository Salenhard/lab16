#pragma once
#include "HashTable.h"
#include "Iterator.h"

template<class T>
class HashTableIterator : public Iterator<T>
{
private:
	// указатель таблицы, подлежащий обходу
	HashTable<T>* hashTable;

	// индекс текущего просматриваемого блока
	// и указатель на связанный список
	int currentBucket;
	LinkedList<T>* currBucketPtr;

	// утилита для реализации метода Next
	void SearchNextNode(int cb);

public:

	// конструктор
	HashTableIterator(HashTable<T>& hf);

	// базоыве методы итератора
	virtual void Next(void);
	virtual void Reset(void);
	virtual T& Data(void);

	// подготовить итератор для сканирования другой таблицы
	void SetList(HashTable<T>& lst);
};


template <class T>
void HashTableIterator<T>::SearchNextNode(int cb) {
	currentBucket = -1;
	
	// если индекс cb больше размера таблицы, прекратить поиск
	if (cb > hashTable->numBuckets)
		return;

	// иначе искать, начиная с текущего списка до конца таблицы,
	// непустой блок и обновить частные элементы данных
	for (int i = cb; i < hashTable->numBuckets; i++) {
		if (!hashTable->buckets[i].ListEmpty()) {
			// перед те как вернуться, установить currentBucket равным 1
			// и в currBucketPtr поместить адрес нового непутого списка
			currBucketPtr = &hashTable->buckets[i];
			currBucketPtr->Reset();
			currentBucket = i;
			return;
		}
	}
}

template<class T>
void HashTableIterator<T>::Next() {
	// продвинуться к следующему узлу текущего списка
	currBucketPtr->Next();

	// по достижению конца списка вызвать SearchNextNode
	// для поиска следующего непустого блока в таблице
	if (currBucketPtr->EndOfList())
		SearchNextNode(++currentBucket);

	// установить флажок iterationComlpete, если непустых списков
	// больше нет
	this->iterationComplete = currentBucket == -1;
}


template<class T>
T& HashTableIterator<T>::Data() {
	if (currBucketPtr == nullptr) {
		cout << "Data: Ошибка указатель пустой";
		exit(1);
	}
	return currBucketPtr->Data();
}

template<class T>
void HashTableIterator<T>::Reset() {
	SearchNextNode(0);
}

template<class T>
void HashTableIterator<T>::SetList(HashTable<T>& lst) {
	this->hashTable = lst;
}

// конструктор. инициализирует базовый класс и класс HashTable
// SearchNextNode идентифицирует первый непустой блок в таблице
template<class T>
HashTableIterator<T>::HashTableIterator(HashTable<T>& hf) : Iterator<T>(), hashTable{ &hf } {
	SearchNextNode(0);
};
