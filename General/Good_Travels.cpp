#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 1000005;
int N, M, S, E, fun[MAXN], scc[MAXN], dp[MAXN];
long long fun2[MAXN];
bool past[MAXN];
vector<int> graph[MAXN], rgraph[MAXN], graph2[MAXN];
stack<int> myorder;

void dfs(int node)
{
	past[node] = true;
	for (int i = 0; i != graph[node].size(); ++i)
	if (!past[graph[node][i]])
		dfs(graph[node][i]);
	myorder.push(node);
}

void rdfs(int node, int SCC)
{
	past[node] = true;
	for (int i = 0; i != rgraph[node].size(); ++i)
	if (!past[rgraph[node][i]])
		rdfs(rgraph[node][i], SCC);
	scc[node] = SCC;
}

long long bash(int node)
{
	if (dp[node])
		return dp[node];
	if (node == scc[E])
		return fun2[scc[E]];
	if (graph2[node].size() == 0)
		return -1;
	past[node] = true;
	long long temp = fun2[node];
	for (long long i = 0; i != graph2[node].size(); ++i)
	{
		temp = max(temp, fun2[node] + bash(graph2[node][i]));
	}
	if (temp == fun2[node])
		return -1;
	dp[node] = temp;
	return temp;
}

int main()
{
	//freopen("Good Travels.txt", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &S, &E);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", &fun[i]);
	}
	for (int i = 0; i != M; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		graph[a].push_back(b);
		rgraph[b].push_back(a);
	}
	for (int i = 1; i <= N; ++i)
	if (!past[i])
		dfs(i);
	memset(past, false, sizeof(past));
	int cnt = 0;
	while (!myorder.empty())
	{
		int node = myorder.top(); myorder.pop();
		if (!past[node])
			rdfs(node, ++cnt);
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j != graph[i].size(); ++j)
		{
			if (scc[i] != scc[graph[i][j]])
			{
				graph2[scc[i]].push_back(scc[graph[i][j]]);
			}
		}
	}
	for (int i = 1; i <= N; ++i)
	{
		fun2[scc[i]] += fun[i];
	}

//	cout << scc[1] << " " << scc[2] << " " << scc[3] << " " << scc[4] << endl;
	cout << bash(scc[S]);
	return 0;
}