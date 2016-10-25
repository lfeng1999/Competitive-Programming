#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
int c,r,d, max_weight[10010];
bool past[10010];
vector<pair<int,int>> graph[10010];


int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> c >> r >> d;
    while (r--){
        int v, u, w;
        cin >> v >> u >> w;
        graph[v].push_back(make_pair(u,w));
        graph[u].push_back(make_pair(v,w));
    }
    priority_queue<pii> Q;
    Q.push(make_pair(1e9, 1));
    while (!Q.empty()){
        int v = Q.top().second, w = Q.top().first;Q.pop();
        if (past[v]) continue;
        past[v] = true;
        max_weight[v] = w;
        for (int i=0; i<graph[v].size(); ++i){
            int u = graph[v][i].first, w2 = graph[v][i].second;
            Q.push(make_pair(min(w,w2),u));
        }
    }
    int best = 1e9;
    while (d--){
        int v;
        cin >> v;
        best = min(best, max_weight[v]);
    }
    cout << best;
}
