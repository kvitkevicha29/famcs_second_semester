#include "pch.h"
#include "CQueue.h"
#include <iostream>
using namespace std;

CQueue& CQueue::operator = (const CQueue& Q) 
{
	if (typeid(Q) != typeid(*this))
		throw My_exception("Different types");

	if (this != &Q) 
	{
		Erase();
		Clone(Q);
	}
	return *this;
}
void CQueue::Erase()
{
	SIZE = 0;
	first = 0;
	last = 0;
	delete[] Mas;
}

void CQueue::Clone(const Queue& q)
{
	if (typeid(q) != typeid(*this))
		throw My_exception("Different types");
	const CQueue* Qu = (const CQueue*)&q;
	SIZE = Qu->SIZE;
	first = Qu->first;
	last = Qu->last;
	Mas = new InfoType[SIZE];
	for (int i = 0; i < SIZE; i++)
		Mas[i] = Qu->Mas[i];

}

CQueue::CQueue(unsigned cpty)
{
	last = 0;
	first = 0;
	Mas = new InfoType[cpty];
	SIZE = cpty;
}

CQueue::CQueue(const CQueue& q) 
{
	Clone(q);
}

CQueue::~CQueue()
{
	cout << "CQueue деструктор.\n";
}

void CQueue::Push(InfoType AInfo) 
{
	if (last + 1 == first || (last + 1 == SIZE && !first)) 
	{
		throw My_exception("Queue is full");
	}
	if (last == SIZE) last = 0;
	Mas[last] = AInfo;
	last++;
}

bool CQueue::Pop() 
{
	if (this->IsEmpty())
	{
		return false;;
	}
	first++;
	if (first == SIZE) first = 0;
	return true;
}

InfoType CQueue::GetFirst() const
{
	if (this->IsEmpty())
		throw My_exception("Queue is empty");
	return Mas[first];
}

bool CQueue::IsEmpty()const 
{
	if (first == last)
		return true;
	return false;
}

unsigned CQueue::GetSize() const 
{
	if (last >= first)
		return last - first;
	return(last + SIZE - first);
}

InfoType& CQueue::operator [] (unsigned u) 
{
	if (u >= SIZE - 1)
		throw My_exception("Too big [Index]");
	if (first + u >= SIZE)
		return Mas[first + u - SIZE];
	return Mas[first + u];
}

const InfoType& CQueue::GetByIndex(unsigned u) const 
{
	if (u >= SIZE - 1)
		throw My_exception("Too big Index");
	if (first + u >= SIZE)
		return Mas[first + u - SIZE];
	return Mas[first + u];
}

void CQueue::Browse(void ItemWork(InfoType)) const
{
	if (this->IsEmpty())
		throw My_exception("Queue is empty");
	if (last > first)
		for (unsigned i = first; i < last; i++)
			ItemWork(Mas[i]);
	else
	{
		for (unsigned i = first; i < SIZE; i++)
			ItemWork(Mas[i]);
		for (unsigned i = 0; i < last; i++)
			ItemWork(Mas[i]);
	}

}

void CQueue::Browse(void ItemWork(InfoType&)) 
{
	if (this->IsEmpty())
		throw My_exception("Queue is empty");
	if (last > first)
		for (unsigned i = first; i < last; i++)
			ItemWork(Mas[i]);
	else
	{
		for (unsigned i = first; i < SIZE; i++)
			ItemWork(Mas[i]);
		for (unsigned i = 0; i < last; i++)
			ItemWork(Mas[i]);
	}
}