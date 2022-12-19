#pragma once
template<class T>
class Iterator
{	
protected:
	int iterationComplete;
public:
	Iterator() : iterationComplete{ 0 }
	{}
	virtual void Next() = 0;
	virtual void Reset() = 0;
	virtual T& Data() = 0;
	virtual int EndOfList() const {
		return iterationComplete;
	}
};

