#include <bits/stdc++.h>

using namespace std;

#define MAXLEN 610
#define MAXRECT 210
int dp[MAXLEN][MAXLEN];
bool valid[MAXLEN][MAXLEN];
int W,H,N;

int bash(){
    for (int i=1; i<=W; ++i){
        for (int j=1; j<=H; ++j){
            if (valid[i][j]){
                continue;
            }
            dp[i][j] = i*j;
            for (int k=1; 2*k <= i; ++k){
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i-k][j]);
            }
            for (int k=1; 2*k <= j; ++k){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j-k]);
            }
        }
    }
    return dp[W][H];
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> W >> H >> N;
    for (int i=0; i!=N; ++i){
        int w,h;
        cin >> w >> h;
        valid[w][h] = true;
    }
    cout << bash();
    return 0;
}
