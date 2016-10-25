#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF2 0x3f
#define INF 0x7fffffff
#define mp make_pair
#define pb push_back

int N, n, m[26][26], o[26][26], r[8] = {1,0,-1,0,0,1,0,-1};


void recur(int x, int y, int oxy)
{
	if (o[x][y] <= oxy)
		return;
	o[x][y] = oxy;
	for (int i = 0; i != 4; ++i)
	{
		int nx = x + r[i * 2], ny = y + r[i * 2 + 1];
		if (nx>=1 && nx <=n && ny >=1 && ny <=n)
		if (abs(m[x][y] - m[nx][ny]) <= 2)
		{
			if (m[x][y] > m[1][1] | m[nx][ny] > m[1][1])
				recur(nx, ny, oxy + 1);
			else
				recur(nx, ny, oxy);
		}
	}
}

int main()
{
	//ifstream file("MountainP.txt");
	scanf("%d", &N);
	while (N--)
	{
		memset(m, INF2, sizeof(m));
		memset(o, INF2, sizeof(o));
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &m[i][j]);
		recur(1, 1, 0);
		if (o[n][n] <= 100000)
			cout << o[n][n] << endl << endl;
		else
			cout << "CANNOT MAKE THE TRIP" << endl << endl;
	}
	return 0;
}