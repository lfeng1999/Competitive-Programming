#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
const int MAX_N = 1e5 + 10;
ll N, R[MAX_N], L[MAX_N], H[MAX_N];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=0; i<N; ++i) cin >> R[i] >> L[i] >> H[i];
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    Q.push(make_pair(0, 0));
    ll mhappy = 0;
    for (int i=0; i<N; ++i){
        while (!Q.empty() && Q.top().first <= R[i]){
            mhappy = max(mhappy, Q.top().second);
            Q.pop();
        }
        Q.push(make_pair(R[i] + L[i], mhappy+H[i]));
    }
    while (!Q.empty()){
        mhappy = max(mhappy, Q.top().second);
        Q.pop();
    }
    cout << mhappy;

    return 0;
}
