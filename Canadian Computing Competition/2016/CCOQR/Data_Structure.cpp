#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
vector<pair<ll,ll>> V;

bool mysort(pair<ll,ll> a, pair<ll,ll> b){
    if (a.first + a.second > b.first + b.second) return true;
    else if(a.first + a.second == b.first + b.second) return a.first > b.first;
    return false;
}

int main()
{
    //freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    ll N; int M;
    cin >> N >> M;

    for (int i=0; i<M; ++i){
        ll r, c;
        cin >> r >> c;
        V.push_back(make_pair(N+1-r, c));
    }
    sort(V.begin(), V.end(), mysort);

    stack<pair<int,int>> S;
    ll tot = 0;
    for (int i=0; i<M; ++i){
        ll r = V[i].first, c = V[i].second;
        while (i + 1 < M && V[i+1].first + V[i+1].second == r + c){
            i++;
        }
        if (S.empty()){
            tot += (1+r)*r/2;
            S.push(make_pair(r, c));
            continue;
        }

        ll r0 = S.top().first, c0 = S.top().second;
        if ( r < r0 && c >= c0){continue;}
        tot += (1+r)*r/2;

        ll r2 = r + c - c0, c2 = c;

        if (r2 < 1) continue;

        tot -= (1+r2)*r2/2;


        S.push(make_pair(r, c));
    }
    cout << tot;

    return 0;
}