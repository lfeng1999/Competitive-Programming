#include<bits/stdc++.h>

using namespace std;

long long dp[1000010], MOD, N, pow2[1000010];
string s;

int main()
{
    //freopen("lin3.in","r",stdin);
    cin.sync_with_stdio(0);
    cin >> N >> MOD >> s;
    //cout << N << " " << MOD << " " << s << endl;
    int minv = 0, maxv = 0, cnt = 0;
    for (int i=0; i!=s.length(); ++i){
        cnt+=(s[i] == 'L')?1:-1;
        minv = min(minv, cnt);
        maxv = max(maxv, cnt);
    }
    pow2[0] = 1;
    for (int i=1; i!= 1000010; ++i){
        pow2[i] = (pow2[i-1]*2)%MOD;
    }
    if (minv!=-1){
        dp[1] = (s[1] == 'L')?1:pow2[(N-2)/2]+1;
        for (int i = 3; i <=N-1; i+=2){
            if (s[i] == 'L'){
                dp[i] = dp[i-2];
            }
            else{
                dp[i] = (dp[i-2] + pow2[(N-i-1)/2]) % MOD;
            }
        }
        if (minv == 0){
            cout << dp[N-((N%2)?2:1)];
        }
        else{
            cout << (dp[N-((N%2)?2:1)] + pow2[N/2] + pow2[(N+1)/2] - 2)%MOD;
        }
    }
    else{
        dp[0] = (s[0] == 'L')?1:pow2[(N-1)/2] + 1;
        for (int i = 2; i <= N-1; i+=2){
            if (s[i] == 'L'){
                dp[i] = dp[i-2];
            }
            else{
                dp[i] = (dp[i-2] + pow2[(N-1-i)/2])%MOD;
            }
        }
        cout << (dp[N-((N%2)?1:2)] + pow2[N/2] - 1)%MOD;
    }
}
