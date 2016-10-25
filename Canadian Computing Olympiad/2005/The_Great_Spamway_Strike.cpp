#include <bits/stdc++.h>

using namespace std;

int graph[110][110], sleep[110];

int main()
{
//    freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<110; ++i)
        for (int j=0; j<110; ++j)
            graph[i][j] = 1e9;
    int N;
    cin >> N;
    for (int i=0; i<=N; ++i){
        int M;
        cin >> sleep[i] >> M;
        for (int j=0; j<M; ++j){
            int z; cin >> z;
            graph[i][z] = graph[z][i] = 10;
        }
    }
    for (int i=0; i<=N; ++i)
        for (int j=0; j<=N; ++j)
            if (graph[i][j] == 10)
                graph[i][j] += sleep[j];
    for (int j=0; j<=N; ++j)
    for (int i=0; i<=N; ++i)
    for (int k=0; k<=N; ++k){
        if (graph[i][j] != 1e9 && graph[j][k] != 1e9){
            graph[i][k] = min(graph[i][k], graph[i][j] + graph[j][k]);
        }
    }
    int best = 0;
    for (int i=1; i<=N; ++i)
        if (graph[0][i]!=1e9)
            best = max(best, graph[0][i] + graph[i][0]);
    cout << best;

    return 0;
}
