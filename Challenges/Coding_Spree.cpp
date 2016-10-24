#include <bits/stdc++.h>

using namespace std;

int dp[1001];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N,T;
    cin >> N >> T;
    for (int i=0; i!=N; ++i)
    {
        int v, h;
        cin >> v >> h;
        for (int j=T; j>=h; --j)
            dp[j] = max(dp[j-h]+v, dp[j]);
    }
    printf("%d",dp[T]);
}
