#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"

using namespace std;

Person::Person()
{
	name = new char[7];
	strcpy(name, "Person");
}

Person::Person(const char *info)
{
	cout << "Конструктор Person\n";
	name = new char[strlen(info) + 1];
	strcpy(name, info);
}

Person::~Person()
{
	cout << "Деструктор Person\n";
	delete[] name;
}

void Person::SetFio(const char *info)
{
	delete[] name;
	name = new char[strlen(info) + 1];
	strcpy(name, info);
}

char* Person::GetFio() const
{
	char *info = new char[strlen(name) + 1];
	strcpy(info, name);
	return info;
}

void Person::Print() const
{
	cout << name;
}

Student::Student()
{
	group = 0;
	year = 0;
}

Student::Student(const char* info, int gr, int ye) :Person(info), group(gr), year(ye) { cout << "Конструктор Student\n"; }

void Student::SetGr(int gr)
{
	group = gr;
}

void Student::SetYe(int ye)
{
	year = ye;
}

void SetGr(int gr)
{
	
}

void SetYe(int ye)
{

}

void Student::Print() const
{
	Person::Print();
	cout << group << " " << year;
}

Teacher::Teacher(const char *name1, const char *dep1)
{
	cout << "Конструктор Teacher\n";
	strcpy(name, name1);
	strcpy(dep, dep1);
}

void Teacher::SetDep(const char *a)
{
	strcpy(dep, a);
}

char * Teacher::GetDep() const
{
	return nullptr;
}

void Teacher::Print() const
{
}

Teacher::~Teacher()
{
	cout << "Деструктор Teacher\n";
	delete[] dep;
}
