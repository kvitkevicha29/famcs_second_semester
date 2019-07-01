#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

ifstream fin("input.txt");

struct SMark
{
	string Subject;	  //предмет
	int Mark;	//оценка
};

struct SStudData
{
	string Name;	//фамилия, инициалы
	int Number;		//номер зачётки
	vector <SMark> Marks;	//рез-ты сессии
	double Avg; //средний балл
	int total; //сумма баллов
	bool good; //хороший ли студент (все отметки >= 4) 
	friend ostream& operator<<(ostream &, const SStudData&);
};

void getSStudData(map<int, SStudData> &m)
{
	string buf;
	int n = 1;
	while (getline(fin, buf, '\n'))
	{
		SStudData cur;
		cur.good = true;
		cur.Name = buf.substr(0, buf.find_first_of(';'));
		buf.erase(0, buf.find_first_of(';') + 1);
		cur.Number = stoi(buf.substr(0, buf.find_first_of(';')));
		buf.erase(0, buf.find_first_of(';') + 1);
		SMark cur_m;
		int cnt = 0; int sum = 0;
		while (buf.length())
		{
			cur_m.Subject = buf.substr(0, buf.find_first_of(",."));
			buf.erase(0, buf.find_first_of(",.") + 1);
			cur_m.Mark = stoi(buf.substr(0, buf.find_first_of(",.")));
			if (cur_m.Mark < 4) cur.good = false;
			buf.erase(0, buf.find_first_of(",.") + 1);
			cur.Marks.push_back(cur_m);
			sum += cur_m.Mark;
			cnt++;
		}
		cur.total = sum;
		cur.Avg = sum * (1.0) / cnt;
		m.insert(make_pair(n++, cur));
	}
}

void my_swap(double &a, double &b)
{
	if (a > b)
	{
		double tmp = a;
		a = b;
		b = tmp;
	}
}

void print_map(const map<int, SStudData> &m)
{
	auto i = m.begin();
	if (i != m.end())
	{
		for (i; i != m.end(); ++i)
		{
			cout << "Номер по порядку: " << i->first << endl;
			cout << i->second;
		}
	}
	else cout << "Map is empty!\n";
}

bool numberCMP(const pair<int, SStudData> &p1, const pair<int, SStudData> &p2)
{
	return (p1.second.Number < p2.second.Number);
}

bool AlphabetCMP(const pair<int, SStudData> &p1, const pair<int, SStudData> &p2)
{
	return (p1.second.Name < p2.second.Name || (p1.second.Name == p2.second.Name && p1.second.Avg > p2.second.Avg));
	/*if (p1.second.Name < p2.second.Name) return true;
	if (p1.second.Name == p2.second.Name && p1.second.Avg > p2.second.Avg) return true;*/
}

bool avgCMP(const pair<int, SStudData> &p1, const pair<int, SStudData> &p2)
{
	return (p1.second.Avg > p2.second.Avg);
}

void printSortedByNumber(const map<int, SStudData> &m)
{
	vector<pair<int, SStudData>> v;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		v.push_back(*i);
	}
	cout << "\n\n\n\n\nОтсортированный список (по номеру зачётки): \n";
	sort(v.begin(), v.end(), numberCMP);
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		cout << "Номер по порядку: " << (*i).first << endl;
		cout << (*i).second << endl;
	}
}

void printSortedByName(const map<int, SStudData> &m)
{
	vector<pair<int, SStudData>> v;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		v.push_back(*i);
	}
	cout << "\n\n\n\n\nОтсортированный список (по ФИО и среднему баллу): \n";
	sort(v.begin(), v.end(), AlphabetCMP);
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		cout << "Номер по порядку: " << (*i).first << endl;
		cout << "ФИО: " << (*i).second.Name << endl;
		cout << "Номер зачётки: " << (*i).second.Number << endl;
		cout << "Средний балл: " << setprecision(2) << fixed << (*i).second.Avg << endl;
		cout << "________________________________________\n";
	}
}

