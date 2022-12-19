#pragma once

#include <iostream>
#include <stdlib.h>
#include "Node.h"

using namespace std;

template <class T>
class LinkedList
{
	template <class> friend class SeqListIterator;		//  friend class - отстой

private:
	// указатели для доступа к началу и концу списка 
	Node<T>* front, * rear;
	// используются для извлечения, вставки и удаления данных
	Node<T>* prevPtr, * currPtr;
	// число элементов в списке 
	int size;
	// положение в списке. используется методом Reset 
	int position;

	// создание узла
	Node<T>* GetNode(const T& item, Node<T>* ptrNext = nullptr);
	// очистка узла
	void FreeNode(Node<T>* pl);
	// колирует список L в текущий список 
	void CopyList(const LinkedList<T>& L);
	
public:	
	// конструктор 
	LinkedList();
	// конструктор 
	LinkedList(const LinkedList<T>& L);
	// деструктор 
	~LinkedList();

	// проверка состояния списка 
	int ListSize() const;
	// проверка на пустоту
	int ListEmpty() const;

	// установление position в положение pos
	void Reset(int pos = 0);
	// переход к след. узлу
	void Next();
	// проверка, дошли ли до конца списка
	bool EndOfList() const;
	// возврат position
	int CurrentPosition() const;

	// вставить вначале
	void InsertFront(const T& item);
	// вставить в конец
	void InsertRear(const T& item);
	// вставить на какую-то позицию
	void InsertAt(const T& item);
	void InsertAfter(const T& item);

	// методы удаления 
	T DeleteFront();
	// удаление какого-то элемента
	void DeleteAt();

	// возвратить/изменить данные 
	T& Data();
	// очистка списка 
	void ClearList();
	LinkedList<T>& operator = (const LinkedList<T>& L);
};

/*----------реализация этой шляпы----------*/

template <class T>
Node<T>* LinkedList<T>::GetNode(const T& item, Node<T>* ptrNext) {
	Node<T>* temp = new Node<T>(item, ptrNext);
	return temp;
};


template <class T>
void LinkedList<T>::FreeNode(Node<T>* pl) {
	delete pl;
};


template <class T>
void LinkedList<T>::CopyList(const LinkedList<T>& L) {
	// р - указатель на L
	Node<T>* p = L.front;
	int pos;
	// вставлять каждый элемент из L в конец текущего объекта 
	while (p != nullptr) {
		InsertRear(p->data);
		p = p->NextNode();
	}

	// выход, если список пустой
	if (position == -1)
		return;

	// nереустановить prevPtr и currPtr в новом списке
	prevPtr = nullptr;
	currPtr = front;
	for (pos = 0; pos != position; pos++) {
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
};


template <class T>
LinkedList<T>::LinkedList() {
	front = nullptr;
	rear = nullptr;
	prevPtr = nullptr;
	currPtr = nullptr;
	size = 0;
	position = 0;
};


template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L) {
	CopyList(L);
};


template <class T>
LinkedList<T>::~LinkedList(void) {
	delete front;
	delete rear;
};


// оператор присваивания
template <class T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& L) {
	CopyList(L);	//копируем список из входного
	return *this;	//возвращаем этот список
};


template <class T>
int LinkedList<T>::ListSize(void) const {
	return size;
};


template <class T>
int LinkedList<T>::ListEmpty(void) const {
	return size == 0;
};


template <class T>
void LinkedList<T>::Reset(int pos) {
	int startPos;
	// если список пустой, выход 
	if (front == nullptr)
		return;
	// если положение задано не верно, закончить программу
	if (pos < 0 || pos > size - 1)
	{
		cerr << "Reset: Неверно задано положение: " << pos << std::endl;
		return;
	}
	// установить механизм nрохоЖдения в pos
	if (pos == 0) {
		// перейти в начало списка
		prevPtr = nullptr;
		currPtr = front;
		position = 0;
	}
	else
		// nереустановить currPtr, prevPtr, и startPos 
	{
		currPtr = front->NextNode();
		prevPtr = front;
		startPos = 1;
		// передвигаться вправо до pos 
		for (position = startPos; position != pos; position++) {
			// передвинуть оба указателя прохождения вперед
			prevPtr = currPtr;
			currPtr = currPtr->NextNode();
		}
	}
};


