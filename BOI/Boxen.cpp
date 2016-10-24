#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

bool past[100010];
int N,n;
vector<int> graph[100010];

void dfs(int node)
{
	past[node] = true;
	for (int i = 0; i != graph[node].size(); ++i)
	if (!past[graph[node][i]])
		dfs(graph[node][i]);
}

int main()
{
	//freopen("Boxen.txt", "r", stdin);
	for (int qq = 0; qq != 2; ++qq)
	{
		int cost = 0;
		scanf("%d",&N);
		for (int i = 1; i <= N; ++i)
		{
		        scanf("%d",&n);
			graph[n].push_back(i);
			graph[i].push_back(n);
		}
		for (int i = 1; i <= N; ++i)
		{
			if (!past[i])
			{
				++cost;
				dfs(i);
			}
		}
		cout << cost << " ";

		for (int i = 1; i <= 100000; ++i)
			graph[i].clear();
		memset(past, false, sizeof(past));
	}
	return 0;
}