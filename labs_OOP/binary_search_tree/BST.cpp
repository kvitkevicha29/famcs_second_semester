#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
ifstream fin("INPUT.TXT");
ofstream fout("OUTPUT.TXT");

class BST
{
private:
	struct TreeItem {
		int Info;
		TreeItem *right;
		TreeItem *left;
		TreeItem *father;
		TreeItem() { left = right = father = NULL; }
	};
	TreeItem *root;
public:
	BST() { root = NULL; }
	BST(const BST &);
	bool RootCheck()
	{
		if (root != NULL)
			return true;
		else
			return false;
	}
	int getInfo(const BST *&)
	{
		return root->Info;
	}
	const BST & operator = (const BST &);
	bool Find(int, TreeItem*&);
	bool FindByValue(int, int &);
	bool insert(int);
	bool Remove(int);
	void bfs(TreeItem *Root, void Func(int&)) const;
	void bfs(void Func(int&)) const;
	void EraseTr(TreeItem* &);	
	void Erase();
	friend void Print(int &a);
	void printByLevel(TreeItem *t, int level);
	virtual ~BST();
protected:
	TreeItem* Clone(TreeItem*);
	void DeleteTree(TreeItem *);
};

BST::TreeItem* BST::Clone(TreeItem* Tr)
{
	if (Tr == NULL)
		return NULL;
	TreeItem* New = new TreeItem;
	New->Info = Tr->Info;
	New->left = Clone(Tr->left);
	New->right = Clone(Tr->right);
	return New;
}

void BST::Erase()
{
	DeleteTree(root);
	root = NULL;
	cout << "Tree is erased.\n";
}

BST::~BST()
{
	Erase();
}

void BST::DeleteTree(TreeItem *t)
{
	if (t != NULL)
	{
		DeleteTree(t->left);
		DeleteTree(t->right);
		delete t;
	}
}

BST::BST(const BST& L)
{
	root = Clone(L.root);
}

const BST & BST::operator = (const BST &L)
{
	if (&L == this)
		return *this;
	Erase();
	root = Clone(L.root);
	return *this;
}

bool BST::Find(int x, TreeItem* &t)
{
	if (root == NULL)
	{
		t = NULL;
		return false;
	}
	t = root;
	for (;;)
	{
		if (t->Info == x)
		{
			return true;
		}
		if (t->Info > x)
		{
			if (t->left == NULL)
				return false;
			t = t->left;
		}
		else
		{
			if (t->right == NULL)
				return false;
			t = t->right;
		}
	}
}

void BST::printByLevel(TreeItem *t, int level)
{
	int count = 0;
	if (t == nullptr)
		return;  // Если дерево пустое, то отображать нечего, выходим
	else {  // Иначе
		if (level == 0 || level < 0)
		{
			cout << "Нет таких уровней";
			return;
		}
		else
		{
			cout << level << " уровень" << endl;
			cout << t->Info << endl;

		}
	}
}

bool BST::insert(int x)
{
	int ch = 0;
	TreeItem* s = new TreeItem;
	if (Find(x, s))
	{
		return false;
	}
	if (root == NULL)
	{
		TreeItem *p = new TreeItem;
		root = p;
		p->Info = x;
		p->father = NULL;
		return true;
	}
	else
	{
		TreeItem *p = new TreeItem;
		p = root;
		TreeItem *q = new TreeItem;
		q->Info = x;
		for (; ; )
		{
			if (p->Info > x)
			{
				if (p->left == NULL)
				{
					p->left = q;
					q->father = p;
					return true;
				}
				else
				{
					p = p->left;
				}
			}
			else
			{
				if (p->right == NULL)
				{
					q->father = p;
					p->right = q;
					return true;
				}
				else
				{
					p = p->right;
				}
			}
		}
	}
}

bool BST::FindByValue(int a, int &t)
{
	if (root == NULL)
	{
		return false;
	}
	TreeItem *temp = new TreeItem;
	temp = root;
	for (;;)
	{
		if (temp->Info == a)
		{
			t++;
			return true;
		}
		if (temp->Info > a)
		{
			t++;
			if (temp->left == NULL)
				return false;
			temp = temp->left;
		}
		else
		{
			t++;
			if (temp->right == NULL)
				return false;
			temp = temp->right;
		}
	}

}

