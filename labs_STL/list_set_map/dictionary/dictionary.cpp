#include "pch.h"
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");

string lowerWord(string w)
{
	for (unsigned i = 0; i < w.length(); ++i)
	{
		w[i] = tolower(w[i]);
	}
	return w;
}

int main()
{
	setlocale(LC_ALL, ".1251");
	if (!fin) { cout << "No input file!\n"; return -1; }
	if (!fin.is_open()) { cout << "Input is not opened!\n"; return -1; }
	if (fin.peek() == EOF) { cout << "Input file is empty!\n"; return -1; }
	set <string> words;
	string buf;
	while (fin.good())
	{
		fin >> buf;
		words.insert(buf);
	}
	set <string> ::iterator i = words.begin();
	cout << "All words:\n";
	for (i; i != words.end(); ++i)
	{
		cout << *i << endl;
	}
	map <string, int> freq_dict;
	fin.seekg(ios::beg);
	while (fin.good())
	{
		fin >> buf;
		++freq_dict[lowerWord(buf)];
	}
	cout << "Frequency (without checking case):\n";
	for (map< string, int >::iterator it = freq_dict.begin(); it != freq_dict.end(); ++it)
	{
		cout << it->first << " : " << it->second << " --- " ;
		for (i = words.begin(); i != words.end(); ++i)
		{
			if (it->first == lowerWord(*i)) cout << *i << ' ';
		}
		cout << endl;
	}
}
