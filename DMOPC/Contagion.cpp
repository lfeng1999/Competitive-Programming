#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
pll counts[3010];
ll S[3010], sdist[3010];
bool past[3010];


ll ptdist(int i, int j){
    return (counts[i].first - counts[j].first)*(counts[i].first - counts[j].first) + (counts[i].second - counts[j].second)*(counts[i].second - counts[j].second);
}

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<3010; ++i){
        sdist[i] = 1e18;
    }
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        cin >> counts[i].first >> counts[i].second;
    }
    int X, QQ, cnt = 0;
    cin >> X >> QQ;


    int v = X-1;
    sdist[v] = 0;
    while (cnt!=N){
        ll t = sdist[v];

        past[v] = true;
        S[cnt++] = t;
        for (int i=0; i<N; ++i){
            if (i == v || past[i]) continue;
            ll nd = ptdist(i,v) + t;
            if (nd < sdist[i])
                sdist[i] = nd;
        }
        ll mint = 1e18;
        for (int i=0; i<N; ++i){
            if (!past[i] && sdist[i] < mint){
                mint = sdist[i];
                v=i;
            }
        }
    }
//    for (int i=0; i<N; ++i) cout << S[i] << " ";
//    cout << endl;
    while (QQ--){
        ll t;
        cin >>t;
        int p = upper_bound(S, S+cnt, t) - S - 1;
        printf("%d\n",p+1);

    }

    return 0;
}
