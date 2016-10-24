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
#include <functional>
#include <map>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF 1 << 30
#define INF2 0x3f3f3f3f
#define INF3 0x7fffffff
#define mp make_pair
#define pb push_back
#define MOD 1000000007]
#define mset(a) memset(a,-1,sizeof(a))
#define mset2(a) memset(a,INF2,sizeof(a))
#define rint(x) scanf("%dist",&x)
#define rchar(x) scanf(" %c",&x)
#define rll(x) scanf("%lld",&x)
#define ssort(x) sort(x.begin(),x.end())
#define maxn 102

int n, k, w[maxn], parent, dist[maxn], stree[maxn];
int dp[maxn][51][maxn];
vector<int> adj[maxn];

void cadist(int node, int dis)
{
	dist[node] = dis;
	for (int i = 0; i != adj[node].size(); ++i)
		cadist(adj[node][i], dis + dist[adj[node][i]]);
}

int gtree(int node)
{
	int siz = 1;
	for (int i = 0; i != adj[node].size(); ++i)
		siz += gtree(adj[node][i]);
	stree[node] = siz;
	return siz;
}

int cost(int node, int nmill, int lmill)
{
	if (nmill < 0)
		return INF;
	else if (nmill >= stree[node])
		return 0;
	else if (dp[node][nmill][lmill] != -1)
		return dp[node][nmill][lmill];
	int dp2[maxn][51];
	mset2(dp2);
	for (int i = 0; i <= nmill; ++i)
		dp2[0][i] = 0;
	for (int i = 1; i <= adj[node].size(); ++i)
	for (int j = 0; j <= nmill; ++j)
	for (int k = 0; k + j <= nmill; ++k)
	{
		dp[adj[node][i-1]][k][lmill] = min(cost(adj[node][i - 1], k - 1, adj[node][i - 1]), cost(adj[node][i - 1], k, lmill));
		dp2[i][k + j] = min(dp2[i][k + j], dp2[i - 1][j] + dp[adj[node][i - 1]][k][lmill]);
	}
	dp[node][nmill][lmill] = dp2[adj[node].size()][nmill] + (dist[node] - dist[lmill])*w[node];
	return dp[node][nmill][lmill];
}

int main()
{
	mset(dp);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", &w[i], &parent, &dist[i]);
		adj[parent].pb(i);
	}
	cadist(0, 0);
	gtree(0);
	cout << cost(0, k, 0);
	return 0;
}
