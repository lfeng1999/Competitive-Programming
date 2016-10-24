#include <bits/stdc++.h>

using namespace std;

int N;

struct Node{
    int L, R, val = 0, lazy_min = -1, lazy_max = 1e9;
} seg[4500010];

void build_tree(int v, int L, int R){
    seg[v].L = L, seg[v].R = R;

    if (L == R){
        return;
    }

    build_tree(v*2, L, (L+R)/2);
    build_tree(v*2+1, (L+R)/2 + 1, R);
}

void set_max(int v, int val){
    seg[v].lazy_max = min(seg[v].lazy_max, val);
    seg[v].lazy_min = min(seg[v].lazy_min, val);
}

void set_min(int v, int val){
    seg[v].lazy_max = max(seg[v].lazy_max, val);
    seg[v].lazy_min = max(seg[v].lazy_min, val);
}

void push_lazy(int v){
    if (seg[v].L == seg[v].R){
        return;
    }
    set_min(v*2, seg[v].lazy_min);
    set_max(v*2, seg[v].lazy_max);
    set_min(v*2+1, seg[v].lazy_min);
    set_max(v*2+1, seg[v].lazy_max);
    seg[v].lazy_min = -1;
    seg[v].lazy_max = 1e9;
}

void update_max(int v, int L, int R, int H){
    if (R < seg[v].L || seg[v].R < L) return;

    push_lazy(v);
    if (L <= seg[v].L && seg[v].R <= R){
        set_max(v, H);
        return;
    }
    update_max(v*2, L, R, H);
    update_max(v*2 + 1, L, R, H);
}

void update_min(int v, int L, int R, int H){
    if (R < seg[v].L || seg[v].R < L) return;

    push_lazy(v);
    if (L <= seg[v].L && seg[v].R <= R){
        set_min(v, H);
        return;
    }
    update_min(v*2, L, R, H);
    update_min(v*2 + 1, L, R, H);
}

int ans[2000010][2];

void expand(int v){
    if (seg[v].L == seg[v].R){
        ans[seg[v].L][0] = seg[v].lazy_min;
        ans[seg[v].L][1] = seg[v].lazy_max;
        return;
    }
    push_lazy(v);
    expand(v*2);
    expand(v*2 + 1);
}

#define endl '\n'

int main()
{
//    freopen("CCO.in","r",stdin);
    int nCommands;
    scanf("%d%d", &N, &nCommands);
    build_tree(1, 0, N - 1);

    for (int qq=0; qq<nCommands; ++qq){
        int op, L, R, H;
        scanf("%d%d%d%d", &op, &L, &R, &H);
//        cout << op << " " << L << " " << R << endl;
        if (op == 1){
            update_min(1, L, R, H);
        }
        else{
            update_max(1, L, R, H);
        }
    }
    expand(1);
    for (int i=0; i<N; ++i){
        if (ans[i][0] == -1)
            cout << 0 << endl;
        else
            cout << ans[i][0] << endl;
    }


    return 0;
}
