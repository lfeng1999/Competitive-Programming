#include <bits/stdc++.h>

using namespace std;

vector<int> n, drums;
int T[110], P[110], diff[500][500];
double dp[110][500];

int main()
{
//    freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N,D;
    cin >> N >> D;
    for (int i=0; i!=N; ++i){
        cin >> T[i] >> P[i];
        P[i]--;
    }
    for (int i = 0; i != 1 << 12; ++i){
        if (__builtin_popcount(i) == D){
            drums.push_back(i);
        }
    }
    int S = drums.size();
    for (int i=0; i != S; ++i){
        for (int j=0; j!=S; ++j){
            vector<int> v,u;
            for (int k = 0; k!=12; ++k){
                if (1 << k & drums[i]){
                    v.push_back(k);
                }
                if (1 << k & drums[j]){
                    u.push_back(k);
                }
            }
            for (int k=0; k!=D; ++k){
                if (v[k] != u[k]){
                    diff[i][j]++;
                }
            }
        }
    }
    for (int i=0; i!=110; ++i){
        fill(dp[i], dp[i] + 500, -1e10);
    }
    for (int i=0; i!=S; ++i){
        if (1 << P[0] & drums[i]){
            dp[0][i] = 1e10;
        }
    }
    for (int i=1; i!=N; ++i){
        for (int fr=0; fr!=S; ++fr){
            for (int to=0; to!=S; ++to){
                if (1 << P[i] & drums[to]){
                    dp[i][to] = max(dp[i][to], min(dp[i-1][fr], diff[fr][to] == 0? 1e10: 1.0*(T[i]-T[i-1])/diff[fr][to]));
                }
            }
        }
    }
    double ans = *max_element(dp[N-1], dp[N-1] + 500);
    if (ans == 1e10){
        printf("%.2lf",0.00);
    }
    else{
        printf("%.2lf", ans);
    }
    return 0;
}
