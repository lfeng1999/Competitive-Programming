#include <bits/stdc++.h>

using namespace std;

int bit[100010];

void update(int x, int val)
{
    for (; x <= 100000; x+=x&-x)
        bit[x]+=val;
}

int query(int x)
{
    int tot = 0;
    for (; x > 0; x-=x&-x)
        tot+=bit[x];
    return tot;
}


int main()
{
    //freopen("COCI.txt","r",stdin);
    int N,L,R;
    scanf("%d",&N);
    for (int i=0; i!=N; ++i)
    {
        scanf("%d%d",&L,&R);
        int queryL = query(L), queryR = query(R);
        printf("%d\n",queryL+queryR);
        if (queryL)
        {
            update(L,-queryL);
            update(L+1,queryL);
        }
        if (queryR){
            update(R,-queryR);
            update(R+1,queryR);
        }
        update(L+1,1);
        update(R,-1);
    }
    return 0;
}
