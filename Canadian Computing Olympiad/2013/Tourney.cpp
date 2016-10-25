#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, M, size, j, S;
int nodes[2100000];
int winner[2100000];
char K;

int power(int n, int k)
{
	int total = 1;
	for (int i = 0; i != k; ++i)
		total *= n;
	return total;
}

void build_heap()
{
	for (int i = size - 1; i != 0; --i)
	{
		nodes[i] = max(nodes[i * 2], nodes[i * 2 + 1]);
		if (nodes[i] == nodes[i * 2])
			winner[i] = winner[i * 2];
		else
			winner[i] = winner[i * 2 + 1];
	}
}

void update(int i)
{
	if (i == 0)
		return;
	nodes[i] = max(nodes[i * 2], nodes[i * 2 + 1]);
	if (nodes[i] == nodes[i * 2])
		winner[i] = winner[i * 2];
	else
		winner[i] = winner[i * 2 + 1];
	update(i / 2);
}

int query(int node, int i)
{
	if (node == 0)
		return 0;
	if (nodes[node] == i)
		return 1 + query(node / 2, i);
	else
		return 0;
}

int main()
{
	//ifstream file("Tourney.txt");
	scanf("%d%d", &N, &M);
	size = power(2, N);
	for (int i = size; i != size * 2; ++i)
	{
		scanf("%d", &nodes[i]);
		winner[i] = i;
	}
	build_heap(); 
	for (int i = 0; i != M; ++i)
	{
		cin >> K;
		if (K == 'W')
			cout << winner[1] - size + 1<< endl;
		else if (K == 'R')
		{
			scanf("%d%d", &j,&S);
			nodes[size + j - 1] = S;
			update((size + j - 1) / 2);
		}
		else if (K == 'S')
		{
			scanf("%d", &j);
			cout << query((size + j - 1) / 2, nodes[size + j - 1]) << endl;
		}

	}
	return 0;
}