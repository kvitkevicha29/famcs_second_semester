#pragma once
#include "Queue.h"
#include <iostream>
using namespace std;

class CQueue : public Queue 
{
private:
	Node* Mas;
	unsigned first, last, SIZE;
	void Erase();
	void Clone(const Queue&);
public:
	//CQueue();
	CQueue(unsigned cpty = 100);
	CQueue(const CQueue&);
	virtual ~CQueue(); // только сообщение о вызове
	virtual void Push(Node AInfo);
	virtual bool Pop();
	virtual Node GetFirst() const;
	virtual bool IsEmpty()const;
	virtual unsigned GetSize() const;
	virtual Node& operator [] (unsigned);
	virtual CQueue& operator = (const CQueue&);
	virtual const Node& GetByIndex(unsigned) const;
	virtual void Browse(void ItemWork(Node)) const;
	virtual void Browse(void ItemWork(Node&));
};