#include <bits/stdc++.h>

using namespace std;

int num[100010], dp[100010], counter[10000];

int main()
{
    //freopen("IOI.txt","r",stdin);
    int N, T;
    cin >> N >> T;
    int maxc = 0;
    for (int i=0; i!=N; ++i){
        cin >> num[i];
        counter[num[i]]++;
        maxc = max(maxc, counter[num[i]]);
    }
    for (int i = N; i<N*N; ++i){
        num[i] = num[i%N];
    }
    dp[0] = 1;
    for (int i=1; i<N*N; ++i){
        dp[i] = 1;
        for (int j = 1; j<=i && j <= N; ++j){
            if (num[i] >= num[i-j]){
                dp[i] = max(dp[i],dp[i-j] + 1);
            }
        }
        //cout << num[i] << " " << dp[i] << endl;
    }
    int maxv = 0;
    if (N*T <= N*N){
        for (int i=0; i!=N*T; ++i){
            maxv = max(dp[i], maxv);
        }
        cout << maxv;
    }
    else{
        for (int i=0; i!=N*N; ++i){
            maxv = max(dp[i], maxv);
        }
        cout << maxv + maxc*(T-N);
    }
    return 0;
}