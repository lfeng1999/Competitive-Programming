#include <bits/stdc++.h>

using namespace std;

int N, Q, arr[200001][16], tree[300001][16], orig[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

void build_tree(int node, int L,int R)
{
    if (L==R)
    {
        for (int i=0; i!=16; ++i)
            tree[node][i] = arr[L][i];
        return;
    }
    build_tree(node*2,L,(L+R)/2);
    build_tree(node*2+1,(L+R)/2+1,R);

    for (int i=0; i!=16; ++i)
        tree[node][i] = tree[node*2][tree[node*2+1][i]-1];
}
void update(int node, int L, int R, int pos)
{
    if (L==R)
    {
        for (int i=0; i!=16; ++i)
            tree[node][i] = arr[L][i];
        return;
    }
    if (pos<=(L+R)/2)
        update(node*2,L,(L+R)/2,pos);
    else
        update(node*2+1,(L+R)/2+1,R,pos);
    for (int i=0; i!=16; ++i)
        tree[node][i] = tree[node*2][tree[node*2+1][i]-1];
}


void gen(int r, int c, int s, int pos)
{
    for (int i=0; i!=16; ++i)
        arr[pos][i]=orig[i];
    if (s==1)
    {
        return;
    }
    int p1 = r*4+c, p2 = r*4+c+s-1;
    int p3 = (r+s-1)*4+c, p4 = (r+s-1)*4+c+s-1;
    int temp = arr[pos][p2];
    for (int i=p2; i>p1; --i)
        arr[pos][i] = arr[pos][i-1];
    for (int i=p1; i<p3; i+=4)
        arr[pos][i] = arr[pos][i+4];
    for (int i=p3; i<p4; ++i)
        arr[pos][i] = arr[pos][i+1];

    for (int i=p4; i>p2; i-=4)
        arr[pos][i] = arr[pos][i-4];
    arr[pos][p2+4] = temp;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> N >> Q;
    for (int i=0; i!=N; ++i)
    {
        int a,b,c;
        cin >> a >> b >> c;
        gen(--a,--b,c,i);
    }
    build_tree(1,0,N-1);
    for (int i=0; i!=Q; ++i)
    {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        gen(--b,--c,d,--a);
        update(1,0,N-1,a);
        for (int i=0; i!=4; ++i)
        {
            for (int j=0; j!=4; ++j)
                printf("%d ",tree[1][i*4+j]);
            printf("\n");
        }
    }

}
