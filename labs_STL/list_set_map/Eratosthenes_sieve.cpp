#include "pch.h"
#include <iostream>
#include <set>

using namespace std;

int main()
{
	setlocale(LC_ALL, ".1251");
	int N = 0;
	cout << "Введите, пожалуйста, натуральное число:\n";
	cin >> N;
	set <int> s;
	set <int>::iterator i = s.begin();
	int cnt = 1;
	while (cnt <= N)
	{
		s.insert(cnt++);
	}
	cnt = 2;
	int step = 0;
	while (cnt < N)
	{
		while (step <= N)
		{
			step += cnt;
			s.erase((cnt + step));
		}
		cnt++;
		step = 0;
	}
	cout << "Все простые числа, меньшие либо равные введенном Вам:\n";
	for (i = s.begin(); i != s.end(); ++i)
	{
		cout << *i << " ";
	}
}