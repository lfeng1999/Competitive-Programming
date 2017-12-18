#include <bits/stdc++.h>

using namespace std;

bool past[1510];
int dist[1510][1510];
vector<int> graph[1510];
int main()
{
    // freopen("test.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N, M, K;
    cin >> N >> M >> K;
    memset(graph,false,sizeof(graph));
    for (int i=0; i<M; ++i){
        int v, u;
        cin >> v >> u;
        // graph[v][u] = graph[u][v] = true;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    for (int i=1; i<=N; ++i){
        queue<int> Q;
        Q.push(i);
        memset(past,false,sizeof(past));
        int amt = 1;
        past[i] = true;
        for (int p = 0; p<K; ++p){
            int psize = Q.size();
            for (int qq = 0; qq < psize; ++qq){
                int v = Q.front(); Q.pop();
                for (int u : graph[v]){
                    if (!past[u]){
                        past[u] = true;
                        Q.push(u);
                        amt++;
                    }
                }
            }
        }
        cout << amt << "\n";
    }

    return 0;
}