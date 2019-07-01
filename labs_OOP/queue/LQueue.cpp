#include "pch.h"
#include "LQueue.h"
#include <iostream>
using namespace std;

LQueue& LQueue::operator = (const LQueue& Q) 
{
	if (typeid(Q) != typeid(*this))
		throw My_exception("Different types");

	if (this != &Q) {
		Erase();
		Clone(Q);
	}
	return *this;
}

void LQueue::Erase() 
{
	while (!this->IsEmpty())
		this->Pop();
}

void LQueue::Clone(const Queue& Q)
{
	if (typeid(Q) != typeid(*this))
		throw My_exception("Different types");
	const LQueue* Qu = (const LQueue*)&Q;
	front = NULL;
	rear = NULL;
	size = 0;
	QItem* tmp = Qu->front;
	for (int i = 0; i < Qu->size; ++i)
	{
		Push(tmp->info);
		tmp = tmp->next;
		size++;
	}

}

LQueue::LQueue(const LQueue& Q) 
{
	front = NULL;
	rear = NULL;
	size = 0;
	Clone(Q);
}
LQueue::~LQueue()
{
	cout << "LQueue deleted.\n";
}
void LQueue::Push(InfoType AInfo) 
{
	QItem* e = new QItem(AInfo);
	if (size > 0) {
		rear->next = e;
	}
	else {
		front = e;
		front->next = rear;
	}
	rear = e;
	++size;
}

bool LQueue::Pop() 
{
	if (this->IsEmpty())
		return false;
	QItem* tmp = front;
	front = front->next;
	delete tmp;
	--size;
	if (size == 0)
		rear = NULL;
	return true;

}

InfoType LQueue::GetFirst() const 
{
	if (this->IsEmpty())
		throw "Queue is empty";
	return front->info;

}

bool LQueue::IsEmpty()const 
{
	return (!front);
}

unsigned LQueue::GetSize() const 
{
	size_t cnt = 0u;
	const QItem* iter = front;
	do {
		cnt++;
		iter = iter->next;
	} while (iter != rear->next);
	return cnt;
}

InfoType& LQueue::operator [] (unsigned u)
{
	if (u > size)
		throw My_exception("Too big [index]\n");
	size_t cnt = 0u;
	QItem* iter = front;
	while (cnt != u)
	{
		cnt++;
		iter = iter->next;
	}
	return iter->info;

}

const InfoType& LQueue::GetByIndex(unsigned u) const 
{
	if (u > size)
		throw My_exception("Too big index\n");
	size_t cnt = 0u;
	QItem* iter = front;
	while (cnt != u)
	{
		cnt++;
		iter = iter->next;
	}
	return iter->info;
}

void LQueue::Browse(void ItemWork(InfoType)) const 
{
	if (this->IsEmpty())
		throw My_exception("Queue is empty");
	QItem* temp = front;
	while (temp != rear)
	{
		ItemWork(temp->info);
		temp = temp->next;
	}
	ItemWork(temp->info);
}
void LQueue::Browse(void ItemWork(InfoType&))
{
	if (this->IsEmpty())
		throw My_exception("Queue is empty");
	QItem* temp = front;
	while (temp != rear)
	{
		ItemWork(temp->info);
		temp = temp->next;
	}
	ItemWork(temp->info);
}