#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int treeval[1000010];

struct Node
{
	Node *left, *right;
	pair<int, int> Lrange, Rrange;
	int lbound = 0, rbound = 0, value = 10000000;
	Node(int l, int h)
	{
		lbound = l;
		rbound = h;
		if (lbound == rbound)
			value = treeval[l];
		else
		{
			left = new Node(lbound, (lbound + rbound) / 2);
			right = new Node((lbound + rbound) / 2 + 1, rbound);
			value = min(left->value, right->value);
		}
	}
	void update(int pos)
	{
		if (pos == lbound && pos == rbound)
			value = treeval[pos];
		else if (pos <= (lbound + rbound) / 2)
		{
			left->update(pos);
			value = min(left->value, right->value);
		}
		else
		{
			right->update(pos);
			value = min(left->value , right->value);
		}
	}
	int query(int i, int j)
	{
		if (i > rbound | j < lbound)
			return 123123212;
		else if (j >=rbound && i <=lbound)
			return value;
		else
		{
			return min(left->query(i, j), right->query(i, j));
		}
	}
};




int N = 0, M = 0, i = 0, x = 0;
char type = 'a';

int main()
{
	//ifstream file("SegTree.txt");
	cin >> N >> M;

	for (int i = 0; i != N; ++i)
	{
		cin >> treeval[i];
	}
	Node mynode(0, N-1);
	for (int k = 0; k != M; ++k)
	{
		cin >> type >> i >> x;
		if (type == 'Q')
			cout << mynode.query(i, x) << endl;
		else
		{
			treeval[i] = x;
			mynode.update(i);
		}

	}


	return 0;
}