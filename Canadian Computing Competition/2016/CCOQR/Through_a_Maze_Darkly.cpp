#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

unordered_map<int,int> rot[100010];
vector<int> graph[100010];
unordered_map<int,bool> past[100010];
int best[100010], occur[100010], totcycle[100010];


int main()
{
    //freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<100010; ++i) best[i] = -1;

    int N, M, Q;
    cin >> N;

    for (int v=1; v<=N; ++v){
        cin >> M;
        for (int j=0; j<M; ++j){
            int u;
            cin >> u;
            rot[u][v] = j;
            graph[v].push_back(u);
            past[v][u] = false;
        }
    }
    for (int i=1; i<=N; ++i){
        for (int j=0; j<graph[i].size(); ++j){
            int v = i, u = graph[i][j];
            if (past[v][u]) continue;
            vector<pair<int,int>> cycle;

            do{
                cycle.push_back(make_pair(v, u));

                int np = rot[v][u];

                past[v][u] = true;

                np = (np - 1 + graph[u].size())%graph[u].size();
                v = u;
                u = graph[v][np];
                occur[v] = -1;
                totcycle[v] = 0;
            }while (v != i || u != graph[i][j]);



            for (int k=0; k<cycle.size(); ++k){
                int v = cycle[k].first, u = cycle[k].second;
                if (occur[v] != -1){
                    best[v] = max(best[v], k - occur[v]);
                    totcycle[v] += k - occur[v];
                }
                occur[v] = k;
            }
            for (pair<int,int> p : cycle){
                int v = p.first;
                best[v] = max(best[v], (int)cycle.size() - totcycle[v]);
            }
        }
    }
    int QQ; cin >> QQ;
    while (QQ--){
        int x; cin >> x;
        cout << best[x] << endl;
    }
    return 0;
}