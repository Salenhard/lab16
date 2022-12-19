#pragma once

# include <iostream>
# include <stdlib.h>

enum ErrorType
{
	invalidArraysize, memoryAllocationError, indexOutOfRange
};

const char* errorMsg[] = {
	"Неверный разыер массива", "Ошибка выделения nамяти", "Неверный индекс: "
};

// шаблонный класс массива
template <class T>
class Array {
private:
	// динаыически выделяемый сnисок размером size
	T* alist; 
	int size;
	// метод оОработки ошибок 
	void Error(ErrorType error, int badIndex = 0) const;

public:
	// конструктор
	Array(int sz = 50);
	// конструктор копирования
	Array(const Array<T>& А);
	// деструктор
	~Array();

	// перегрузка присваивания
	Array<T>& operator = (const Array<T>& rhs); 
	// перегрузка индексного оператора
	T& operator [] (int i);
	// перегрузка указателя
	operator T* () const;

	// операции с размероы ыассива 
	int ListSize() const;		// читать size
	void Resize(int sz);		// обновлять size
};


template<class T>
void Array<T>::Error(ErrorType error, int badIndex) const {
	if (badIndex != 0) {
		std::cerr << errorMsg[error] << std::endl;
		exit(1);
	}
	else {
		std::cerr << errorMsg[error] << badIndex << std::endl;
		exit(1);
	}
}


template<class T>
Array<T>::Array(int sz) {
	// проверка на наличие параметра неверного размера 
	if (sz <= 0)
		Error(invalidArraysize);
	// nрисваивание размера и выделение памяти 
	size = sz;
	alist = new T[size];
	for (int i = 0; i < sz; i++)
		alist[i] = T();
	// убеждаемся в том, что система выделяет необходимую память,
	if (alist == nullptr) 
		Error(memoryAllocationError);
}


template<class T>
Array<T>::~Array() {
	delete[] alist;
}


template<class T>
Array<T>::Array(const Array<T>& X) {
	// получить разwер объекта Х и присвоить текущеwу объекту
	int n = X.size; 
	size = n;
	// выделить новую память дпя объекта с проверкой 
	// возможных ошибок
	alist = new T[n];
	if (alist == nullptr)
		Error(memoryAllocationError);

	// колировать элементы массива объекта Х в текупо,�й объект
	T* srcptr = X.alist;	// адрес начала X.aliзt 
	T* destptr = alist;		// адрес начала alist 
	while (n--)				// копировать список 
		*destptr++ = *srcptr++;
}


template<class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	// получить разwер объекта Х и присвоить текущеwу объекту
	int n = rhs.size;
	size = n;
	// выделить новую память дпя объекта с проверкой 
	// возможных ошибок
	alist = new T[n];
	if (alist == nullptr)
		Error(memoryAllocationError);

	// колировать элементы массива объекта Х в текупо,�й объект
	T* srcptr = rhs.alist;	// адрес начала X.aliзt 
	T* destptr = alist;		// адрес начала alist 
	while (n--)				// копировать список 
		*destptr++ = *srcptr++;
}



template<class T>
T& Array<T>::operator [] (int n) {
	// аыnолнение проверки границ массива 
	if (n < 0 && n > size - 1)
		Error(indexOutOfRange, n);
	// возвращается элемент из закрытого списка массива
	return alist[n]; 
}


template<class T>
Array<T>::operator T* () const {
	// возвращает адрес закрытого массива в текущем оОъекте
	return alist; 
}


template<class T>
int Array<T>::ListSize() const {
	return size;
}


template<class T>
void Array<T>::Resize(int sz) {
	// проверка нового размера массива; 
	// выход из программы при sz <= 0 
	if (sz <= 0)
		Error(invalidArraysize);

	// ничего не делать, если размер не изменился
	if (sz == size)
		return;

	// запросить память для нового массива и проверить ответ систеNЫ
	T* newlist = new T[sz]; 
	if (newlist == nullptr)
		Error(memoryAllocationError);

	// ооъявить n и инициализировать значением sz или зize 
	int n =(sz <= size) ? sz : size;
	// колировать n элементов массива из старой в новую память 
	T* srcptr = alist;			// адрес начала alist
	T* destptr = newlist;		// адрес начала newliзt
								
	while (n--)					// колировать список 
		*destptr++ = *srcptr++;

	// удалить старый список 
	delete[] alist;
	// переустановить alist, чтобы он указывал на newlist и обновить член класса size 
	alist = newlist;
	size = sz;

}