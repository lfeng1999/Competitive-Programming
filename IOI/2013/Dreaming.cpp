#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;
const int MAX_N = 100010;
int N,M,L,C,group[MAX_N];
vector<pii> graph[MAX_N];
pii par[MAX_N];
bool visited[MAX_N];
ll mdist[MAX_N][3], out[MAX_N], gd[MAX_N], ans;

void dfs(int node){
    visited[node] = true;
    ll maxtdist = 0;
    group[node] = C;
    for (int i=0; i!=graph[node].size(); ++i){
        if (visited[graph[node][i].first]){
            continue;
        }
        int v = graph[node][i].first, d = graph[node][i].second;
        par[v] = make_pair(node,d);
        dfs(v);
        ll tdist = out[v] + d;
        maxtdist = max(maxtdist,tdist);
        out[node] = max(out[node], tdist);
        for (int i = 0; i!=3; ++i){
            if (tdist > mdist[node][i]){
                swap(tdist,mdist[node][i]);
            }
        }
    }
}

void dfs2(int node){
    int pv = par[node].first, pd = par[node].second;
    if (pv < 0){
        for (int i=0; i!=graph[node].size(); ++i){
            dfs2(graph[node][i].first);
        }
        return;
    }
    ll tdist = mdist[pv][(out[node] + pd == mdist[pv][0])] + pd;
    for (int i=0; i!=3; ++i){
        if (tdist > mdist[node][i]){
            swap(tdist,mdist[node][i]);
        }
    }
    for (int i=0; i!=graph[node].size(); ++i){
        int v = graph[node][i].first, d = graph[node][i].second;
        if (v==pv){
            continue;
        }
        dfs2(v);
    }
}

int main()
{
//    freopen("IOI.txt","r",stdin);
    cin >> N >> M >> L;
    for (int i=0; i!=M; ++i){
        int a,b,c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b,c));
        graph[b].push_back(make_pair(a,c));
    }
    for (int i=0; i!=N; ++i){
        if (visited[i]){
            continue;
        }
        par[i] = make_pair(-1,0);
        dfs(i);
        C++;
        dfs2(i);
    }
    fill_n(gd,MAX_N,numeric_limits<ll>::max());
    for (int i=0; i!=N; ++i){
        gd[group[i]] = min(gd[group[i]],mdist[i][0]);
        ans = max(ans, mdist[i][0]);
    }
    ll mgdist[3];
    memset(mgdist,0,sizeof(mgdist));
    for (int i=0; i!=C; ++i){
        for (int j=0; j!=3; ++j){
            if (gd[i] > mgdist[j]){
                swap(gd[i],mgdist[j]);
            }
        }
    }
    if (C > 1){
        ans = max(ans,mgdist[0] + mgdist[1] + L);
    }
    if (C > 2){
        ans = max(ans, mgdist[1] + mgdist[2] + 2*L);
    }
    cout << ans;
}
