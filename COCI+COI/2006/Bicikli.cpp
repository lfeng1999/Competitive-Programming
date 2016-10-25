#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000;
const int MAXN = 10001;
vector<int> graph[MAXN];
int dp[MAXN];
bool past[MAXN], pp;

bool bval(int x)
{
    if (x > MOD)
        return true;
    return false;
}

int bash(int node)
{
    if (node == 2)
        return 1;
    if (dp[node]!=-1)
        return dp[node];
    if (past[node])
        return 0;
    past[node] = true;
    int ans = 0;
    for (int i=0; i!=graph[node].size(); ++i){
        ans+=bash(graph[node][i]);
        pp = (pp || bval(ans));
        ans%=MOD;
    }
    pp = (pp || bval(ans));
    ans%=MOD;
    dp[node]=ans;
    return ans;
}


int main()
{
    cin.sync_with_stdio(false); cin.tie(0);
    int N,M;
    cin >> N >> M;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    memset(dp,-1,sizeof(dp));
    int ans = bash(1);
    if (pp)
        printf("%09d",ans);
    else
        printf("%d",ans);
    return 0;
}
