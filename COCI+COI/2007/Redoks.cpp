#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

struct Node{
    int L, R, dial[10], lazy;
} seg[530010];

int dials[250010], N, M;

void build_tree(int v, int L, int R){
    seg[v].L = L, seg[v].R = R;
    if (L == R){
        seg[v].dial[dials[L]]++;
        return;
    }
    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2 + 1, R);
    for (int i=0; i < 10; ++i){
        seg[v].dial[i] = seg[v*2].dial[i] + seg[v*2+1].dial[i];
    }
}

void rotate_dial(int v, int amt){
    int dial2[10];
    for (int i=0; i<10; ++i){
        dial2[(i+amt)%10] = seg[v].dial[i];
    }
    for (int i=0; i<10; ++i){
        seg[v].dial[i] = dial2[i];
    }
}

void push_lazy(int v){
    rotate_dial(v, seg[v].lazy);

    if (seg[v].L != seg[v].R){
        seg[v*2].lazy += seg[v].lazy;
        seg[v*2+1].lazy += seg[v].lazy;
    }
    seg[v].lazy = 0;
}

void update(int v, int LL, int RR, int val){
    push_lazy(v);
    if (seg[v].R < LL || RR < seg[v].L) return;

    if (LL <= seg[v].L && seg[v].R <= RR){
        rotate_dial(v, val);
        if (seg[v].L != seg[v].R){
            seg[v*2].lazy += val;
            seg[v*2+1].lazy += val;
        }
        return;
    }
    update(v*2, LL, RR, val);
    update(v*2+1, LL, RR, val);

    for (int i=0; i<10; ++i){
        seg[v].dial[i] = seg[v*2].dial[i] + seg[v*2+1].dial[i];
    }
}

int query(int v, int LL, int RR){
    push_lazy(v);
    if (seg[v].R < LL || RR < seg[v].L) return 0;

    if (LL <= seg[v].L && seg[v].R <= RR){
        int ans = 0;
        for (int i=0; i<10; ++i){
            ans += seg[v].dial[i] * i;
//            cout << seg[v].dial[i] * i << endl;
        }
        return ans;
    }

    int ans = query(v*2, LL, RR) + query(v*2+1, LL, RR);
    return ans;
}

int main(){
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;

    for (int i=0; i<N; ++i){
        char ch; cin >> ch;
        dials[i] = ch - '0';
    }
    build_tree(1, 0, N - 1);
    for (int i=0; i<M; ++i){ // fix
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << query(1, a, b) << endl;
        update(1, a, b, 1);

    }
    return 0;
}