bool BST::Remove(int e)
{
	TreeItem*s;
	TreeItem*q;
	if (!Find(e, s))
		return false;
	else
	{
		if ((s->left != NULL) && (s->right != NULL))
		{
			q = s->right;
			while (q->left != NULL)
				q = q->left;
			s->Info = q->Info;
			EraseTr(q);
		}
		else
			EraseTr(s);
		return true;
	}
}

void BST::EraseTr(TreeItem* &s)
{
	TreeItem *q;
	if (s->left != NULL)
		q = s->left;
	else
		q = s->right;
	if (q != NULL)
		q->father = s->father;
	if (s->father == NULL)
		root = q;
	else
		if ((s->father)->left == s)
			(s->father)->left = q;
		else
			(s->father)->right = q;
	delete s;
	s = NULL;
}

void BST::bfs(TreeItem *Root, void Pri(int&)) const
{
	if (Root == NULL)
	{
		return;
	}
	bfs(Root->left, Pri);
	Pri(Root->Info);
	bfs(Root->right, Pri);
}

void BST::bfs(void Pri(int&)) const
{
	if (root != NULL)
	{
		bfs(root->left, Pri);
		Pri(root->Info);
		bfs(root->right, Pri);
	}
	else
	{
		fout << "Your tree is empty!\n";
		return;
	}
}

void Print(int &a)
{
	fout << a << endl;
}

int main()
{
	if (!fin)
	{
		cout << "There is no input file!\n";
		return 1;
	}
	if (!fin.is_open())
	{
		cout << "Input file is not opened!\n";
		return 1;
	}
	if (fin.peek() == EOF)
	{
		cout << "Input file is empty!\n";
		return 1;
	}
	if (!fout)
	{
		cout << "There is no output file!\n";
		return 1;
	}
	if (!fout.is_open())
	{
		cout << "Output file is not opened!\n";
		return 1;
	}
	void(*foo)(int &a) = &Print;
	BST tree;
	string buf;
	int cur_value = 0;
	bool flag = 0;
	while (fin >> buf)
	{
		if (buf == "I")
		{
			fin >> cur_value;
			if (tree.insert(cur_value))
			{
				fout << cur_value << ": inserted\n";
			}
			else
			{
				fout << cur_value << ": not inserted\n";
			}
			flag = 1;
		}
		if (buf == "D")
		{
			fin >> cur_value;
			if (tree.Remove(cur_value))
			{
				fout << cur_value << ": deleted\n";
			}
			else
			{
				fout << cur_value << ": not deleted\n";
			}
			flag = 1;
		}
		if (buf == "F")
		{
			int cnt = 0;
			fin >> cur_value;
			if (tree.FindByValue(cur_value, cnt))
			{
				fout << cur_value <<": found after " << cnt << " comparison(s)\n";
			}
			else
			{
				fout << cur_value << ": not found after " << cnt << " comparison(s)\n";
			}
			flag = 1;
		}
		if (buf == "L")
		{
			fout << "List of elements\n";
			tree.bfs(foo);
			flag = 1;
		}
		if (buf == "P")
		{
			fin >> cur_value;
			cout << "Level " << cur_value << endl;

		}
	}
	
	fout << "Operator '=':\n------------------------\n";
	BST Tree1;
	Tree1 = tree;
	Tree1.bfs(foo);
	fout << "------------------------\n";
	fout << "Constuctor:\n------------------------\n";
	BST Tree2 = tree;
	Tree2.bfs(foo);
	fout << "------------------------\n";
	BST Tree3(tree);
	fout << "Constuctor:\n------------------------\n";
	Tree3.bfs(foo);
	fout << "------------------------\n";

	BST Tree;
	Tree.Erase();

	fin.close();
	fout.close();

	if (fin.is_open())
	{
		cout << "Input file is not closed!\n";
		return 1;
	}
	if (fout.is_open())
	{
		cout << "Output file is not closed!\n";
		return 1;
	}

	if (flag)
	{
		cout << "All is well. Check your output file, please!\n";
	}
	else
	{
		cout << "Output file is empty. Something went wrong!\n";
	}
	return 0;
}
