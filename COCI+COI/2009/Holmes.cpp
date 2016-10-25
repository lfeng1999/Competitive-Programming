#include <bits/stdc++.h>

using namespace std;

vector<int> graph[1001], rgraph[1001];
int D, M, N;
bool happened[1001];
set<int> cause[1001];
vector<int> evidence;

void happen(int x)
{
    queue<int> Q;
    Q.push(x);
    while (!Q.empty())
    {
        int node = Q.front(); Q.pop();
        for (int i=0; i!=graph[node].size(); ++i)
        {
            if (!happened[graph[node][i]])
            {
                happened[graph[node][i]] = true;
                Q.push(graph[node][i]);
            }
        }
    }
}

void gencause(int n)
{
    if (rgraph[n].size()==0)
    {
        cause[n].insert(n);
        return;
    }
    for (int i=0; i!=rgraph[n].size(); ++i)
    {
        if (cause[rgraph[n][i]].size()==0)
            gencause(rgraph[n][i]);
        for (auto x : cause[rgraph[n][i]])
            cause[n].insert(x);
    }
}


int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> D >> M >> N;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
        rgraph[b].push_back(a);
    }
    for (int i=0; i!=N; ++i)
    {
        int a;
        cin >> a;
        evidence.push_back(a);
        happened[a] = true;
    }
    for (int i=1; i<=D; ++i)
    if (happened[i])
        happen(i);
    for (int i=1; i<=D; ++i)
        if (cause[i].size()==0)
            gencause(i);
    for (int i=1; i<=D; ++i)
    {
        if (!happened[i])
        {
            for (int j=0; j!=evidence.size(); ++j)
            {
                bool valid = true;
                for (auto x : cause[evidence[j]])
                    if (!cause[i].count(x))
                        valid = false;
                if (!valid)
                    continue;
                happened[i] = true;
                happen(i);
            }
        }
    }

    for (int i=1; i<=D; ++i)
    if (happened[i])
        printf("%d ",i);

}
