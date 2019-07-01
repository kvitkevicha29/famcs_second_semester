#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Class.h"
#include <string>
#include <iostream>

person::person(): ID(ident++)
{
	name = new char[1];
	strcpy(name, "");
}

person::person(const char* n) : ID(ident++)
{
	cout << "����������� person\n";
	name = new char[strlen(n) + 1];
	strcpy(name, n);
}

person::~person()
{
	cout << "���������� person\n";
	delete[] name;
}

char* person::getname() const
{
	char* temp = new char[strlen(name) + 1];
	strcpy(temp, name);
	return temp;
}

void person::setname(const char* s)
{
	delete[] name;
	name = new char[strlen(s) + 1];
	strcpy(name, s);
}

void person::print() const
{
	cout << "��� : " << name  << " ID: " << getID() << endl;
}

student::student() : person(), course(0), group(0) {}

student::student(const char* n, const int c, const int g) : person(n), course(c), group(g) { cout << "����������� student\n"; }

void student::print() const
{
	person::print();
	cout << "���� : " << course;
	cout << ", ������ : " << group << endl << endl;
}

teacher::teacher() : person()
{
	cout << "����������� teacher\n";
	depart = new char[1];
	strcpy(depart, "");
}

teacher::teacher(const char* n, const char* d) : person(n)
{
	cout << "����������� teacher\n";
	depart = new char[strlen(d) + 1];
	strcpy(depart, d);
}

teacher::~teacher()
{
	cout << "���������� teacher\n";
	delete[] depart;
}

char* teacher::getdepart() const
{
	char* temp = new char[strlen(depart) + 1];
	strcpy(temp, depart);
	return temp;
}

void teacher::setdepart(const char* d)
{
	delete[] depart;
	depart = new char[strlen(d) + 1];
	strcpy(depart, d);
}

void teacher::print() const
{
	person::print();
	cout << "������� : " << depart << endl << endl;
}