void printByAVG(const map<int, SStudData> &m, double a, double b)
{
	bool flag = false;
	my_swap(a, b);
	vector<pair<int, SStudData>> v;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		if ((*i).second.Avg >= a && (*i).second.Avg <= b)
		{
			flag = true;
			v.push_back(*i);
		}
	}
	if (flag)
	{
		cout << "\n\n\n\n\nВсе студенты со средним баллом из диапазона от " << a << " до " << b << " (по убыванию среднего балла):" << endl;
		sort(v.begin(), v.end(), avgCMP);
		for (auto i = v.begin(); i != v.end(); ++i)
		{
			cout << "Номер по порядку: " << (*i).first << endl;
			cout << (*i).second << endl;
		}
	}
	else cout << "Нет студентов со средним баллом из диапазона от " << a << " до " << b << "!" << endl;
}

void printBySubject(const map<int, SStudData> &m, const string &s)
{
	bool flag = false;
	cout << "Все студенты, которые сдавали дисциплину '" << s << "':" << endl;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		for (auto j = (*i).second.Marks.begin(); j != (*i).second.Marks.end(); ++j)
		{
			if ((*j).Subject == s)
			{
				flag = true;
				cout << "Номер по порядку: " << (*i).first << endl;
				cout << (*i).second << endl;
			}
		}
	}
	if (!flag) cout << "Никто не сдавал эту дисциплину!" << endl;
}

struct subjMark
{
	int total_mark;
	int students;
};

map<string,subjMark> getSubjects(const map<int, SStudData> &m) //количество студентов, сдававших каждый предмет
{
	map<string, subjMark> freq;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		for (auto j = (*i).second.Marks.begin(); j != (*i).second.Marks.end(); ++j)
		{
			++(freq[(*j).Subject].students);
			freq[(*j).Subject].total_mark += (*j).Mark;
		}
	}
	return freq;
}

bool avgCMP_(const pair<string, subjMark> &p1, const pair<string, subjMark> &p2)
{
	return ((p1.second.total_mark*(1.0)/p1.second.students) > (p2.second.total_mark*(1.0)/p2.second.students));
}

void printSubj(const map<string, subjMark> &m)
{
	vector<pair<string, subjMark>> v;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		v.push_back(*i);
	}
	cout << "\n\n\n\n\nОтсортированный список дисциплин (по среднему баллу): \n";
	sort(v.begin(), v.end(), avgCMP_);
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		cout << "Дисциплина: " << (*i).first << endl;
		cout << "Средний балл: " <<  setprecision(2) << fixed << ((*i).second.total_mark*(1.0)/(*i).second.students) << endl;
	}
}

void maxTotalStudents(const map<int, SStudData> &m)
{
	int max = INT_MIN;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		if ((*i).second.total > max) max = (*i).second.total;
	}
	cout << "Студент(ы) с максимальной суммой баллов за все экзамены:\n";
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		if ((*i).second.total == max)
		{
			cout << (*i).first << " номер - " << (*i).second.Name << endl;
		}
	}
}

void printBadStudents(const map<int, SStudData> &m)
{
	bool flag = true;
	cout << "Все студенты с неудовлетворительными отметками:\n";
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		if (!(*i).second.good)
		{
			flag = false;
			cout << (*i).second.Name << " - плохой студент!\n";
		}
	}
	if (flag) cout << "Таких не нашлось! Все студенты успешно сдали сессию!\n";
}

int main()
{
	setlocale(LC_ALL, ".1251");
	map<int, SStudData> M;
	getSStudData(M);
	print_map(M);
	printSortedByNumber(M);
	printSortedByName(M);
	printByAVG(M, 7.5, 5.5);
	printByAVG(M, 0, 4);
	printBySubject(M, "Учебная практика");
	printBySubject(M, "Дискретная математика");
	map<string, subjMark> eachSubj = getSubjects(M);
	for (auto i = eachSubj.begin(); i != eachSubj.end(); ++i)
	{
		cout << "Дисциплину '" << (*i).first << "' сдавал(о) " << (*i).second.students << " студент(ов)" << endl;
	}
	printSubj(eachSubj);
	maxTotalStudents(M);
	printBadStudents(M);
}

ostream & operator<<(ostream &out, const SStudData &SS)
{
	out << "ФИО: " << SS.Name << endl;
	out << "Зачётка: " << SS.Number << endl;
	out << "Результаты сессии:\n";
	for (auto i = SS.Marks.begin(); i != SS.Marks.end(); ++i)
	{
		out << '\t' << (*i).Subject << ": " << (*i).Mark << endl;
	}
	out << "Средний балл: " << setprecision(2) << fixed << SS.Avg << endl;
	out << "________________________________________\n";
	return out;
}
