#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll damage[1000010], queries[1000010];
vector<ll> Qs;
unordered_map<ll, int> ans;

int main()
{
//    freopen("WC.txt","r",stdin);
    cin.sync_with_stdio(0);
    int N, M;
    cin >> N >> M;

    for (int i=1; i<=N; ++i){
        cin >> damage[i];
        damage[i] += damage[i-1];
    }
    for (int i=1; i<=M; ++i){
        cin >> queries[i];
        Qs.push_back(queries[i]);
    }
    sort(Qs.begin(), Qs.end());
    int j=0;
    for (int i=1; i<=N; ++i){
        int dmg = Qs[j];
        while (dmg +  damage[i] < 0 && j < M){
            ans[Qs[j]] = i-1;
            dmg = Qs[++j];
        }
    }
    for (; j < Qs.size(); ++j){
        ans[Qs[j]] = N;
    }
    for (int i=1; i<=M; ++i){
        printf("%d\n", ans[queries[i]]);
    }
    return 0;
}
