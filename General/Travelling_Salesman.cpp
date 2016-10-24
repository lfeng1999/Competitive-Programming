#include <bits/stdc++.h>

using namespace std;

int city[30001];
vector<int> graph[30001];

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N,M,K;
    cin >> N >> M;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    memset(city,-1,sizeof(city));
    cin >> K;
    queue<pair<int,int>> Q;
    for (int i=0; i!=K; ++i)
    {
        int a;
        cin >> a;
        city[a] = 0;
        Q.push(make_pair(a,0));
    }
    int mdist = 0;
    while (!Q.empty())
    {
        int v = Q.front().first, d = Q.front().second; Q.pop();
        for (int i=0; i!=graph[v].size(); ++i)
        if (city[graph[v][i]]==-1)
        {
            Q.push(make_pair(graph[v][i],d+1));
            city[graph[v][i]] = d + 1;
            mdist = max(mdist,d+1);
        }
    }
    cout << mdist;

}
