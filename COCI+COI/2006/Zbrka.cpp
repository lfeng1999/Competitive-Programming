#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
int dp[1001][10001];

int solve(int n, int c)
{
    if (c == 0)
        return 1;
    if (n==0)
        return 0;
    if (dp[n][c]!=-1)
        return dp[n][c];
    long long tot = (solve(n,c-1) + solve(n-1,c))%MOD;
    if (c >= n)
        tot -= solve(n-1,c-n);
    tot+=2*MOD;
    tot%=MOD;
    dp[n][c]=tot;
    return tot;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    int N,C;
    cin >> N >> C;
    memset(dp,-1,sizeof(dp));
    cout << solve(N,C);
    return 0;
}
