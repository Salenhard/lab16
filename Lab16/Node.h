#pragma once
template <typename T>
class Node							// шаблонный класс узла списка
{
private:
	Node* next;						// указатель на след. узел

public:
	T data;							// данные узла списка
	// конструктор
	Node(const T& item, Node<T>* ptrnext = nullptr);

	// методы модификации списка
	void InsertAfter(Node<T>* p);
	Node<T>* DeleteAfter();
	
	// получение адреса следующего узла
	Node<T>* NextNode() const;
};

template <class T>
Node<T>::Node(const T& item, Node<T>* ptrnext) : data{ item }, next{ ptrnext } {};

// возвратить заркытый член next
template <class T>
Node<T>* Node<T>::NextNode() const {
	return next;
}

// вставить узел p после текущего узла 
template <class T>
void Node<T>::InsertAfter(Node<T>* p) {
	// p указывает на следующий за текущим узел
	// а текущий узел - на p.
	p->next = next;
	next = p;
}

// удалить узел, следующий за текущим, и возвратить его адрес
template <class T>
Node<T>* Node<T>::DeleteAfter()
{
	// сохранить адрес удаляемого узла
	Node<T>* tempPtr = next;

	// если нет следующего узла, возвратить NULL
	if (next == nullptr)
		return nullptr;

	// текущий узел указывает на узел, следующий за tempPtr.
	next = tempPtr->next;
	
	// возвратить указатель на несвязанный узел
	return tempPtr;
}