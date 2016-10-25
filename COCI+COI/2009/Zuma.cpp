#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7fffffff;
int N, K, dp[101][101][6], num[101];

int solve(int L, int R, int B)
{
    if (L > R)
        return 0;
    if (L == R)
        return K - B - 1;
    int &d = dp[L][R][B];
    if (d!=-1)
        return d;
    d = INF;
    if (B == K-1)
        d = solve(L+1,R,0);
    else if (B < K-1)
        d = solve(L,R,B+1) + 1;
    for (int i=L+1; i<=R; ++i)
    {
        if (num[i]!=num[L])
            continue;
        d = min(d, solve(L+1,i-1,0) + solve(i,R,min(B+1,K-1)));
    }
    return d;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i=0; i<=N; ++i)
        cin >> num[i];
    memset(dp,-1,sizeof(dp));
    printf("%d",solve(0,N-1,0));
}
