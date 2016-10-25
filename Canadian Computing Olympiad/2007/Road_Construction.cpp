#include <bits/stdc++.h>

using namespace std;

int N, R, occur[1010], low_link[1010], graph[1010][1010];

vector<pair<int,int>> bridges;

int occur_cnt = 1, nbridge = 0;

void dfs(int v, int p){
    occur[v] = low_link[v] = occur_cnt;
    occur_cnt++;

    for (int u = 1; u <=  N; ++u){
        if (u == p || !graph[v][u]) continue;

        if (occur[u] != 0){
            low_link[v] = min(low_link[v], occur[u]);
        }
        else{
            dfs(u, v);

            if (occur[v] > low_link[u]){
                low_link[v] = min(low_link[v], low_link[u]);
            }
            else if (occur[v] < low_link[u]){
                bridges.push_back(make_pair(v, u));
            }
        }

    }

}

bool past[1010];
int cycle[1010], ncycle = 0;
vector<int> tree_graph[1010];

void dfs2(int v){
    past[v] = true;
    cycle[v] = ncycle;
    for (int u = 1; u <= N; ++u){
        if (!graph[v][u] || past[u]) continue;
        dfs2(u);

    }
}

int main()
{
//    freopen("CCO.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> R;

    for (int i=0; i<R; ++i){
        int v, u; cin >> v >> u;

        graph[v][u] = graph[u][v] = true;
    }

    dfs(1, -1);

    for (int i=0; i<bridges.size(); ++i){
        int v = bridges[i].first, u = bridges[i].second;
        graph[v][u] = graph[u][v] = false;
    }

    for (int i=1; i<=N; ++i){
        if (!past[i]){
            dfs2(i);
            ncycle++;
        }
    }

    for (int i=0; i<bridges.size(); ++i){
        tree_graph[cycle[bridges[i].first]].push_back(cycle[bridges[i].second]);
        tree_graph[cycle[bridges[i].second]].push_back(cycle[bridges[i].first]);
    }

    int leaves = 0;
    for (int i=0; i<ncycle; ++i){
        if (tree_graph[i].size() == 1)
            leaves++;
    }

    cout << (leaves + 1)/2;


    return 0;
}
