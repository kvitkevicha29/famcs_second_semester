#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Class.h"
#include <typeinfo>
#include <iostream>
#include <Windows.h>

int main()
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int MAX_SIZE = 256;
	person *arr[20];
	int index = 0;
	bool S = true, T = true;
	const int MX = 20;
	cout << "1 - Ввести студента\n2 - Ввести преподователя\n3 - Вывести список студентов\n4 - Вывести список преподователей\n5 - Выход из меню\n";
	int choice;
	do {
		cout << "Ваш выбор:\n";
		cin >> choice;
		while (choice > 5 || choice < 0)
		{
			cout << "Попробуйте еще раз\n";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			char* name = new char[MAX_SIZE];
			int group = 0, course = 0;
			cout << "ФИО: ";
			cin.ignore();
			cin.getline(name, MAX_SIZE);
			cout << "Курс: ";
			cin >> course;
			cout << "Группа: ";
			cin >> group;
			student *tempS = new student(name, course, group);
			arr[index] = tempS;
			index++;
			S = false;
			delete[] name;
			break;
		}
		case 2:
		{
			char* name = new char[MAX_SIZE];
			char* depart = new char[MAX_SIZE];
			cout << "ФИО: ";
			cin.ignore();
			cin.getline(name, MAX_SIZE);
			cout << "Кафедра: ";   
			cin >> depart;
			teacher *tempT = new teacher(name, depart);
			arr[index++] = tempT;
			T = false;
			delete[] name;
			delete[] depart;
			break;
		}
		case 3:
		{
			if (S == true)
			{
				cout << "В массиве нет студентов!\n";
				break;
			}
			cout << "Список студентов:\n";
			for (int i = 0; i < index; i++)
				if (typeid(*arr[i]) == typeid(student))
					arr[i]->print();
			break;
		}
		case 4:
		{
			if (T == true)
			{
				cout << "В массиве нет преподавателей!\n";
				break;
			}	
			cout << "Список преподавателей:\n";
			for (int i = 0; i < index; i++)
				if (typeid(*arr[i]) == typeid(teacher))
					arr[i]->print();
			break;
		}
		}
	} while (choice != 5);
	cout << "Вы вышли из меню.\n";
	return 0;
}
