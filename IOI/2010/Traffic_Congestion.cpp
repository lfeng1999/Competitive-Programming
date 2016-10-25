#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000010;
int city[MAX_N], par[MAX_N], subtree_sz[MAX_N], tot = 0, worstcase[MAX_N];
vector<int> graph[MAX_N];

void dfs(int v, int p){
    par[v] = p;
    subtree_sz[v] = city[v];
    for (int u : graph[v]){
        if (u == p) continue;
        dfs(u, v);
        subtree_sz[v] += subtree_sz[u];
        worstcase[v] = max(worstcase[v], subtree_sz[u]);
    }
    worstcase[v] = max(worstcase[v], tot - subtree_sz[v]);
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        cin >> city[i];
        tot += city[i];
    }
    for (int i=0; i<N-1; ++i){
        int v, u; cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    dfs(0, -1);
    int ans = -1, best = 1e9;
    for (int i=0; i<N; ++i){
        if (worstcase[i] < best){
            best = worstcase[i];
            ans = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
