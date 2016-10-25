#include <bits/stdc++.h>

using namespace std;

vector<int> graph[21];
int past[21];

bool dfs(int v, int tm){
//    cout << v << " " << tm << endl;
    past[v] = tm;
    for (int u : graph[v]){
        if (past[u]!=0){
            if (tm - past[u] == 5){
                return true;
            }
            continue;
        }
        if (dfs(u, tm+1)) return true;
    }
    return false;
}

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N, M;
    cin >> N >> M;
    while (M--){
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    fill(past, past+21, 0);
    for (int i=1; i<=N; ++i){
        if (dfs(i, 1)){
            cout << "YES";
            return 0;
        }
        fill(past, past+21, 0);
    }
    cout << "NO";
    return 0;
}
