#include <bits/stdc++.h>

using namespace std;

int V, P, vil[310], dist[310][310], dp[41][310], rev[41][310], pdist[310];

int main()
{
    //freopen("IOI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> V >> P;

    for (int i=1; i<=V; ++i){
        cin >> vil[i];
        pdist[i] = vil[i] + pdist[i-1];
    }

    for (int i=1; i<=V; ++i){
        for (int j=i+1; j<=V; ++j){
            int &ans = dist[i][j]; ans = 0;

            for (int k = i+1; k < j; ++k){
                ans += min(vil[k] - vil[i], vil[j] - vil[k]);
            }
            dist[j][i] = ans;
        }
    }

    for (int i=1; i<=V; ++i){
        dp[1][i] = dp[1][i-1] + (vil[i] - vil[i-1])*(i-1);
    }

    for (int i=2; i<=P; ++i){
        for (int j=i; j<=V; ++j){
            dp[i][j] = 1e9;
            for (int k = j-1; k >= i; k--){
                if (dp[i][j] > dp[i-1][k] + dist[k][j]){
                    dp[i][j] = dp[i-1][k] + dist[k][j];
                    rev[i][j] = k;
                }
            }
            if (dp[i][j] == 1e9) dp[i][j] = 0;
        }
    }


    int best = 1e9, bestidx;
    for (int i=P; i<=V; ++i){
        dp[P][i] += + (pdist[V] - pdist[i]) - vil[i] * (V - i);
        if (best > dp[P][i]){
            best = dp[P][i];
            bestidx = i;
        }
    }

    printf("%d\n", best);

    int ans[41];


    for (int i=P; i > 0; --i){
        ans[i] = bestidx;
        bestidx = rev[i][bestidx];
    }
    for (int i=1; i<=P; ++i){
        printf("%d ", vil[ans[i]]);
    }


    return 0;
}
