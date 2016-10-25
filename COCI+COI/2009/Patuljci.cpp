#include <bits/stdc++.h>

using namespace std;

int N, C, col[650010], M, tree[650010];
vector<int> cpos[10001];

int cnt(int val, int L, int R)
{
    return upper_bound(cpos[val].begin(),cpos[val].end(), R) - lower_bound(cpos[val].begin(),cpos[val].end(), L);
}

void build_tree(int node, int L, int R)
{
    if (L==R)
    {
        tree[node] = col[L];
        return;
    }
    int avg = (L+R)/2;
    build_tree(node*2,L,avg);
    build_tree(node*2+1,avg+1,R);

    //cout << tree[2] << " " << tree[3] << endl;
    if (cnt(tree[node*2], L, R) > cnt(tree[node*2+1],L,R))
        tree[node] = tree[node*2];
    else
        tree[node] = tree[node*2 + 1];
}

int query(int node, int L, int R, int LL, int RR)
{//                looking for,     node left, right
    if (R < LL || L > RR)
        return 0;
    if (L <= LL  && RR <= R)
        return tree[node];
    int avg = (LL+RR)/2;
    int a = query(node*2, L, R, LL, avg), b = query(node*2+1, L, R, avg + 1, RR);
    if (a == b)
        return a;
    int aa = cnt(a,L,R), bb = cnt(b,L,R);
    if (aa > bb)
        return a;
    else
        return b;
}



int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> C;
    for (int i=1; i<=N; ++i)
    {
        cin >> col[i];
        cpos[col[i]].push_back(i);
    }
    build_tree(1,1,N);
    int M;
    cin >> M;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        int v = query(1,a,b,1,N);
        if (cnt(v,a,b) > (b-a+1)/2)
            printf("yes %d\n", v);
        else
            printf("no\n");
    }

}
