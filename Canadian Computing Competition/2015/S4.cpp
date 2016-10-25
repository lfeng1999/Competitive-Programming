#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>

using namespace std;


int K, N, M, dp[2010][210], A, B, a, b, t, h;
vector< pair < int, pair< int, int > > > edges[2010];
#define rint(a) scanf("%d",&a)
#define rint2(a,b) scanf("%d%d", &a,&b)
#define rint3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define rint4(a,b,c,d) scanf("%d%d%d%d",&a,&b,&c,&d)

void recur(int a)
{
	queue< pair <int, int> > Q;
	Q.push(make_pair(a, K));
	dp[a][K] = 0;
	while (!Q.empty())
	{
		int node = Q.front().first, hull = Q.front().second; Q.pop();
		for (int i = 0; i != edges[node].size(); ++i)
		{
			int tnode = dp[node][hull];
			b = edges[node][i].first, t = edges[node][i].second.first, h = edges[node][i].second.second;
			//cout << dp[b][hull - h] << " ";
			if (hull > h && dp[b][hull - h] > tnode + t)
			{
				dp[b][hull - h] = tnode + t;
				Q.push(make_pair(b, hull - h));
			}

		}
	}
}

int main()
{
	memset(dp, 1000000, sizeof(dp));
	//ifstream file("CCCS4.txt");
	rint3(K,N,M);
	for (int i = 0; i != M; ++i)
	{
		rint4(a,b,t,h);
		edges[a].push_back(make_pair(b, make_pair(t, h)));
		edges[b].push_back(make_pair(a, make_pair(t, h)));
	}
	rint2(A,B);
	recur(A);
	int maxt = 1000000000;
	for (int i = 1; i <= K; ++i)
		maxt = min(maxt, dp[B][i]);
	if (maxt < 100000000)
		cout << maxt;
	else
		cout << -1;
	return 0;
}