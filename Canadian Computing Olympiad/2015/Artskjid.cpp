#include <bits/stdc++.h>

using namespace std;

typedef bitset<19> Mask;
typedef pair<int, pair<int,int> > pipii;
//          distance, node, bitset
int N,M,dp[19][1<<19];
int bsize[1<<19];
bool past[19][1<<19];
vector<pair<int,int> > graph[20];

struct pipiicmp
{
    bool operator()( const pair<int,pair<int,int> > &a,const pair<int,pair<int,int> > &b) const
    {
        int x1 = bsize[a.second.second], x2 = bsize[b.second.second];
        if (x1 < x2)
            return false;
        else if (x1 > x2)
            return true;
        return (a.first < b.first);
    }
};

int main()
{
    memset(dp,0,sizeof(dp));
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    int power[20];
    int tot = 1;
    for (int i=0; i<=19; ++i)
    {
        power[i]=tot;
        tot*=2;
    }
    for (int i=0; i!=(1<<19); ++i)
    {
        Mask x =i;
        bsize[i] = x.count();
    }
    scanf("%d%d",&N,&M);
    for (int i=0; i!=M; ++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        graph[a].push_back(make_pair(c,b));
    }
    priority_queue<pipii,vector<pipii>, pipiicmp> Q;
    Q.push(make_pair(0,make_pair(0,1)));
    int maxd = 0;
    while (!Q.empty())
    {
        int node = Q.top().second.first, dist = Q.top().first, pp = Q.top().second.second;Q.pop();
        if (past[node][pp]) continue;
        if (node == N-1)
        {
            if (dist > maxd)
                maxd = dist;
            continue;
        }
        Mask x = pp;
        past[node][pp] = true;
        for (int i=0; i!=graph[node].size(); ++i)
        {
            int v = graph[node][i].second, d = graph[node][i].first;
            if (!x[v] && dp[v][pp+power[v]] < d+dist)
            {
                dp[v][pp+power[v]] = d+dist;
                Q.push(make_pair(d+dist,make_pair(v,pp+power[v])));
            }
        }
    }
    cout << maxd;
}