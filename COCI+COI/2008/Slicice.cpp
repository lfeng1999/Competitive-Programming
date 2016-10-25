#include <bits/stdc++.h>

using namespace std;

const int source = 0, sink = 1101, MAXN2 = 100000000;
int capacity[1102][1102];
//int counter[102];
//int counter2[102];
bool past[1102];
vector<int> adj[1102];
vector<pair<int,int>> games;

int augment(int cur, int curflow)
{
    if (cur == sink)
        return curflow;
    past[cur] = true;
    for (int i=0; i!=adj[cur].size(); ++i)
    {
        int v = adj[cur][i];
        if (capacity[cur][v] && !past[v])
        {
            int flow = augment(v,min(capacity[cur][v],curflow));
            if (flow > 0)
            {
                capacity[cur][v]-=flow;
                capacity[v][cur]+=flow;
                return flow;
            }
        }
    }
    return 0;
}

int max_flow()
{
    int mflow = 0,flow = 0;
    do
    {
        memset(past,false,sizeof(past));
        flow = augment(source, MAXN2);
        mflow += flow;
    }while (flow > 0);
    return mflow;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N,M;
    cin >> N >> M;
    int maxc = 0;
    for (int i=1; i<=N; ++i)//purchase to sink
    {
        cin >> capacity[1000+i][sink];
        maxc+=capacity[1000+i][sink];
        adj[1000+i].push_back(sink);
        adj[sink].push_back(1000+i);
    }
    cout << endl;
    maxc/=2;
    for (int i=1; i<=M; ++i)//purchase to children
    {
        int a, b;
        cin >> a >> b;
        games.push_back(make_pair(a,b));
        capacity[i][1000+a] = 2;
        capacity[i][1000+b] = 2;
        adj[i].push_back(1000+a);
        adj[1000+a].push_back(i);
        adj[i].push_back(1000+b);
        adj[1000+b].push_back(i);
    }
    for (int i=M+1; i<=maxc; ++i) //purchase to children
    {
        for (int j=1; j<=N; ++j)
        {
            capacity[i][1000+j]=2;
            adj[i].push_back(1000+j);
            adj[1000+j].push_back(i);
        }
    }
    for (int i=1; i<=maxc; ++i) //source to purchase
    {
        capacity[source][i]=2;
        adj[i].push_back(source);
        adj[source].push_back(i);
    }
    max_flow();
    cout << maxc << endl;
    for (int i=0; i!=M; ++i)
    {
        printf("%d %d %d\n",games[i].first,games[i].second,2 - capacity[i+1][1000+games[i].first]);
    }
    for (int i=M+1; i<=maxc; ++i)
    {
        queue<int> Q;
        for (int j=1001; j<=1000+N; ++j)
        {
            if (capacity[i][j]==0 || capacity[i][j] == 1)
                Q.push(j);
        }
        if (Q.size() == 2)
        {
            printf("%d ",Q.front()-1000);
//            counter[Q.front()-1000]++;
            Q.pop();
            printf("%d %d\n", Q.front()-1000,1);
//            counter[Q.front()-1000]++;
        }
        else
        {
            Q.push(Q.front()-1000);Q.pop();
//            counter[Q.front()]+=2;
            printf("%d ", Q.front());
            if (Q.front() == 1)
                printf("%d %d\n", 2, 2);
            else
                printf("%d %d\n", 1, 2);
        }
    }
}
