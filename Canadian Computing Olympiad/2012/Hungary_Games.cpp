#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x7fffffff
#define MAXN 20010
#define pb push_back
#define mp make_pair

int N, M, A, B, L, dist[MAXN][2];
vector<pair<int, int>> edges[MAXN];

void spfa()
{
	queue<pair<int, int>> Q;
	Q.push(mp(1, 0));
	while (!Q.empty())
	{
		B = Q.front().first; L = Q.front().second; Q.pop();
		for (int i = 0; i != edges[B].size(); ++i)
		{
			int alt = L + edges[B][i].second;
			if (dist[edges[B][i].first][0] > alt)
			{
				dist[edges[B][i].first][1] = dist[edges[B][i].first][0];
				dist[edges[B][i].first][0] = alt;
				Q.push(mp(edges[B][i].first, dist[edges[B][i].first][0]));
			}
			else if (dist[edges[B][i].first][0] != alt && dist[edges[B][i].first][1] > alt)
			{
				dist[edges[B][i].first][1] = alt;
				Q.push(mp(edges[B][i].first, alt));
			}
		}
	}
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i != M; ++i)
	{
		scanf("%d%d%d", &A, &B, &L);
		edges[A].pb(mp(B, L));
	}
	for (int i = 0; i != MAXN; ++i)
	for (int j = 0; j != 2; ++j)
		dist[i][j] = INF;
	spfa();
	if (dist[N][1] == INF)
		cout << -1;
	else
		cout << dist[N][1];
	return 0;
}