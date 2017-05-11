#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> graph[50010];
int par[16][50010], dep[50010], flow[50010];

void dfs(int v, int p){
	dep[v] = dep[p] + 1;
	par[0][v] = p;
	for (int i=1; i<16; ++i)
		par[i][v] = par[i-1][par[i-1][v]];
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
	}
}
int lca(int v, int u){
	if (dep[v] < dep[u]) swap(v, u);
	for (int i=15; i>=0; --i){
		if (dep[v]-dep[u] >= (1 << i))
			v = par[i][v];
	}
	if (v == u) return v;
	for (int i=15; i>=0; --i){
		if (par[i][v] != par[i][u]){
			v = par[i][v];
			u = par[i][u];
		}
	}
	return par[0][v];
}
int ans = 0;
void dfs2(int v, int p){
	for (int u : graph[v]){
		if (u == p) continue;
		dfs2(u, v);
		flow[v] += flow[u];
	}
	ans = max(ans, flow[v]);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("maxflow.in","r",stdin);
	freopen("maxflow.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u); graph[u].push_back(v);
	}
	dfs(1, 0);
	for (int qq=0; qq<k; ++qq){
		int v, u; cin >> v >> u;
		int p = lca(v, u);
		flow[v]++; flow[u]++;
		flow[p]--; flow[par[0][p]]--;
	}
	dfs2(1, 0);
	cout << ans;
	return 0;
}