template <class T>
void LinkedList<T>::Next(void) {
	// выйти, если конец списка или // список пустой 
	if (currPtr != nullptr) {
		// nереустановить два указателя на один узел вперед
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
};


template <class T>
bool LinkedList<T>::EndOfList() const {
	return position == size;
};


template <class T>
int LinkedList<T>::CurrentPosition(void) const {
	return position;
};


template<typename T>
void LinkedList<T>::InsertFront(const T& item) {
	Node<T>* newNode; //новый узел
	newNode = GetNode(item, front); //передаём в него значение и адрес начала
	front = newNode; //указываем на новый узел
	currPtr = front; //обновляем текущий указатель
	position = 0; //обновляем позицию
	size++; //увеличиваем размер
}


template<typename T>
void LinkedList<T>::InsertRear(const T& item) {
	Node<T>* newNode; //новый узел
	this->currPtr = this->front;
	this->position = 0;
	//если список пуст, вставить item в начало
	if (this->currPtr == nullptr)
		this->InsertFront(item);
	else {
		//найти узел с нулевым указателем
		while (this->currPtr->NextNode() != nullptr)
			this->currPtr = this->currPtr->NextNode();
		// создать узел и вставить в конец списка (после currPtr)
		newNode = this->GetNode(item, this->rear);
		this->currPtr->InsertAfter(newNode);
		this->size++;
	}
}


template <class T>
void LinkedList<T>::InsertAt(const T& item) {
	Node<T>* newNode;
	// два случая: вставка в начало или внутрь списка
	if (prevPtr == nullptr) {
		// вставка в начало списка. nоыещает также узел в пустой список 
		newNode = GetNode(item, front);
		front = newNode;
	}
	else {
		// вставка внутрь списка. помещает узел после prevPtr
		newNode = GetNode(item);
		prevPtr->InsertAfter(newNode);
	}

	// при prevPtr == rear, имеем вставку в пустой список 
	// или в хвост нелустого списка; обновляет rear и positioп
	if (prevPtr == rear) {
		rear = newNode;
		position = size;
	}
	// обновить currPtr и увеличить size
	currPtr = newNode;
	size++;
};


template<typename T>
void LinkedList<T>::InsertAfter(const T& item) {
	Node<T>* newNode; //новый узел
	if (this->front == nullptr) { //если список пуст
		//вставляем его в начало
		newNode = this->getNode(item, this->front);
		this->front = newNode;
	}
	else {
		if (this->currPtr == this->rear) { //если это хвостовой узел
			//вставляем в конец списка
			newNode = this->getNode(item, this->rear);
			this->prev_ptr->insAfter(newNode);
		}
		else {
			//вставляем после текущего
			newNode = this->getNode(item, currPtr->nextNode());
			this->currPtr->insAfter(newNode);
		}
	}
	this->next(); //смещаем позицию
	this->size++;
}


template <class T>
T LinkedList<T>::DeleteFront() {					// TODO
	Node<T>* p;
	T tmp = nullptr;

	// ошибка, если список пустой или конец списка
	if (currPtr == nullptr) {
		cerr << "Ошибка удаления!" << std::endl;
		exit(1);
	}

	if (front != nullptr)
	{
		p = front;
		front = front->NextNode();
		tmp = p->data;
	}

	FreeNode(p);
	return tmp;
};


template <class T>
void LinkedList<T>::DeleteAt(void) {
	Node<T>* p;
	// ошибка, если список пустой или конец списка
	if (currPtr == nullptr) {
		cerr << "Ошибка удаления!" << std::endl;
		exit(1);
	}

	// удалять можно только в начале и внутри списка
	if (prevPtr == nullptr) {
		// сохранить адрес начала, но не связывать его. если это - последний узел, присвоить front значение NULL 
		p = front;
		front = front->NextNode();
	}
	else {
		// не связывать внутренний узел после prevPtr, запомнить адрес 
		p = prevPtr->DeleteAfter();
	}

	// если хвост удален, адрес нового хвоста в prevPtr, // а position уыеньwается на 1 
	if (p == rear) {
		rear = prevPtr;
		position--;
	}

	// установить currPtr на последний удаленный узел. Если р - последний узел в списке, currPtr становится равным NULL 
	currPtr = p->NextNode();
	// освободить узел и уменьшить значение size
	FreeNode(p);
	size--;
};


template <class T>
T& LinkedList<T>::Data(void) {
	// ошибка, если список пустой или прохождение закончено
	if (size == 0 || currPtr == nullptr) {
		cerr << "Data: Неверная ссылка!" << std::endl;
		exit(1);
	}
	return currPtr->data;
};


template <class T>
void LinkedList<T>::ClearList() {
	Node<T>* currPosition, * nextPosition;
	currPosition = front;
	while (currPosition != nullptr) {
		// получить адрес следующего узла и удалить текущий
		nextPosition = currPosition->NextNode();
		FreeNode(currPosition);
		currPosition = nextPosition; // перейти к следующему узлу 
	}
	front = rear = nullptr;
	prevPtr = currPtr = nullptr;
	size = 0;
	position = -1;
};