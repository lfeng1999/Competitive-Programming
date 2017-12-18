#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int par[18][100010], dep[100010];
lint pdist[18][100010];
vector<pair<int,int>> g[100010];
void dfs(int v, int p, int d){
	par[0][v] = p;
	pdist[0][v] = d;
	dep[v] = dep[p] + 1;
	for (int i=1; i<18; ++i){
		par[i][v] = par[i-1][par[i-1][v]];
		pdist[i][v] = pdist[i-1][v] + pdist[i-1][par[i-1][v]];
	}
	for (auto it : g[v]){
		if (it.first == p) continue;
		dfs(it.first, v, it.second);
	}
}
lint dist(int a, int b){
	if (dep[a] > dep[b]) swap(a, b);
	lint dif = dep[b] - dep[a];
	lint ret = 0;
	for (int i=17; i>=0; --i){
		if (dif >= (1 << i)){
			dif -= (1 << i);
			ret += pdist[i][b];
			b = par[i][b];
		}
	}
	if (a == b) return ret;
	for (int i=17; i>=0; --i){
		if (par[i][a] != par[i][b]){
			ret += pdist[i][a] + pdist[i][b];
			a = par[i][a];
			b = par[i][b];
		}
	}
	ret += pdist[0][a] + pdist[0][b];
	return ret;
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	for (int qq=0; qq<n-1; ++qq){
		int v, u, d; cin >> v >> u >> d;
		g[v].push_back({u, d});
		g[u].push_back({v, d});
	}
	dfs(1, 1, 0);
	int nq, k;
	cin >> nq >> k;
	for (int qq=0; qq<nq; ++qq){
		int a, b; cin >> a >> b;
		cout << dist(a, k) + dist(k, b) << '\n';
	}
	return 0;
}