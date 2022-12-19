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
	// ����� ������; ������������� ������ �������
	int numBuckets;

	//���-������� ���� ������ ��������� �������
	Array<LinkedList<T>> buckets;

	// ��� ������� � ����� �������� ������
	// � �������� ���������� ��������� ���
	unsigned long (*hf)(T);
	T* current;

public:

	// ���������� �����������
	HashTable(HashTable<T> &hashTable) {
		numBuckets = hashTable.numBuckets;
		buckets = hashTable.buckets;
		hf = hashTable.hf;
	}

	// ����������� � �����������, �����������
	// ������ ������� � ���-�������
	HashTable(int nbucket, unsigned long (*hashf)(T));
	// ������ ��������� �������
	virtual void Insert(const T& key);
	virtual int Find(const T& key);
	virtual void Delete(const T& key);
	virtual void ClearList();
	void Update(const T& key);

	//������������� ��������, ������� ������ �
	// ������-������

	friend class HashTableIterator<T>;
};

template<class T>
void HashTable<T>::Insert(const T& key) {

	// hashval - ������ ����� (���������� ������)
	int hashval = int(hf(key) % numBuckets);

	// lst - ��������� ��� buckets[hashval].
	// �������� �������� ��� ��������
	LinkedList<T>& lst = buckets[hashval];
	if (!lst.ListEmpty() ) {
		for (lst.Reset(); !lst.EndOfList(); lst.Next())
			// ���� ���� ������, �������� ������ � �����
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
	// ��������� �������� ���-������� � ���������� lst
	// �� ������ ��������������� ���������� ������
	int hashval = int(hf(key) % numBuckets);
	LinkedList<T>& lst = buckets[hashval];

	// ������������� ���� ��������� ������ � ������ key
	for (lst.Reset(); !lst.EndOfList(); lst.Next())
		if (lst.Data() == key)
		{
			current = &lst.Data();
			return 1;					// ������� true
		}
	return 0;						// ����� ������� false
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
	cout << "�������� ��� � ������!";
}

// �������� ������ �� ����� ������ �� ��������� ������
template<class T>
void HashTable<T>::ClearList() {
	int hashval = int(hf(*current) % numBuckets);
	LinkedList<T>& lst = buckets[hashval];		//���� �����
	lst.ClearList();			// �������� �����
}

template <class T>
void HashTable<T>::Update(const T& key) {
	int hashval = int(hf(key) % numBuckets);		// ������ �����
	LinkedList<T>& lst = buckets[hashval];		//���� �����
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
