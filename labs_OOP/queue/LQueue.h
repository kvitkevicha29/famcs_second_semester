#pragma once
#include "Queue.h"
#include <iostream>
using namespace std;

class LQueue : public Queue {
private:
	struct QItem {
		Node info;
		QItem* next;
		QItem(Node Ainfo) : info(Ainfo), next(NULL) {}
	};
	QItem *front, *rear;
	unsigned size;
	virtual void Erase();
	virtual void Clone(const Queue&);
public:
	LQueue() : front(NULL), rear(NULL), size(0) {};
	LQueue(const LQueue&);
	virtual ~LQueue(); // только сообщение о вызове
	virtual void Push(Node AInfo);
	virtual LQueue& operator = (const LQueue&);
	virtual bool Pop();
	virtual Node GetFirst() const;
	virtual bool IsEmpty()const;
	virtual unsigned GetSize() const;
	virtual Node& operator [] (unsigned);
	virtual const Node& GetByIndex(unsigned) const;
	virtual void Browse(void ItemWork(Node)) const;
	virtual void Browse(void ItemWork(Node&));
};
