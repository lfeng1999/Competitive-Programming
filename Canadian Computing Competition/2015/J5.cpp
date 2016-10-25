#include <bits/stdc++.h>

using namespace std;

int dp[251][251];

int main()
{
    int N, K;
    cin >> N >> K;
    for (int i=0; i <= N; ++i) dp[i][1] = 1;
    for (int i=1; i <= K; ++i) dp[0][i] = dp[1][i] = 1;
    for (int i=2; i <= N; ++i){
        for (int j=2; j <= K; ++j){
            for (int k=0; k < i/j + 1; k++){
                dp[i][j]+=dp[i-j*k][j-1];
            }
        }
    }
    cout << dp[N-K][K];
}
