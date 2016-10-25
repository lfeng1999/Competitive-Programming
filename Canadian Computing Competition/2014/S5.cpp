#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x7fffffff
#define mp make_pair
#define pb push_back
#define PII pair<int,int>
#define PIPII pair<int,pair<int,int>>
#define MAXN 2010

PII p[MAXN];
vector<PIPII> dpp;
int dist[MAXN], candy[MAXN], N, d, a, b, pcandy[MAXN];

int cdist(int i, int j)
{
	int dx = p[i].first - p[j].first;
	int dy = p[i].second - p[j].second;
	return dx*dx + dy*dy;
}

int main()
{
	scanf("%d", &N);
	p[0].first = p[0].second = 0;
	for (int i = 1; i <= N; ++i)
		scanf("%d%d", &p[i].first,&p[i].second);
	for (int i = 0; i <= N; ++i)
	for (int j = i + 1; j <= N; ++j)
		dpp.pb(mp(cdist(i, j), mp(i, j)));
	sort(dpp.begin(), dpp.end());
	for (int i = 0; i != dpp.size(); ++i)
	{
		d = dpp[i].first, a = dpp[i].second.first, b = dpp[i].second.second;
		if (d != dist[a])
		{
			dist[a] = d;
			pcandy[a] = candy[a];
		}
		if (d != dist[b])
		{
			dist[b] = d;
			pcandy[b] = candy[b];
		}
		candy[a] = max(candy[a], pcandy[b] + 1);
		if (a)
			candy[b] = max(candy[b], pcandy[a] + 1);
	}
	cout << candy[0];
	return 0;
}