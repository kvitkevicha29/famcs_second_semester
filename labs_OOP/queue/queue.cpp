#include "pch.h"
#include <iostream>
#include "Queue.h"

#define _CRT_SECURE_NO_WARNINGS

Queue::Queue(const Queue& Q)
{
	Clone(Q);
}

Queue::~Queue()
{
	Erase();
	cout << "Queue is deleted!" << endl;
}

Queue& Queue::operator = (const Queue& Q) 
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
