#include <bits/stdc++.h>

using namespace std;

int N,C;
int cost[1000000], dp[1000000], dp2[1000000];
//        state    sold everything, bought one
int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(dp,0,sizeof(dp));
    memset(cost,0,sizeof(cost));
    cin >> N >> C;
    C*=2;
    for (int i=0; i!=N; ++i)
    {
        double a;
        cin >> a;
        cost[i]=a*1000+0.1;
    }
    dp2[0] = -cost[0];
    for (int i=1; i!= N; ++i)
    {
        dp[i] = max(dp[i-1], dp2[i-1] + cost[i] - C);
        dp2[i] = max(dp2[i - 1], dp[i]-cost[i]);
    }
    cout << dp[N-1];
}
