#include <bits/stdc++.h>

using namespace std;

int bcard[101], wcard[101], cap[202][202], source = 0, sink = 201;
bool past[202];
//source to black to white to sink
int GCD(int a,int b)
{
    if (b==0) return a;
    else return GCD(b,a%b);
}

int augment(int cur, int curflow)
{
    if (cur == sink)
        return curflow;
    past[cur] = true;
    for (int i=0; i<=sink; ++i)
    {
        if (cap[cur][i] && !past[i])
        {
            int flow = augment(i,min(cap[cur][i],curflow));
            if (flow > 0)
            {
                cap[cur][i]-=flow;
                cap[i][cur]+=flow;
                return flow;
            }
        }
    }
    return 0;
}

int max_flow()
{
    int flow = 0, mflow = 0;
    do
    {
        memset(past,false,sizeof(past));
        flow = augment(source,0x7fffffff);
        mflow+=flow;
    } while (flow > 0);
    return mflow;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N,M;
    cin >> N >> M;
    for (int i=1; i<=N; ++i)
    {
        cin >> bcard[i];
        cap[source][i]=1;
    }
    for (int i=1; i<=M; ++i)
    {
        cin >> wcard[i];
        cap[100+i][sink]=1;
    }
    for (int i=1; i<=N; ++i)
    {
        for (int j=1; j<=M; ++j)
        {
            if (GCD(max(bcard[i],wcard[j]), min(bcard[i],wcard[j])) != 1)
                cap[i][100+j] = 1;
        }
    }
    cout << max_flow()*2;
}
