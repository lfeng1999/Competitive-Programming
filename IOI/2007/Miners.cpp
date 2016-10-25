#include <bits/stdc++.h>

using namespace std;

int N, dp[2][4][4][4][4], f[100010], cal;
//      2nd last, last, 2nd last, last
int sum(int i, int j, int k){
    int tot = (1 << i) | (1 << j) | (1 << k);
    tot/=2;
    return __builtin_popcount(tot);
}

int main()
{
//    freopen("IOI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;

    for (int i = 0; i < N; ++i){
        char ch; cin >> ch;
        f[i] = (ch == 'M') ? 1 : (ch == 'F') ? 2 : 3;
    }

    for (int i = N - 1; i >= 0; --i){

        for (int j = 0; j < 4; ++j){
            for (int k = 0; k < 4; ++k){
                for (int l = 0; l < 4; ++l){
                    for (int m = 0; m < 4; ++m){
                        dp[1&i][j][k][l][m] = max(dp[1^(1&i)][j][k][m][f[i]] + sum(f[i], l, m), dp[1^(1&i)][k][f[i]][l][m] + sum(f[i], j, k));
                    }
                }
            }
        }
    }

    cout << dp[0][0][0][0][0];



    return 0;
}
