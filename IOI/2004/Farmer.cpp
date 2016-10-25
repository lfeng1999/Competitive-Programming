#include <bits/stdc++.h>

using namespace std;

int dp[150010];

int main()
{
//    freopen("IOI.txt","r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    int Q, M, K;
    cin >> Q >> M >> K;
    dp[0] = 0;
    for (int i=0; i<M; ++i){
        int F; cin >> F;
        for (int j=Q-1; j > Q-F && j >= 0; --j){
            dp[Q] = max(dp[Q], dp[j] + Q - j - 1);
        }
        for (int j=Q-F; j>=0; --j){
            dp[j+F] = max(dp[j+F], dp[j] + F);
        }
    }
    for (int i=0; i<K; ++i){
        int F; cin >> F;
        for (int j=Q-1; j > Q-F && j >= 0; --j){
            dp[Q] = max(dp[Q], dp[j] + Q - j - 1);
        }
        for (int j=Q-F; j>=0; --j){
            dp[j+F] = max(dp[j+F], dp[j] + F - 1);
        }
    }

    printf("%d\n", dp[Q]);

    return 0;
}
