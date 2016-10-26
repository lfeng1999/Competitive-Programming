#include <bits/stdc++.h>

using namespace std;

long long nCk[1001][1001];
const int MOD = 1000000007;

int main()
{
    for (int i=0; i!=1001; ++i){
        nCk[i][0] = 1;
    }
    for (int i=1; i!=1001; ++i){
        for (int j=1; j!=1001; ++j){
            nCk[i][j] = (nCk[i-1][j-1] + nCk[i-1][j])%MOD;
        }
    }
    int n;
    cin >> n;
    int cnt = 0;
    long long ans = 1;
    for (int i=0; i!=n; ++i){
        int x;
        cin >> x;
        ans*=nCk[cnt+x-1][cnt];
        ans%=MOD;
        cnt+=x;
    }
    cout << ans;
    return 0;
}