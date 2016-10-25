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
const int MOD = 1000000007;
const int maxn = 2005;
const int INF = 1 << 30;
const int INF2 = 0x3f3f3f3f;
const int INF3 = 0x7fffffff;
#define mp make_pair
#define pb push_back
#define mset2(a) memset(a,-1,sizeof(a))
#define mset(a) memset(a,INF2,sizeof(a))
#define rint(x) scanf("%dist",&x)
#define rchar(x) scanf(" %c",&x)
#define rll(x) scanf("%lld",&x)
#define ssort(x) sort(x.begin(),x.end())

int N, M, po[10], pe, graph[102][102];
map<PII, int> animal, edgelen;

int prim(int n)
{
	bool vis[102];
	memset(vis, false, sizeof(vis));
	priority_queue<PII, vector<PII>, greater<PII>> Q;
	Q.push(mp(0, 0));
	long long siz = 0, nq = 1;
	while (!Q.empty() && nq<=n)
	{
		int len = Q.top().first;
		int node = Q.top().second;
		Q.pop();
		if (vis[node])
			continue;
		siz += len;
		nq++;
		vis[node] = true;
		for (int i = 0; i != n; ++i)
		{
			if (!vis[i])
			{
				Q.push(mp(graph[node][i], i));
			}
		}
		if (siz > INF)
			return INF;
	}
	return siz;
}

int main()
{
	mset(graph);
	//ifstream file("Animal Farm.txt");
	//file >> M;
	rint(M);
	for (int k = 0; k != M; ++k)
	{
		//file >> N;
		rint(N);
		for (int i = 0; i != N; ++i) rint(po[i]);
			//file >> po[i];
		po[N] = po[0];
		for (int i = 0; i != N; ++i)
		{
			//file >> pe;
			rint(pe);
			PII x = mp(min(po[i], po[i + 1]),max(po[i],po[i+1]));
			if (animal.count(x))
			{
				graph[animal[x]][k] = graph[k][animal[x]] = min(graph[animal[x]][k],edgelen[x]);
				animal.erase(x);
			}
			else
			{
				animal[x] = k, edgelen[x] = pe;
			}
		}
	}
	for (auto i : animal)
	if (edgelen[i.first] < graph[M][i.second])
		graph[M][i.second] = graph[i.second][M] = edgelen[i.first];

	cout << min(prim(M), prim(M + 1)) << endl;

	return 0;
}