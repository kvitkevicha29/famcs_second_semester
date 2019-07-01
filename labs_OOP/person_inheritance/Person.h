#pragma once
#include <iostream>

//Person -> Student
//		 -> Prepod

using namespace std;

class Person
{
protected:
	char* name;
public:
	Person();
	Person(const char*);
	virtual ~Person();
	void SetFio(const char*);
	char* GetFio() const;
	void Print() const;
};

class Student :public Person
{
private:
	int group;
	int year;
public:
	Student();
	Student(const char*, int, int);
	void SetGr(int gr);
	void SetYe(int ye);
	int GetGr() const { return group; }
	int GetYe() const { return year; }
	void Print() const;
};

class Teacher :public Person
{
private:
	char* dep;
public:
	Teacher(const char* name1, const char* dep1);
	void SetDep(const char* a);
	char* GetDep() const;
	void Print() const;
	~Teacher();
};