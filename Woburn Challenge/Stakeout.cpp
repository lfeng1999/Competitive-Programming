#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
typedef long long ll;
int houses[300010], N, M, queries, nspies[300010];
int agents[300010][2];

struct Node{
    int L, R, min_val, lazy;
} seg[1200010];


void build_tree(int v, int L, int R){
    seg[v].L = L, seg[v].R = R;
    seg[v].lazy = 0;
    if (L == R){
        seg[v].min_val = nspies[L];
        return;
    }
    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2 + 1, R);
    seg[v].min_val = min(seg[v*2].min_val, seg[v*2+1].min_val);
}

void push_lazy(int v){
    seg[v].min_val += seg[v].lazy;

    if (seg[v].L != seg[v].R){
        seg[v*2].lazy += seg[v].lazy;
        seg[v*2+1].lazy += seg[v].lazy;
    }

    seg[v].lazy = 0;
}

void update(int v, int LL, int RR, int val){
    push_lazy(v);
    if (LL <= seg[v].L && seg[v].R <= RR){
        seg[v].min_val += val;
        if (seg[v].L != seg[v].R){
            seg[v*2].lazy += val;
            seg[v*2+1].lazy += val;
        }
        return;
    }
    if (RR < seg[v].L || seg[v].R < LL) return;

    update(v*2, LL, RR, val);
    update(v*2 + 1, LL, RR, val);

    seg[v].min_val = min(seg[v*2].min_val, seg[v*2+1].min_val);
}

int query(int v, int LL, int RR){
    push_lazy(v);
    if (LL <= seg[v].L && seg[v].R <= RR){
        return seg[v].min_val;
    }
    if (seg[v].R < LL || RR < seg[v].L) return 1e9;

    return min(query(v*2, LL, RR), query(v*2+1, LL, RR));

}

ll pow2[300010];
const ll MOD = 1e9 + 7;

int main()
{
//    freopen("WoburnChallenge.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> queries;
    for (int i=0; i<N; ++i){
        cin >> houses[i];
    }
    sort(houses, houses + N);

    for (int i=1; i<=M; ++i){
        int A, R;
        cin >> A >> R;
        agents[i][0] = lower_bound(houses, houses + N, A - R) - houses;
        agents[i][1] = upper_bound(houses, houses + N, A + R) - houses - 1;

        nspies[agents[i][0]]++;
        nspies[agents[i][1] + 1]--;
    }
    for (int i=1; i<N; ++i){
        nspies[i] += nspies[i-1];
    }
    ll cur = 1;
    for (int i=0; i<=M; ++i){
        pow2[i] = cur;
        cur *= 2;
        cur %= MOD;
    }
    for (int qq = 0; qq < queries; qq++){ // fix

        int Q; cin >> Q;


        build_tree(1, 0, N - 1);


        if (query(1, 0, N - 1) < Q){
            cout << -1 << endl;
            continue;
        }

        ll ans = 0;
//        for (int i=1; i<=M; ++i){
//            cout << agents[i][0] << " " << agents[i][1] << endl;
//        }
//        cout << query(1, 0, 1) << endl;
        for (int i = M; i >= 1; --i){
            if (query(1, agents[i][0], agents[i][1]) > Q){
                update(1, agents[i][0], agents[i][1], -1);
            }
            else{
                ans += pow2[i];
                ans %= MOD;
            }
        }
        cout << ans << endl;

    }



    return 0;
}
