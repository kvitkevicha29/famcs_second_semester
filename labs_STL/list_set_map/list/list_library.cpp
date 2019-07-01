#include "pch.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct author {
	string surname;
	string name;
	string patronymic;
	bool operator==(const author &a);
};

struct Book {
	int UDK;
	list <author> authors;
	string title;
	int year;
	bool operator==(const Book &);
};

bool bookCMP(const Book &b1, const Book &b2)
{
	return (b1.title < b2.title);
}

bool authorCMP(const author &a1, const author &a2)
{
	if (a1.surname < a2.surname) return true;
	if (a1.surname == a2.surname && a1.name < a2.name) return true;
	if (a1.surname == a2.surname && a1.patronymic < a2.patronymic) return true;
	return false;
}

bool listsAreEqual(const list <author> &l1, const list <author> &l2)
{
	bool flag = true;
	if (l1.size() != l2.size()) return false;
	list <author>::const_iterator i1 = l1.begin();
	list <author>::const_iterator i2 = l2.begin();
	for (; i1 != l1.end(); ++i1, ++i2)
	{
		if ((((*i1).surname) != (*i2).surname || (*i1).name != (*i2).name || (*i1).patronymic != (*i2).patronymic)) return false;
	}
	return true;
}

bool author::operator==(const author &a)
{
	return (a.surname == this->surname && a.name == this->name && a.patronymic == this->patronymic);
}
bool Book::operator==(const Book &b)
{
	return (b.UDK == this->UDK && b.year == this->year && b.title == this->title && listsAreEqual(b.authors, this->authors));
}

ifstream fin("books.txt");

Book getBook(string buf)
{
	Book book;
	book.UDK = stoi(buf.substr(0, buf.find_first_of(';')));
	buf.erase(0, buf.find_first_of(';') + 1);
	book.title = buf.substr(0, buf.find_first_of(';'));
	buf.erase(0, buf.find_first_of(';') + 1);
	string cur_name;
	book.year = stoi(buf.substr(0, buf.find_first_of(';')));
	buf.erase(0, buf.find_first_of(';') + 1);
	cur_name = buf.substr(0, buf.find_first_of(",;"));
	while (cur_name.length())
	{
		author aut;
		aut.surname = cur_name.substr(0, cur_name.find_first_of(' '));
		cur_name.erase(0, cur_name.find_first_of(' ') + 1);
		aut.name = cur_name.substr(0, cur_name.find_first_of(' '));
		cur_name.erase(0, cur_name.find_first_of(' ') + 1);
		cur_name.erase(cur_name.length());
		aut.patronymic = cur_name;
		book.authors.push_back(aut);
		cur_name.clear();
		buf.erase(0, buf.find_first_of(",;") + 1);
		cur_name = buf.substr(0, buf.find_first_of(",;\n"));
	}
	return book;
}

void printAuthor(const author &a)
{
	cout << setw(12) << "Фамилия: " << a.surname << endl;
	cout << setw(12) << "Имя: " << a.name << endl;
	cout << setw(12) << "Отчество: " << a.patronymic << endl;
}

void printBook(const Book &b)
{
	cout << setw(6) << "УДК: " << b.UDK << endl;
	cout << "Название книги: " << b.title << endl << endl;
	auto i = b.authors.begin();
	cout << "Список авторов: " << endl;
	for (i; i != b.authors.end(); ++i)
	{
		printAuthor(*i);
		cout << endl;
	}
	cout << setw(4) << "Год издания: " << b.year << endl;
	cout << "______________________________________________\n";
}

void Add(list <Book> &l, const Book &b)
{
	list<Book>::iterator i = l.begin();
	for (i; i != l.end();)
	{
		if ((*i).title < b.title)
		{
			i++;
		}
		else break;
	}
	l.insert(i, b);
	i--;
	(*i).authors.sort(authorCMP);
}

bool Delete(list <Book> &l, const Book &b)
{
	bool flag = false;
	list<Book>::iterator i = l.begin();
	for (i; i != l.end(); ++i)
	{
		if ((*i) == b)
		{
			flag = true;
			l.erase(i);
			break;
		}
	}
	if (flag) cout << "Книга удалена.\n";
	else cout << "Такой книги не было в списке.\n";
	return flag;
}

bool findByTitle(list<Book> &l, string t)
{
	list<Book>::iterator i = l.begin();
	for (i; i != l.end(); ++i)
	{
		if ((*i).title == t)
		{
			printBook(*i);
			return true;
		}
	}
	return false;
}

