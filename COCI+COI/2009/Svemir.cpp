#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
pii p[3][100000];
bool past[100010];
int N;
vector<pair<int,int>> graph[100010];

int prim()
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    int tot = 0, cnt = 0;
    Q.push(make_pair(0,0));
    while (!Q.empty() && cnt!=N)
    {
        int d = Q.top().first, node = Q.top().second; Q.pop();
        if (past[node])
            continue;
        cnt++;
        tot+=d;
        past[node] = true;
        for (int i=0; i!=graph[node].size(); ++i)
        {
            int nd = graph[node][i].first, np = graph[node][i].second;
            if (!past[np])
                Q.push(make_pair(nd, np));
        }
    }
    return tot;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> N;
    for (int i=0; i!=N; ++i)
    {
        for (int j=0; j!=3; ++j)
        {
            int a;
            cin >> a;
            p[j][i] = make_pair(a,i);
        }
    }
    for (int j=0; j!=3; ++j)
    {
        sort(p[j], p[j]+N);
        for (int i=1; i!=N; ++i)
        {
            graph[p[j][i-1].second].push_back(make_pair(p[j][i].first - p[j][i-1].first,p[j][i].second));
            graph[p[j][i].second].push_back(make_pair(p[j][i].first - p[j][i-1].first,p[j][i-1].second));
        }
    }
    printf("%d",prim());
}
