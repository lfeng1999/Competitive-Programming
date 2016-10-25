#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

bool grid[32][32];
string word;
int pos = 0;

void build(int a, int b, int len)
{
	char let = word[pos];
	++pos;
	if (let == 'f')
	{
		for (int i = a; i != a + len; ++i)
		for (int j = b; j != b + len; ++j)
			grid[i][j] = true;
	}
	else if (let == 'p')
	{
		build(a, b, len / 2);
		build(a + len / 2, b, len / 2);
		build(a, b + len / 2, len / 2);
		build(a + len / 2, b + len / 2, len / 2);
	}
}

int main()
{
	//ifstream file("Quadtree.txt");
	int N = 0;
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
		pos = 0;
		cin >> word;
		build(0, 0, 32);
		pos = 0;
		cin >> word;
		build(0, 0, 32);
		int total = 0;
		for (int i = 0; i != 32; ++i)
			for (int j = 0; j != 32; ++j)
				total += grid[i][j];
		printf("There are %d black pixels. \n", total);
		memset(grid, false, sizeof(grid));
	}
	return 0;
}