bool findAuthorsBook(list<Book> &l, const author &a)
{
	bool flag = false;
	list<Book>::iterator i = l.begin();
	for (i; i != l.end(); ++i)
	{
		list<author>::iterator i_a = (*i).authors.begin();
		for (i_a; i_a != (*i).authors.end(); ++i_a)
		{
			if ((*i_a) == a)
			{
				printBook((*i));
				flag = true;
			}
		}
	}
	if (!flag) cout << "Книг данного автора нет в библиотеке!\n";
	return flag;
}

bool deleteBooksAuthor(list<Book> &l, const Book &b, const author &a)
{
	bool flag = false;
	list<Book>::iterator i = l.begin();
	for (i; i != l.end(); ++i)
	{
		if (*i == b)
		{
			list <author> ::iterator it = ((*i).authors).begin();
			for (it; it != ((*i).authors).end(); ++it)
			{
				if (*it == a)
				{
					((*i).authors).erase(it);
					printBook(*i);
					flag = true;
					break;
				}
			}
		}
	}
	if (flag) cout << "Автор удалён.\n";
	if (!flag) cout << "Такой книги/автора нет в списке!\n";
	return flag;
}

bool addBooksAuthor(list<Book> &l, const Book &b, const author &a)
{
	bool flag = false;
	list<Book>::iterator i = l.begin();
	for (i; i != l.end(); ++i)
	{
		if (*i == b)
		{
			(*i).authors.push_back(a);
			(*i).authors.sort(authorCMP);
			flag = true;
		}
	}
	if (flag) cout << "Автор добавлен.\n";
	if (!flag) cout << "Такой книги нет в списке!\n";
	return flag;
}

int main()
{
	setlocale(LC_ALL, ".1251");
	system("chcp 1251");
	if (!fin) { cout << "No input file!\n"; return -1; }
	if (!fin.is_open()) { cout << "Input is not opened!\n"; return -1; }
	if (fin.peek() == EOF) { cout << "Input file is empty!\n"; return -1; }
	list <Book> library;
	string buf;
	Book tmp;
	while (getline(fin, buf))
	{
		tmp = getBook(buf);
		library.push_back(tmp);
	}
	library.sort(bookCMP);
	list<Book>::iterator i = library.begin();
	for (i; i != library.end(); ++i)
	{
		((*i).authors).sort(authorCMP);
		printBook(*i);
	}
	cout << "_______________________________________________________________________\n";
	cout << "_______________________________________________________________________\n";
	cout << "_______________________________________________________________________\n";

	Book book1;
	book1.title = "Мифы и легенды про лабы по проге";
	book1.UDK = 128341;
	book1.year = 2019;
	author a1, a2;
	a1.surname = "Горшунова";
	a1.name = "Екатерина";
	a1.patronymic = "Сергеевна";
	a2.surname = "Квиткевич";
	a2.name = "Александр";
	a2.patronymic = "Сергеевич";
	book1.authors.push_back(a1);
	book1.authors.push_back(a2);
	Add(library, book1);
	for (i = library.begin(); i != library.end(); ++i)
	{
		printBook(*i);
	}
	cout << "------------------------------------\n";
	Delete(library, book1);
	cout << "------------------------------------\n";
	for (i = library.begin(); i != library.end(); ++i)
	{
		printBook(*i);
	}
	Delete(library, book1);
	string title;
	cout << "Введите название искомой книги:\n";
	getline(cin, title, '\n');
	findByTitle(library, title);
	cout << "Введите название искомой книги:\n";
	getline(cin, title, '\n');
	findByTitle(library, title);
	author Razmyslovich, Filiptsov, Shiryaev;
	Razmyslovich.surname = "Размыслович";
	Razmyslovich.name = "Георгий";
	Razmyslovich.patronymic = "Прокофьевич";
	cout << "Все книги Размысловича Георгия Прокофьевича: \n";
	findAuthorsBook(library, Razmyslovich);

	Filiptsov.surname = "Филипцов";
	Filiptsov.name = "Александр";
	Filiptsov.patronymic = "Владимирович";

	Shiryaev.surname = "Ширяев";
	Shiryaev.name = "Владимир";
	Shiryaev.patronymic = "Михайлович";

	Book Praktikum;
	Praktikum.UDK = 512514;
	Praktikum.title = "Геометрия и алгебра. Практикум";
	Praktikum.year = 2018;
	Praktikum.authors.push_back(Razmyslovich);
	Praktikum.authors.push_back(Filiptsov);
	Praktikum.authors.push_back(Shiryaev);
	Praktikum.authors.sort(authorCMP);

	deleteBooksAuthor(library, Praktikum, Razmyslovich);
	deleteBooksAuthor(library, Praktikum, Razmyslovich);

}
