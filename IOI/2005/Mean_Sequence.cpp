#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
//    freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    ll v1 = 0, v2 = 0, dyn = 0, lo = -1e18, hi = 1e18;
    for (int i=0; i<N; ++i){
        cin >> v2;
        if (1^(i&1)){
            dyn += -v1 + v2;
            hi = min(hi, dyn);
        }
        else{
            dyn += v1 - v2;
            lo = max(lo, dyn);
        }

        swap(v1, v2);
    }
    if (hi >= lo)
        cout << hi - lo + 1;
    else
        cout << 0;
    return 0;
}
