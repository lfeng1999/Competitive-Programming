#include <bits/stdc++.h>

using namespace std;

int N,M, val[100010], seg[300100],a,b, LL, RR;
char mv;

void build_tree(int node, int L, int R){
    if (L==R){
        seg[node] = val[L];
        return;
    }
    build_tree(node*2,L,(L+R)/2);
    build_tree(node*2+1,(L+R)/2+1,R);
    seg[node] = min(seg[node*2], seg[node*2+1]);
}
void update(int node, int pos, int L, int R){
    if (L==R){
        seg[node] = val[pos];
        return;
    }
    int mid = (L+R)/2;
    if (pos <= mid) update(node*2, pos, L, mid);
    else update(node*2+1,pos,mid+1,R);
    seg[node] = min(seg[node*2],seg[node*2+1]);
}
int query(int node, int L, int R){
    if (R < LL || RR < L) return 1e9;
    if (LL <= L && R <= RR) return seg[node];
    int mid = (L+R)/2;
    return min(query(node*2,L,mid), query(node*2+1,mid+1,R));
}

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i=0; i!=N; ++i)
        cin >> val[i];
    build_tree(1,0,N-1);
    for (int i=0; i!=M; ++i){
        cin >> mv >> LL >> RR;
        if (mv == 'Q')
            cout << query(1,0,N-1) << '\n';
        else if (mv == 'M'){
            val[LL] = RR;
            update(1,LL,0,N-1);
        }
    }
    return 0;
}
