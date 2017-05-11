#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100010], rgraph[100010], graph2[100010], rgraph2[100010];
int n, m, nscc, vscc[100010], val[100010], dist1[100010], dist2[100010];
bool past[100010];
stack<int> stk;
void dfs1(int v){
	past[v] = true;
	for (int u : graph[v]) 
		if (!past[u])
			dfs1(u);
	stk.push(v);
}
void dfs2(int v){
	past[v] = true;
	vscc[v] = nscc;
	for (int u : rgraph[v])
		if (!past[u]) dfs2(u);
}
void dfs3(int v){
	for (int u : graph2[v])
		dfs3(u);
	stk.push(v);
}
void dfs4(int v){
	for (int u : rgraph2[v]) 
		dfs4(u);
	stk.push(v);
}


int main(){
	freopen("test.txt","r",stdin);
	// freopen("grass.in","r",stdin);
	// freopen("grass.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int qq=0; qq<m; ++qq){
		int v, u; cin >> v >> u;
		graph[v].push_back(u); rgraph[u].push_back(v);
	}
	for (int i=1; i<=n; ++i)
		if (!past[i])
			dfs1(i);
	nscc = 0;
	memset(past, false, sizeof(past));
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		if (past[v]) continue;
		++nscc;
		dfs2(v);
	}
	for (int v=1; v<=n; ++v){
		val[vscc[v]]++;
		for (int u : graph[v]){
			if (vscc[u] != vscc[v]){
				graph2[vscc[v]].push_back(vscc[u]);
				rgraph2[vscc[u]].push_back(vscc[v]);
			}
		}
		graph[v].clear();
		rgraph[v].clear();
	}
	memset(past, false, sizeof(past));
	dfs3(vscc[1]);
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		dist1[v] = val[v];
		for (int u : rgraph2[v]){
			dist1[v] = max(dist1[v], val[v] + dist1[u]);
		}
	}
	memset(past, false, sizeof(past));
	dfs4(vscc[1]);
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		dist2[v] = val[v];
		for (int u : graph2[v]){
			dist2[v] = max(dist2[v], val[v] + dist2[u]);
		}
	}
	int ans = val[vscc[1]];
	for (int v=1; v<=nscc; ++v){
		for (int u : rgraph2[v]){
			if (dist1[v] != 0 && dist2[u] != 0)
				ans = max(ans, dist1[v] + dist2[u] - val[vscc[1]]);
		}
	}
	cout << ans;
	return 0;
}