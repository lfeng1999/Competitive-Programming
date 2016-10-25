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
#define INF 1000000
#define mp make_pair
#define pb push_back

int graph[301][2], val[301], dp[301][601], childs[301], bsize[301], colour[301];

int dfs(int n)
{
	val[n] = colour[n];
	bsize[n] = 1;
	for (int i = 0; i != childs[n]; ++i)
	{
		val[n] += dfs(graph[n][i]);
		bsize[n] += bsize[graph[n][i]];
	}
	return val[n];
}

int recur(int n, int d)
{
	if (d < -bsize[n] | d > bsize[n])
		return INF;
	else if (val[n] == d)
		return 0;
	else if (d == 0)
		return 1;
	else if (dp[n][300 + d])
		return dp[n][300 + d];
	int best = INF;
	if (childs[n] == 1)
		best = min(best, recur(graph[n][0], d - colour[n]));
	else if (childs[n] == 2)
	{
		int mk = d - bsize[n];
		if (d>=0)
			for (int i = mk; i <= bsize[n] ; ++i)
				best = min(best, recur(graph[n][0], d - i - colour[n]) + recur(graph[n][1], i));
		else
			for (int i = -bsize[n]; i <= -mk; ++i)
				best = min(best, recur(graph[n][0], d - i - colour[n]) + recur(graph[n][1], i));

	}
	dp[n][300 + d] = best;
	return best;
}

int main()
{
	//ifstream file("TreePruning.txt");
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 0; i != N; ++i)
	{
		int id, col, C, child;
		scanf("%d%d%d", &id, &col, &C);
		if (col == 0)
			col = -1;
		colour[id] = col;
		childs[id] = C;
		for (int i = 0; i != C; ++i)
			scanf("%d", &graph[id][i]);
	}
	dfs(0);
	int ans = recur(0, M);
	if (ans < INF)
		cout << ans;
	else
		cout << -1;
	return 0;
}