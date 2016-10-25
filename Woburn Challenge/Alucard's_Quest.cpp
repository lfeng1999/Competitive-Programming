#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> graph[200010];

int N, K, val[200010], to_add[200010];
bool items[200010];

bool dfs(int v, int p, int d){
    bool flag = items[v];

    for (int i=0; i<graph[v].size(); ++i){
        int u = graph[v][i].first, m = graph[v][i].second;
        if (u == p) continue;

        if (dfs(u, v, m)){
            flag = true;
        }
    }
    if (flag){
        to_add[v] = d;
    }
    return flag;
}

int main(){
    //freopen("WC.txt","r",stdin);
    cin >> N >> K;
    for (int i=0; i<N - 1; ++i){
        int A, B, M;
        cin >> A >> B >> M;
        graph[A].push_back(make_pair(B, M));
        graph[B].push_back(make_pair(A, M));
    }
    for (int qq=0; qq<K; ++qq){
        int node;
        cin >> node;
        items[node] = true;
    }
    dfs(1, -1, 0);
    int ans = 0;
    for (int i=0; i<=N; ++i){
        ans += to_add[i];
    }

    cout << ans;
    return 0;
}
