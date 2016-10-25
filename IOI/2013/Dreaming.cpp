#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endl '\n'

ll best_group[100010], cur, max_branch[100010][2], max_br[3];
int N, M, L, group[100010], max_node[100010][2];
vector<pair<int,int>> graph[100010];
pair<int,int> par[100010]; //p, d

void dfs(int v, int p){
    group[v] = cur;
    for (int i=0; i<graph[v].size(); ++i){
        int u = graph[v][i].first, d = graph[v][i].second;
        if (u == p) continue;

        dfs(u, v);
        par[u] = make_pair(v, d);

        ll udist = max_branch[u][0] + d;

        for (int j=0; j<2; ++j){
            if (udist > max_branch[v][j]){
                swap(udist, max_branch[v][j]);
                swap(u, max_node[v][j]);
            }
        }

    }

}

void dfs2(int v, int p){
    if (p == -1){
        for (int i=0; i<graph[v].size(); ++i){
            dfs2(graph[v][i].first, v);
        }
        return;
    }
    ll pdist = max_branch[p][(max_node[p][0] == v)] + par[v].second;
    int tempp = p;
    for (int i=0; i<2; ++i){
        if (pdist > max_branch[v][i]){
            swap(pdist, max_branch[v][i]);
            swap(tempp, max_node[v][i]);
        }
    }
    for (int i=0; i<graph[v].size(); ++i){
        if (graph[v][i].first == p) continue;
        dfs2(graph[v][i].first, v);
    }

}

void init(){
    for (int i=0; i<N; ++i){
        par[i] = make_pair(-1, 0);
        best_group[i] = 1e9;
    }
    memset(group, -1, sizeof(group));
    for (int v=0; v<N; ++v){
        if (group[v] == -1){
            cur++;
            dfs(v, -1);
            dfs2(v, -1);
        }
    }


    for (int v=0; v<N; ++v){
        ll ans = max_branch[v][0];
        best_group[group[v]] = min(best_group[group[v]], ans);
    }
    for (int i=1; i<=cur; ++i){
        ll ans = best_group[i];
        for (int j=0; j<3; ++j){
            if (ans > max_br[j])
                swap(ans, max_br[j]);

        }
    }


}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> L;
    while (M--){
        int v, u, d;
        cin >> v >> u >> d;
        graph[v].push_back(make_pair(u, d));
        graph[u].push_back(make_pair(v, d));
    }
    init();
    ll ans = 0;
    for (int i=0; i<N; ++i){
        ans = max(ans, max_branch[i][0] + max_branch[i][1]);
    }
    if (cur > 1) ans = max(ans, max_br[0] + max_br[1] + L);
    if (cur > 2) ans = max(ans, max_br[1] + max_br[2] + L*2);


    cout << ans;
    return 0;
}
