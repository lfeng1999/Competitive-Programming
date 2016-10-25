#include <bits/stdc++.h>

using namespace std;

vector<int> graph[1000001];
int N,M,c,d;
int pos = -1;

bool dfs(int node)
{
    if (node == d)
    {
        pos = 2;
        return true;
    }
    for (int i=0; i!=graph[node].size(); ++i)
    {
        if (dfs(graph[node][i]))
            return true;
    }
    return false;
}
bool dfs2(int node)
{
    if (node == c)
    {
        pos = 1;
        return true;
    }
    for (int i=0; i!=graph[node].size(); ++i)
    {
        if (dfs2(graph[node][i]))
            return true;
    }
    return false;
}

int main()
{
    //freopen("CCC.txt","r", stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> N >> M;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    cin >> c >> d;
    dfs(c);
    dfs2(d);
    if (pos == 1)
        cout << "no";
    else if (pos == 2)
        cout << "yes";
    else
        cout << "unknown";
}
