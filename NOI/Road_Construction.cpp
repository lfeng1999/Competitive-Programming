#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1000010;
int n, a, b, c;
vector<pair<int,int>> graph[MAXN];
bool passed[MAXN];
long long tot, cost[MAXN];

int dfs(int node)
{
	passed[node] = true;
	int temp = 1;
	for (int i = 0; i != graph[node].size(); ++i)
	{
		int v = graph[node][i].first;
		long long d = graph[node][i].second;
		if (!passed[v])
		{
			int t = dfs(v);
			tot += d*abs(t - (n - t));
			//cout << node << " " << v << " " << d*abs(t - (n - t)) << " " << t << endl;
			temp += t;
		}
	}
	return temp;
}

int main()
{
	//freopen("NOIRoadConstruction.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i != n-1; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		graph[a].push_back(make_pair(b, c));
		graph[b].push_back(make_pair(a, c));
	}
	dfs(1);
	cout << tot;
	return 0;
}