#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>
using namespace std;

enum Type { passenger, express, error };
string getType(Type t)
{
	if (t == passenger)
	{
		return "passenger";
	}
	if (t == express)
	{
		return "express";
	}
	return "error";
}

class TRAIN {
	int number;
	string destination;
	Type type;
	struct Time {
		int hour;
		int min;
	} dep_time;
	int tr_time;
	friend istream & operator>> (istream &in, TRAIN &train);
	friend void sortByDepTime(vector <TRAIN> &v);
	friend void my_swap_time(TRAIN &a, TRAIN &b);
	friend ostream & operator<< (ostream &out, const TRAIN &train);
	friend void printByDepTime(vector <TRAIN> v, int t1_h, int t1_m, int t2_h, int t2_m);
	friend void printByDestination(vector <TRAIN> v, string dest);
	friend void printExpressByDestination(vector <TRAIN> v, string dest);
	friend TRAIN theFastestOne(vector <TRAIN> v, string dest);
};

void my_swap(int &a, int &b)
{
	int tmp = b;
	b = a;
	a = tmp;
}

void my_swap_time(TRAIN &a,  TRAIN &b)
{
	if (a.dep_time.hour > b.dep_time.hour)
	{
		TRAIN tmp = a;
		a = b;
		b = tmp;
	}
	else if (a.dep_time.hour == b.dep_time.hour)
	{
		if (a.dep_time.min > b.dep_time.min)
		{
			TRAIN tmp = a;
			a = b;
			b = tmp;
		}
	}
}

void sortByDepTime(vector <TRAIN> &v)
{
	auto i = v.begin();
	if (i == v.end())
	{
		cout << "Вектор пуст.\n";
		return;
	}
	for (i; i != v.end(); ++i)
	{
		for (auto j = i + 1; j != v.end(); ++j)
		{
			my_swap_time(*i, *j);
		}
	}
}

void printByDepTime(vector <TRAIN> v, int t1_h, int t1_m, int t2_h, int t2_m)
{
	auto i = v.begin();
	if (i == v.end())
	{
		cout << "Вектор пуст.\n";
		return;
	}
	if ((t1_h > t2_h) || (t1_h == t2_h && t1_m > t2_m))
	{
		my_swap(t1_h, t2_h);
		my_swap(t1_m, t2_m);
	}
	bool flagg = false;
	for (i; i != v.end();)
	{
		bool flag = false;
		if ((*i).dep_time.hour > t1_h && (*i).dep_time.hour < t2_h)
		{
			flag = true;
			flagg = true;
		}
		else if ((*i).dep_time.hour == t1_h && (*i).dep_time.min > t1_m && (*i).dep_time.hour < t2_h)
		{
			flag = true;
			flagg = true;
		}
		else if ((*i).dep_time.hour == t2_h && (*i).dep_time.min < t2_m && (*i).dep_time.hour > t1_h)
		{
			flag = true;
			flagg = true;
		}
		if (flag) cout << (*i);
		if (((*i).dep_time.hour > t2_h) || ((*i).dep_time.hour == t2_h && (*i).dep_time.min > t2_m)) break;
		else i++;
	}
	if (!flagg) cout << "Нет поездов, отправляющихся в интервале от " << setfill('0')
		<< setw(2) << t1_h << ":" << setfill('0') << setw(2) << t1_m << " до " << setfill('0')
		<< setw(2) << t2_h << ":" << setfill('0') << setw(2) << t2_m << endl;
}

void printByDestination(vector <TRAIN> v, string dest)
{
	auto i = v.begin();
	if (i == v.end())
	{
		cout << "Вектор пуст.\n";
		return;
	}
	bool flag = false;
	for (i; i != v.end(); ++i)
	{
		if ((*i).destination == dest)
		{
			cout << (*i);
			flag = true;
		}
	}
	if (flag == false) cout << "Нет поездов, следующих в " << dest << endl;

}

void printExpressByDestination(vector <TRAIN> v, string dest)
{
	auto i = v.begin();
	if (i == v.end())
	{
		cout << "Вектор пуст.\n";
		return;
	}
	bool flag = false;
	for (i; i != v.end(); ++i)
	{
		if ((*i).destination == dest && (*i).type == express)
		{
			cout << (*i);
			flag = true;
		}
	}
	if (flag == false) cout << "Нет скорых поездов, следующих в " << dest << endl;
}

TRAIN theFastestOne(vector <TRAIN> v, string dest)
{
	auto i = v.begin();
	bool flag = false;
	int min_speed = INT_MAX;
	TRAIN ans;
	for (i; i != v.end(); ++i)
	{
		if ((*i).destination == dest && (*i).tr_time < min_speed)
		{
			min_speed = (*i).tr_time;
			ans = *i;
			flag = true;
		}
	}
	if (!flag) cout << "Нет поездов, следующих в " << dest << endl;
	return ans;
}

void print(vector <TRAIN> v)
{
	auto i = v.begin();
	if (i == v.end())
	{
		cout << "Вектор пустой.\n";
		return;
	}
	for (i; i != v.end(); ++i)
	{
		cout << (*i);
	}
}

ifstream fin("train.txt");

int main()
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (!fin)
	{
		cout << "Входной файл не найден.\n";
		return 1;
	}
	if (!fin.is_open())
	{
		cout << "Входной файл не открыт.\n";
		return 1;
	}
	if (fin.peek() == EOF)
	{
		cout << "Входной файл пуст.\n";
		return 1;
	}
	vector <TRAIN> v(0);
	auto i = v.begin();
	TRAIN cur;
	while (fin.good())
	{
		fin >> cur;
		v.push_back(cur);
		i = v.end();
	}
	print(v);
	cout << "SORTED.\n";
	sortByDepTime(v);
	print(v);
	cout << "Введите первую временную границу (ЧЧ:ММ):\n";
	int t1_h = 0, t1_m = 0;
	cin >> t1_h >> t1_m;
	cout << "Введите вторую временную границу (ЧЧ:ММ):\n";
	int t2_h = 23, t2_m = 59;
	cin >> t2_h >> t2_m;
	printByDepTime(v, t1_h, t1_m, t2_h, t2_m);
	cout << "Введите пункт назначения: \n";
	string dest;
	cin >> dest;
	cout << "Все поезда, следующие в " << dest << ":" << endl;
	printByDestination(v, dest);
	cout << "Все скорые поезда, следующие в " << dest << ":" << endl;
	printExpressByDestination(v, dest);
	cout << "Самый быстрый поезд, следующий в " << dest << ":" << theFastestOne(v, dest) << endl;
}

istream & operator>>(istream & in, TRAIN & train)
{
	in >> train.number;
	in >> train.destination;
	string buf;
	in >> buf;
	if (buf == "express") train.type = express;
	else if (buf == "passenger") train.type = passenger;
	else train.type = error;
	in >> train.dep_time.hour;
	in >> train.dep_time.min;
	in >> train.tr_time;
	return in;
}

ostream & operator<< (ostream &out, const TRAIN &train)
{
	out << setw(4) << train.number << " " << train.destination << " " << getType(train.type) << " "
		<< setfill('0') << setw(2) << train.dep_time.hour << ":"
		<< setfill('0') << setw(2) << train.dep_time.min << " " << train.tr_time << endl;
	return out;
}
