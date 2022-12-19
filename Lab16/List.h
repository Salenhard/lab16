#pragma once
template <class T> 
class List	// абстрактный класс
{
protected:
	// число элементов списка, обновляемое производным классом
	int size;
public:
	// конструктор 
	List(void) {
		size = 0;
	};

	virtual int ListSize(void) const {
		return size;
	};

	virtual int ListEmpty(void) const {
		return size == 0;
	};

	virtual int Find(const T& item) = 0;
	virtual void Insert(const T& item) = 0;
	virtual void Delete(const T& item) = 0;
	virtual void ClearList(void) = 0;
};