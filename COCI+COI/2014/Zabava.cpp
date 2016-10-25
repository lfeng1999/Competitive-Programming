#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int N, M, K, ppl[110];
ll dp[110][510];

ll solve(ll n, int k){
    k++;
    int large = n%k;
    int small = k - large;
    ll amt = n/k;
    return large*(amt+1)*(amt+2)/2 + small*(amt)*(amt+1)/2;
}

int main()
{
//    freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    for (int i=0; i<N; ++i){
        int v; cin >> v;
        ppl[v]++;
    }
    for (int i=1; i<=M; ++i){
        for (int j=0; j<=K; ++j){
            ll &ans = dp[i][j] = 1e9;
            for (int k=0; k<=j; ++k){
                ans = min(ans, dp[i-1][j-k] + solve(ppl[i], k));
            }
        }
    }
    cout << dp[M][K];
    return 0;
}