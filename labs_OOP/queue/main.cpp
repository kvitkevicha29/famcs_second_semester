#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "LQueue.h"
#include "CQueue.h"
using namespace std;

void Print(Node in) 
{
	cout << in << endl;
}

int main() 
{
	try
	{
		setlocale(LC_ALL, ".1251");
		LQueue Q;
		Q.Push(7);
		Q.Push(9);
		Q.Push(509);
		Q.Push(76);
		Q.Push(3452);
		Q.Pop();
		cout << "Очередь Q:\n";
		Q.Browse(Print);

		////////
		LQueue P;
		P = Q;
		P.Push(214);
		P.Push(21345);
		cout << "Очередь P:\n";
		P.Browse(Print);
		///////////

		//
		CQueue Qu(5);
		Qu.Push(45);
		Qu.Push(99);
		Qu.Push(0);
		Qu.Pop();
		Qu.Push(10);
		Qu.Push(-23);
		cout << "очередь Qu:\n";
		Qu.Browse(Print);
		//////////
		CQueue O;
		O = Qu;

		cout << "Очередь O\n";
		O.Browse(Print);
		//////////
		cout << "----------------------------\n";
		Queue* Ql3 = new LQueue;
		Queue* Ql2 = new LQueue;
		Ql3->Push(5);
		Ql3->Push(2);
		Ql3->Push(0);
		Ql3->Push(-23);
		Ql3->Push(200);
		cout << "Очередь Ql3\n";
		Ql3->Browse(Print);
		Ql2->Push(14);
		Ql2->Push(27);
		cout << "Очеред Ql2\n";
		Ql2->Browse(Print);

		//Queue *qu2 = &Q;
		//Queue *qqq = new CQueue;
		//(*qqq) = (*qu2);

		Queue *qu99 = &Q;
		Queue *qu100 = &P;
		(*qu99) = (*qu100);


		(*Ql2) = (*Ql3);
		cout << "	Очередь Ql2\n";
		Ql2->Browse(Print);
		/////
		Queue* Qc4 = new CQueue;
		Queue* Qc5 = new CQueue;
		Qc4->Push(12);
		Qc4->Push(-9);
		Qc4->Push(75);
		Qc4->Push(-73);
		Qc4->Push(0);
		(*Qc5) = (*Qc4);
		cout << "Очередь Qc4\n";
		Qc4->Browse(Print);
		cout << "Очередь Qc5\n";
		Qc5->Browse(Print);
		Qc5->Pop();
		Qc5->Pop();
		Qc5->Pop();
		Qc5->Pop();
		Qc5->Pop();
		if (!Qc5->Pop())
			cout << "Queue is empty!\n";
		cout << "Очередь Qc5\n";
		Qc5->Browse(Print);

		delete[] Ql3;
		delete[] Ql2;
		delete[] Qc4;
		delete[] Qc5;

	}
	catch (My_exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}