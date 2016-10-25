#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll ans[25];
const ll MOD = 1e9;

int main()
{
//    freopen("Glenforest.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    ll N, LOGN;
    cin >> N;
    for (int i=1; i<=20; ++i){
        ans[i] = ans[i-1] + 9*pow(10, (i-1)/2);
        ans[i]%=MOD;
    }
    if (N > 20){
        cout << ans[20];
    }
    else{
        cout << ans[N];
    }
    return 0;
}