#include <bits/stdc++.h>

using namespace std;

int N, acc[500010], accuse[500010], ans = 0;
bool past[500010];

void solve(int v, int is_mafia){
    if (past[v]) return;
    past[v] = true;
    ans += is_mafia;
    int u = accuse[v];
    acc[u]--;

    if (acc[u] == 0 || is_mafia){
        solve(u, 1^is_mafia);
    }
}

int main()
{
//    freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        int u;
        cin >> u;
        acc[u]++;
        accuse[i] = u;
    }
    for (int v=1; v<=N; ++v){
        if (acc[v]==0){
            solve(v, 1);
        }
    }
    for (int v=1; v<=N; ++v){
        if (!past[v]){
            solve(v, 0);
        }
    }
    cout << ans;
    return 0;
}