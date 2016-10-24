#include <bits/stdc++.h>

using namespace std;

int M,N,sink, maxn;
bool seen[2000];
vector<int> graph2[2000];
int graph[2000][2000];


int augment(int cur,int curflow)
{
    if (cur == sink)
        return curflow;
    seen[cur] = true;
    for (int k = 0; k!=graph2[cur].size(); ++k)
    {
        int i = graph2[cur][k];
        if (!seen[i] && graph[cur][i])
        {
            int amt = min(curflow,graph[cur][i]);
            int flow = augment(i,amt);
            if (flow > 0)
            {
                graph[cur][i]-=flow;
                graph[i][cur]+=flow;
                return flow;
            }
        }
    }
    return 0;
}


int max_flow()
{
    int maxflow = 0, flow = 0;
    do
    {
        memset(seen,false,sizeof(seen));
        flow = augment(0, 10001);
        maxflow += flow;
    } while (flow > 0);
    return maxflow;
}


int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(graph,0,sizeof(graph));
    cin >> M >> N;
    maxn = M*2+1;
    for (int i=0; i!=M; ++i)
    {
        int a;
        cin >> a;
        if (a==0)
            sink = i*2;
        graph[i*2][i*2+1]=a;
        graph2[i*2].push_back(i*2+1);
        graph2[i*2+1].push_back(i*2);
    }
    for (int i=0; i!=N; ++i)
    {
        int a,b;
        cin >> a >> b;
        --a, --b;
        graph[a*2+1][b*2]=10000;
        graph2[a*2+1].push_back(b*2);
        graph2[b*2].push_back(a*2+1);
    }
    cout << max_flow();
}
