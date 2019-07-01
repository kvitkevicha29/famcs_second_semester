#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("Students.txt");
ofstream f1("Fio.txt");
ofstream f2("Groups.txt");

struct Stud {
	string fio;
	int course;
	int group;
	Stud() : fio(""), course(0), group(0) {}
	Stud(string s, int c, int g) : fio(s), course(c), group(g) {}
};


void my_swap_course(Stud &a, Stud &b)
{
	if (a.course > b.course)
	{
		Stud tmp = a;
		a = b;
		b = tmp;
	}
	else if (a.course == b.course)
	{
		if (a.group > b.group)
		{
			Stud tmp = a;
			a = b;
			b = tmp;
		}
		else if (a.group == b.group)
		{
			if (a.fio > b.fio)
			{
				Stud tmp = a;
				a = b;
				b = tmp;
			}
		}
	}
}

void my_swap_name(Stud &a, Stud &b)
{
	if (a.fio > b.fio)
	{
		Stud tmp = a;
		a = b;
		b = tmp;
	}
}

void print(vector <Stud> s, ostream &out)
{
	auto i = s.begin();
	if (i == s.end())
	{
		cout << "Вектор пуст.\n";
		return;
	}
	for (i; i != s.end(); ++i)
	{
		out << "ФИО: " << (*i).fio << endl;
		out << "Курс: " << (*i).course << endl;
		out << "Группа: " << (*i).group << endl;
		out << "-----------------------------------\n";
	}
}

void sortByCourse(vector <Stud> &v)
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
			my_swap_course(*i, *j);
		}
	}
}

void sortByName(vector <Stud> &v)
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
			my_swap_name(*i, *j);
		}
	}
}
int main()
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (!fin)
	{
		cout << "Входной файл не существует.\n";
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
	vector <Stud> ss(0);
	auto i = ss.begin();
	while (fin.good())
	{
		string buf;
		getline(fin, buf);
		string fio = buf.substr(0, (buf.find_first_of(';')));
		buf.erase(0, buf.find_first_of(';')+1);
		int course = stoi(buf.substr(0, (buf.find_first_of(';'))));
		buf.erase(0, buf.find_first_of(';')+1);
		int group = stoi(buf.substr(0, (buf.find_first_of(';'))));
		Stud A(fio, course, group);
		ss.push_back(A);
		i = ss.end();
	}
	//print(ss, cout);
	sortByCourse(ss);
	print(ss, f2);
	sortByName(ss);
	print(ss, f1);
	cout << "Все выполнено успешно. Проверьте, пожалуйста, выходной файл.\n";
	return 0;
}
