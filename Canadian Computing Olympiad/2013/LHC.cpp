#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MAXN = 400010;
int N, a, b;
long long dp[MAXN], node[MAXN], ans, cnt;
bool flag[MAXN];
vector<int> graph[MAXN];


void dfs(int n)
{
	flag[n] = true;
	for (int i = 0; i != graph[n].size(); ++i)
	{
		int v = graph[n][i];
		if (!flag[v])
		{
			dfs(v);
			long long temp = dp[v] + 1;
			if (temp + dp[n] > ans)
            {
                ans = temp + dp[n];
                cnt = node[n] * node[v];
            }
            else if (temp + dp[n] == ans)
            {
                cnt += node[n] * node[v];
            }
            if (temp > dp[n])
            {
                dp[n] = temp;
                node[n] = node[v];
            }
            else if (temp == dp[n])
            {
                node[n]+=node[v];
            }
		}
	}
}

int main()
{
    //freopen("LHC.txt","r",stdin);
	scanf("%d",&N);
	for (int i = 0; i != N; ++i)
	{
	    scanf("%d%d",&a,&b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	for (int i = 1; i <= N; ++i)
	{
	    node[i] = 1;
	}
	dfs(1);
	printf("%lld %lld", ans+1,cnt);
	return 0;
}
