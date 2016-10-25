#include <bits/stdc++.h>
using namespace std;
string seq;
int N,K;
long long dp[101][101][10];

long long solve(int l,int r,int pre)
{
    if (l>r) return 0;
    if (l==r)
    {
        if (pre>=K-1) return 1;
        else return 100000000;
    }
    if (dp[l][r][pre]!=-1) return dp[l][r][pre];
    long long &ans = dp[l][r][pre];
    ans = 100000000;
    if (pre == K-1) ans = 1+solve(l+1,r,0);
    for (int i=l+1;i<=r;i++)
    {
        if (seq[i]==seq[l])
        {
            ans = min(ans,solve(l+1,i-1,0) + solve(i,r,min(K-1,pre+1)));
        }

    }
    dp[l][r][pre] = ans;
    return ans;
}

int main()
{
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&N,&K);

    cin >> seq;
    int ans = solve(0,N-1,0);
    if (ans<=10000000) 
        cout << ans << endl;
    else cout << -1 << endl;
}