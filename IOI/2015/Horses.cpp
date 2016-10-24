#include <bits/stdc++.h>

using namespace std;

struct Node{
    long long ans, modprod, L, R, maxlog, prodlog;
    double maxp, prod;
}seg[2000010];

const long long MOD = 1000000007;
long long growth[500010], price[500010], N, M;

void build_tree(int node, int L, int R){
    seg[node].L = L;
    seg[node].R = R;
    if (L == R){
        seg[node].prodlog = log10(growth[L]);
        seg[node].prod = (double)(growth[L])/pow(10,seg[node].prodlog);
        seg[node].modprod = growth[L]%MOD;
        seg[node].ans = (price[L]*growth[L])%MOD;
        seg[node].maxlog = log10(price[L]*growth[L]);
        seg[node].maxp = price[L]*growth[L]/pow(10, seg[node].maxlog);
        return;
    }
    build_tree(node*2, L, (L+R)/2);
    build_tree(node*2+1, (L+R)/2+1, R);
    seg[node].modprod = (seg[node*2].modprod*seg[node*2+1].modprod)%MOD;
    seg[node].prodlog = seg[node*2].prodlog+seg[node*2+1].prodlog;
    seg[node].prod = seg[node*2].prod*seg[node*2+1].prod;
    if (seg[node].prod >= 10){
        seg[node].prod/=10;
        seg[node].prodlog++;
    }
    double Rmaxp = seg[node*2+1].maxp*seg[node*2].prod, Rmaxlog = seg[node*2+1].maxlog+seg[node*2].prodlog;
    if (Rmaxp >= 10){
        Rmaxp/=10;
        Rmaxlog++;
    }
    if ((Rmaxlog > seg[node*2].maxlog) || (Rmaxlog == seg[node*2].maxlog && Rmaxp > seg[node*2].maxp)){
        seg[node].maxp = Rmaxp;
        seg[node].maxlog = Rmaxlog;
        seg[node].ans = (seg[node*2+1].ans*seg[node*2].modprod)%MOD;
    }
    else{
        seg[node].maxp = seg[node*2].maxp;
        seg[node].maxlog = seg[node*2].maxlog;
        seg[node].ans = seg[node*2].ans;
    }
}

void update(int node, int pos){
    int L = seg[node].L, R = seg[node].R;
    if (L == R){
        seg[node].prodlog = log10(growth[L]);
        seg[node].prod = (double)(growth[L])/pow(10,seg[node].prodlog);
        seg[node].modprod = growth[L]%MOD;
        seg[node].ans = (price[L]*growth[L])%MOD;
        seg[node].maxlog = log10(price[L]*growth[L]);
        seg[node].maxp = price[L]*growth[L]/pow(10, seg[node].maxlog);
        return;
    }
    if (pos <= (L+R)/2) update(node*2,pos);
    else update(node*2+1,pos);
    seg[node].modprod = (seg[node*2].modprod*seg[node*2+1].modprod)%MOD;
    seg[node].prodlog = seg[node*2].prodlog+seg[node*2+1].prodlog;
    seg[node].prod = seg[node*2].prod*seg[node*2+1].prod;
    if (seg[node].prod >= 10){
        seg[node].prod/=10;
        seg[node].prodlog++;
    }
    double Rmaxp = seg[node*2+1].maxp*seg[node*2].prod, Rmaxlog = seg[node*2+1].maxlog+seg[node*2].prodlog;
    if (Rmaxp >= 10){
        Rmaxp/=10;
        Rmaxlog++;
    }
    if ((Rmaxlog > seg[node*2].maxlog) || (Rmaxlog == seg[node*2].maxlog && Rmaxp > seg[node*2].maxp)){
        seg[node].maxp = Rmaxp;
        seg[node].maxlog = Rmaxlog;
        seg[node].ans = (seg[node*2+1].ans*seg[node*2].modprod)%MOD;
    }
    else{
        seg[node].maxp = seg[node*2].maxp;
        seg[node].maxlog = seg[node*2].maxlog;
        seg[node].ans = seg[node*2].ans;
    }
}

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=0; i < N; ++i) cin >> growth[i];
    for (int i=0; i < N; ++i) cin >> price[i];
    build_tree(1,0,N-1);
    printf("%lld\n",seg[1].ans);
    cin >> M;
    for (int i=0; i < M; ++i){
        int type, pos, val;
        cin >> type >> pos >> val;
        if (type == 1) growth[pos] = val;
        else price[pos] = val;
        update(1,pos);
        printf("%lld\n",seg[1].ans);
    }
    return 0;
}
