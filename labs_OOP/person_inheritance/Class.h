#ifndef LIST_H
#define LIST_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

static int ident = 0;

class person
{
private:
	char* name;
	const int ID;
public:
	person();
	person(const char* n);
	virtual ~person();
	char* getname() const;
	int getID() const { return ID; }
	void setname(const char*);
	virtual void print() const;
};

class student : public person
{
private:
	int course;
	int group;
public:
	student();
	student(const char*, const int, const int);
	int getcourse() const { return course; }
	int getgroup() const { return group; }
	void setcourse(const int c) { course = c; }
	void setgroup(const int g) { group = g; }
	void print() const;
};

class teacher : public person
{
private:
	char* depart;
public:
	teacher();
	teacher(const char*, const char*);
	virtual ~teacher();
	char* getdepart() const;
	void setdepart(const char*);
	void print() const;
};
#endif