#pragma once
#include "HashTable.h"
#include "Iterator.h"

template<class T>
class HashTableIterator : public Iterator<T>
{
private:
	// ��������� �������, ���������� ������
	HashTable<T>* hashTable;

	// ������ �������� ���������������� �����
	// � ��������� �� ��������� ������
	int currentBucket;
	LinkedList<T>* currBucketPtr;

	// ������� ��� ���������� ������ Next
	void SearchNextNode(int cb);

public:

	// �����������
	HashTableIterator(HashTable<T>& hf);

	// ������� ������ ���������
	virtual void Next(void);
	virtual void Reset(void);
	virtual T& Data(void);

	// ����������� �������� ��� ������������ ������ �������
	void SetList(HashTable<T>& lst);
};


template <class T>
void HashTableIterator<T>::SearchNextNode(int cb) {
	currentBucket = -1;
	
	// ���� ������ cb ������ ������� �������, ���������� �����
	if (cb > hashTable->numBuckets)
		return;

	// ����� ������, ������� � �������� ������ �� ����� �������,
	// �������� ���� � �������� ������� �������� ������
	for (int i = cb; i < hashTable->numBuckets; i++) {
		if (!hashTable->buckets[i].ListEmpty()) {
			// ����� �� ��� ���������, ���������� currentBucket ������ 1
			// � � currBucketPtr ��������� ����� ������ �������� ������
			currBucketPtr = &hashTable->buckets[i];
			currBucketPtr->Reset();
			currentBucket = i;
			return;
		}
	}
}

template<class T>
void HashTableIterator<T>::Next() {
	// ������������ � ���������� ���� �������� ������
	currBucketPtr->Next();

	// �� ���������� ����� ������ ������� SearchNextNode
	// ��� ������ ���������� ��������� ����� � �������
	if (currBucketPtr->EndOfList())
		SearchNextNode(++currentBucket);

	// ���������� ������ iterationComlpete, ���� �������� �������
	// ������ ���
	this->iterationComplete = currentBucket == -1;
}


template<class T>
T& HashTableIterator<T>::Data() {
	if (currBucketPtr == nullptr) {
		cout << "Data: ������ ��������� ������";
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

// �����������. �������������� ������� ����� � ����� HashTable
// SearchNextNode �������������� ������ �������� ���� � �������
template<class T>
HashTableIterator<T>::HashTableIterator(HashTable<T>& hf) : Iterator<T>(), hashTable{ &hf } {
	SearchNextNode(0);
};
