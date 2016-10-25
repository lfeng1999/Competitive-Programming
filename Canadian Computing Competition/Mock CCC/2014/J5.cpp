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
#define INF 0x3f
#define INF2 0x7fffffff
#define mp make_pair
#define pb push_back

int R, C, T, t[12][102][102], At, Ax, Ay, Bt, Bx, By;
bool o[12][102][102];
int m[8] = { 1, 0, -1, 0, 0, 1, 0, -1 };

void bfs(int tim, int x, int y)
{
	queue<PIPII> Q;
	Q.push(mp(tim, mp(x, y)));
	while (!Q.empty())
	{
		int ti = Q.front().first, mx = Q.front().second.first, my = Q.front().second.second; Q.pop();
		int mtime = t[ti][mx][my] + 1;
		for (int i = 0; i != 4; ++i)
		{
			if (mtime < t[ti][mx + m[i * 2]][my + m[i * 2 + 1]] && !o[ti][mx + m[i * 2]][my + m[i * 2 + 1]])
			{
				t[ti][mx + m[i * 2]][my + m[i * 2 + 1]] = mtime;
				Q.push(mp(ti, mp(mx + m[i * 2], my + m[i * 2 + 1])));
			}
		}
		for (int i = 1; i <= T; ++i)
		if (mtime < t[i][mx][my] && !o[i][mx][my])
		{
			t[i][mx][my] = mtime;
			Q.push(mp(i, mp(mx, my)));
		}
	}
}


int main()
{
	memset(o, true, sizeof(o));
	scanf("%d%d%d", &R, &C, &T);
	for (int i = 1; i <= T; ++i)
	for (int j = 1; j <= R; ++j)
	for (int k = 1; k <= C; ++k)
	{
		t[i][j][k] = 220000000;
		char a;
		scanf(" %c", &a);
		if (a == 'A')
			Ax = j, Ay = k;
		else if (a == 'B')
			Bx = j, By = k;
		if (a != 'X')
			o[i][j][k] = false;
	}
	t[1][Ax][Ay] = 0;
	bfs(1, Ax, Ay);
	if (t[1][Bx][By] < 220000000)
		cout << t[1][Bx][By];
	else
		cout << -1;

	return 0;
}