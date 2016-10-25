#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200010;
int N, Q, cnum[MAXN], typ[MAXN];
bool past[MAXN];
map<string, int> comp;
string edges[MAXN][3];
vector<pair<int,int>> graph[MAXN*2];

void dfs(int v, int cc, int ntyp){
    cnum[v] = cc;
    typ[v] = ntyp;
    past[v] = true;
    for (int i=0; i < graph[v].size(); ++i){
        int u = graph[v][i].first, d = graph[v][i].second;
        if (!past[u]){
            if (d == 1) dfs(u, cc, ntyp);
            else dfs(u, cc, !ntyp);
        }
        else{
            if (d == 1 && typ[v]!=typ[u]){printf("Waterloo\n"); exit(0);}
            else if (d == 0 && typ[v] == typ[u]){printf("Waterloo\n"); exit(0);}
        }
    }

}

int main()
{
    //freopen("CCO.txt","r",stdin);
    cin >> N >> Q;
    for (int i=0; i<N; ++i) cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    int cnt = 1;
    for (int i=0; i<N; ++i) for (int j=0; j<2; ++j) comp[edges[i][j]] = cnt++;
    for (int i=0; i<N; ++i){
        int v = comp[edges[i][0]], u = comp[edges[i][1]], d = (edges[i][2] == "parallel");
        graph[v].push_back(make_pair(u,d)); graph[u].push_back(make_pair(v,d));
    }
    int cc = 1;
    for (int i=1; i<cnt; ++i) if (cnum[i] == 0) dfs(i, cc++, 1);
    int p =1;
    while (Q--){
        string a, b;
        cin >> a >> b;
        if (!comp.count(a) || !comp.count(b) || cnum[comp[a]]!=cnum[comp[b]]){printf("unknown\n"); continue;}
        int v = comp[a], u = comp[b];
        if (typ[v] == typ[u]) printf("parallel\n");
        else printf("intersect\n");
    }

    return 0;
}
