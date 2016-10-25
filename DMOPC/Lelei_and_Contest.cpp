#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Node{
    int L, R;
    ll sum, lazy = 0;
}seg[800010];
int MOD;
int M, N, Q, arr[200010];


void build_tree(int v, int L, int R){
    seg[v].L = L; seg[v].R = R;
    if (L == R){
        seg[v].sum = arr[L]%MOD;
        return;
    }
    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2+1, R);
    seg[v].sum = (seg[v*2].sum + seg[v*2+1].sum)%MOD;
    return;
}

void update_lazy(int v){
    seg[v].sum += (seg[v].R - seg[v].L + 1)*seg[v].lazy;
    seg[v].sum %= MOD;
    if (seg[v].L == seg[v].R){
        seg[v].lazy = 0;
        return;
    }
    seg[v*2].lazy += seg[v].lazy;
    seg[v*2+1].lazy += seg[v].lazy;
    seg[v].lazy = 0;
    return;
}

void update(int v, int L, int R, int val){
    if (R < seg[v].L || seg[v].R < L) return;
    update_lazy(v);
    if (L <= seg[v].L && seg[v].R <= R){
        seg[v].lazy += val;
        return;
    }
    seg[v].sum += (min(R, seg[v].R) - max(L, seg[v].L) + 1)*val;
    update(v*2, L, R, val);
    update(v*2+1, L, R, val);
    return;
}

int query(int v, int L, int R){
    if (R < seg[v].L || seg[v].R < L) return 0;
    update_lazy(v);
    if (L <= seg[v].L && seg[v].R <= R){
        return seg[v].sum;
    }
    return (query(v*2, L, R) + query(v*2+1, L, R))%MOD;

}

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> M >> N >> Q; MOD = M;

    for (int i=1; i<=N; ++i){
        cin >> arr[i];
    }
    build_tree(1, 1, N);
    while (Q--){
        int a, b, c, d;
        cin >> a;
        if (a == 1){
            cin >> b >> c >> d;
            update(1, b, c, d%MOD);
        }
        else{
            cin >> b >> c;
            printf("%d\n", query(1, b, c));
        }

    }

    return 0;
}