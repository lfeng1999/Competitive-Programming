#include <bits/stdc++.h>

using namespace std;

vector<int> graph[20010];
bool past[20010];
int tree_sz[20010], min_max_subtree = 1e9, N, best_node;

int dfs(int v){
    int max_subtree = 0;
    past[v] = true;
    for (int u : graph[v]){
        if (past[u]) continue;
        int child_sz = dfs(u);
        max_subtree = max(max_subtree, child_sz);
        tree_sz[v] += child_sz;
    }
    max_subtree = max(max_subtree, N - tree_sz[v]);
    if (max_subtree < min_max_subtree){
        min_max_subtree = max_subtree;
        best_node = v;
    }
    return tree_sz[v];
}


int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    fill_n(tree_sz,20010,1);
    cin >> N;
    for (int i=0; i<N-1; ++i){
        int v,u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    dfs(1);
    printf("%d %d",best_node,min_max_subtree);
    return 0;
}
