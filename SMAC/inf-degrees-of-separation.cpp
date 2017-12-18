#include <bits/stdc++.h>

using namespace std;

int n, nq;
vector<pair<int,int>> g[100010];

struct DisjointSet{
	int root[100010];
	void setup(){
		for (int i=0; i<n; ++i) root[i] = i;
	}
	int find(int v){
		if (v == root[v]) return v;
		return root[v] = find(root[v]);
	}
	void merge(int v, int u){
		v = find(v); u = find(u);
		if (v == u) return;
		root[v] = u;
	}
} dsu;

bool in_cycle[100010];
int low_link[100010], disc[100010], dtime = 0;
stack<int> stk;
void dfs(int v, int lastedge){
	low_link[v] = disc[v] = ++dtime;
	stk.push(v);
	for (pair<int,int> it : g[v]){
		int u = it.first;
		if (it.second == (lastedge^1)) continue;
		if (disc[u] != 0){
			low_link[v] = min(low_link[v], disc[u]);
		}
		else{
			dfs(u, it.second);
			low_link[v] = min(low_link[v], low_link[u]);
		}
	}
	if (disc[v] == low_link[v]){
		if (stk.top() == v) stk.pop();
		else{
			while (true){
				int u = stk.top();
				in_cycle[u] = true;
				stk.pop();
				if (u == v) break;
			}
		}
	}
}
int grp[100010], curgrp = 0;
void dfs2(int v, int p){
	grp[v] = curgrp;
	for (pair<int,int> it : g[v]){
		int u = it.first;
		if (in_cycle[u] || p == u) continue;
		dfs2(u, v);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nq;
	dsu.setup();
	for (int v=0; v<n; ++v){
		int u; cin >> u;
		g[v].push_back({u, v*2}); g[u].push_back({v, v*2+1});
		dsu.merge(v, u);
	}
	for (int v=0; v<n; ++v){
		if (disc[v] == 0){
			dfs(v, -1);
		}
		if (in_cycle[v]){
			++curgrp;
			dfs2(v, -1);
		}
	}
	for (int qq=0; qq<nq; ++qq){
		int v, u; cin >> v >> u;
		if (dsu.find(v) != dsu.find(u)){
			cout << 0 << '\n';
		}
		else if (grp[v] == grp[u]){
			cout << 1 << '\n';
		}
		else{
			cout << 2 << '\n';
		}
	}

	return 0;
}