#include <bits/stdc++.h>

using namespace std;

bool graph[1010][1010], pastL[1010][1010], pastR[1010][1010];
int C, N;
vector<int> lcity, rcity;


int rotateleft(int v){return (v-1+C)%C;}
int rotateright(int v){return (v+1)%C;}

bool moveright(int v, int u);

bool moveleft(int v, int u){ //V is left, U is right
    if (pastL[v][u]) return false;
    pastL[v][u] = true;
    int nv = rotateleft(v), nu = rotateright(u);

    if (nv == u) return true;

    if (graph[v][nv]){
        bool flag = moveleft(nv, u);
        if (flag){
            printf("%d\n", nv + 1);
            return true;
        }
    }
    if (graph[v][nu]){
        bool flag = moveright(v, nu);
        if (flag){
            printf("%d\n", nu + 1);
            return true;
        }
    }
    return false;
}

bool moveright(int v, int u){
    if (pastR[v][u]) return false;
    pastR[v][u] = true;
    int nv = rotateleft(v), nu = rotateright(u);
    if (nv == u) return true;

    if (graph[u][nv]){
        bool flag = moveleft(nv, u);
        if (flag){
            printf("%d\n", nv + 1);
            return true;
        }
    }
    if (graph[u][nu]){
        bool flag = moveright(v, nu);
        if (flag){
            printf("%d\n", nu + 1);
            return true;
        }
    }
    return false;
}


int main()
{
//    freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> C >> N;
    for (int i=0; i<N; ++i){
        int v, u;
        cin >> v >> u; v--; u--;
        graph[v][u] = graph[u][v] = true;
    }
    for (int i = 0; i < C; ++i){
        bool flag = moveleft(i, i);
        if (flag){
            printf("%d\n", i+1);
            return 0;
        }
    }
    printf("%d\n", -1);



    return 0;
}
