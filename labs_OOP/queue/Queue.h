#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>

using namespace std;

typedef int Node;
class My_exception : public exception
{
private:
	char* s;
	char* t;
	void operator =(My_exception& e) {};
public:
	My_exception(const char* l) { s = new char[90]; strcpy_s(s, 90, l); };
	const char* what() { t = new char[strlen(s) + 1]; strcpy_s(t, strlen(s) + 1, s); return t; };
	~My_exception() 
	{ 
		delete[] s;
		delete[] t;
	};
};

class Queue {
private:
	virtual void Erase() = 0 {};
	virtual void Clone(const Queue&) = 0 {};
public:
	Queue() {}
	Queue(const Queue&);
	virtual ~Queue();
	virtual Queue& operator = (const Queue&);
	virtual void Push(Node AInfo) = 0;
	virtual bool Pop() = 0;
	virtual Node GetFirst() const = 0;
	virtual bool IsEmpty()const = 0;
	virtual unsigned GetSize() const = 0;
	virtual Node& operator [] (unsigned) = 0;
	virtual const Node& GetByIndex(unsigned) const = 0;
	virtual void Browse(void ItemWork(Node)) const = 0;
	virtual void Browse(void ItemWork(Node&)) = 0;
};
