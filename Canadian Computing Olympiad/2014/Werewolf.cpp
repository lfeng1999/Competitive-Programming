#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;
#define mp make_pair
#define pb push_back

const int MOD = 1000000007;
const int MAXN = 210;

int N, W, M, stree[MAXN], stree2[MAXN], parent[MAXN];
long long dp[MAXN][MAXN][2];
vector<PII> edge[MAXN];
char a;
int b, c;
bool passed[MAXN];

int dfs2(int node)
{
	int tot = 1;
	for (int i = 0; i != edge[node].size(); ++i)
	{
		tot += dfs2(edge[node][i].first);
	}
	stree[node] = tot;
	return tot;
}

void dfs(int node)
{
	passed[node] = true;
	dp[node][0][0] = dp[node][1][1] = 1;
	for (int i = 0; i != edge[node].size(); ++i)
	{
		int child = edge[node][i].first, w = edge[node][i].second;
		if (!passed[child])
			dfs(child);
		for (int j = W; j >= 0; --j)
		{
			long long c1 = 0, c2 = 0;
			for (int k = 0; k <= j; ++k)
			{
				c1 += dp[node][j - k][0] * (dp[child][k][0] + dp[child][k][1]);
				c2 += dp[node][j - k][1] * dp[child][k][!w];
				c1 %= MOD;
				c2 %= MOD;
			}
			dp[node][j][0] = c1;
			dp[node][j][1] = c2;
		}
	}
}

int main()
{
	//ifstream file("Werewolf.txt");
	//file >> N >> W >> M;
	scanf("%d%d%d", &N, &W, &M);
	for (int i = 0; i != M; ++i)
	{
//		file >> a >> b >> c;
		scanf(" %c%d%d", &a, &b, &c);
		edge[b].pb(mp(c, int(a == 'A')));
		parent[c] = b;
	}
	for (int i = 1; i <= N; ++i)
	if (parent[i] == 0)
		edge[0].pb(mp(i, 0));
	//dfs2(0);
	dfs(0);
	cout << dp[0][W][0];
	return 0;
}