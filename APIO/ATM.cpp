#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <cstring>
#include <queue>
#include <functional>

using namespace std;

const int MAXN = 500010;
vector<int> graph[MAXN], rgraph[MAXN], sccgraph[MAXN];
stack<int> stk;
int N, M, S, P, a, b, money[MAXN], scc[MAXN], cost[MAXN];
bool used[MAXN], past[MAXN], pub[MAXN], spub[MAXN];
long long dp[MAXN];

void dfs(int node)
{
	past[node] = true;
	for (int i = 0; i != graph[node].size(); ++i)
	{
		if (!past[graph[node][i]])
			dfs(graph[node][i]);
	}
	stk.push(node);
}

void rdfs(int node, int SCC)
{
	past[node] = true;
	for (int i = 0; i != rgraph[node].size(); ++i)
	{
		if (!past[rgraph[node][i]])
			rdfs(rgraph[node][i], SCC);
	}
	scc[node] = SCC;
}
int bash(int node)
{
	if (node == scc[S])
		return cost[node];
	if (dp[node])
		return dp[node];
	if (sccgraph[node].size() == 0)
		return -1;
	int ans = cost[node];
	for (int i = 0; i != sccgraph[node].size(); ++i)
	{
		ans = max(ans, cost[node] + bash(sccgraph[node][i]));
	}
	if (ans==cost[node])
	{
	    dp[node]=-1;
	    return -1;
	}
	dp[node]=ans;
	return ans;
}

int main()
{
	//freopen("ATMMachine.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0; i != M; ++i)
	{
		scanf("%d%d", &a, &b);
		graph[a].push_back(b);
		rgraph[b].push_back(a);
	}
	for (int i = 1; i <= N; ++i) scanf("%d", &money[i]);
	scanf("%d%d", &S, &P);
	for (int i = 0; i != P; ++i)
	{
		scanf("%d", &a);
		pub[a] = true;
	}
	for (int i = 1; i <= N; ++i)
	if (!past[i])
		dfs(i);
	int t = 0;
	memset(past, false, sizeof(past));
	while (!stk.empty())
	{
		int node = stk.top(); stk.pop();
		if (!past[node])
			rdfs(node, ++t);
	}
	for (int i = 1; i <= N; ++i)
	{
		if (pub[i])
			spub[scc[i]] = true;
		cost[scc[i]] += money[i];
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j != graph[i].size(); ++j)
		{
			if (scc[i] != scc[graph[i][j]])
				sccgraph[scc[graph[i][j]]].push_back(scc[i]);
		}
	}
	for (int i = 1; i <= N; ++i)
	{
		sort(sccgraph[i].begin(), sccgraph[i].end());
		sccgraph[i].erase(unique(sccgraph[i].begin(), sccgraph[i].end()), sccgraph[i].end());
	}
	int mcost = 0;
	for (int i = 1; i <= N; ++i)
	if (spub[i])
		mcost = max(mcost,bash(i));
	printf("%d\n", mcost);
}