#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> graph[200010];
bool cent[200010];
int subsz[200010], par[200010], n, k;

void dfs(int v, int p){
	subsz[v] = 1;
	int dp = 0;
	for (auto &e : graph[v]){
		int u = e.first;
		if (u == p || cent[u]) continue;
		dfs(u, v);
		if (subsz[u] > subsz[dp]){
			dp = u;
		}
		subsz[v] += subsz[u];
	}
	par[v] = dp;
}
int arr[1000010], ans = 1e9;
vector<pair<int,int>> tmp;
void dfs2(int v, int p, int d, int nn){
	if (d > k) return;
	ans = min(ans, arr[k-d] + nn);
	tmp.push_back(make_pair(d, nn));
	for (auto &e : graph[v]){
		int u = e.first;
		if (cent[u] || p == u) continue;
		dfs2(u, v, d + e.second, nn+1);
	}
}

void solve(int v){
	dfs(v, 0);
	int N = subsz[v];
	while (subsz[par[v]]*2 > N){
		v = par[v];
	}
	cent[v] = true; //centroid
	
	for (auto &e : graph[v]){
		int u = e.first;
		if (cent[u]) continue;
		dfs2(u, v, e.second, 1);
		for (auto &p : tmp){
			arr[p.first] = min(arr[p.first], p.second);
		}
		tmp.clear();
	}
	int tans = ans;
	for (auto &e : graph[v]){
		int u = e.first;
		if (cent[u]) continue;
		dfs2(u, v, e.second, 1);
		for (auto &p : tmp){
			arr[p.first] = 1e9;
		}
		tmp.clear();
	}
	ans = tans;
	for (auto &e : graph[v]){
		int u = e.first;
		if (cent[u]) continue;
		solve(u);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(arr, arr + 1000010, 1e9);
	arr[0] = 0;
	cin >> n >> k;
	for (int qq=0; qq<n-1; ++qq){
		int v, u, d; cin >> v >> u >> d;
		v++; u++;
		graph[v].push_back(make_pair(u, d));
		graph[u].push_back(make_pair(v, d));
	}
	solve(1);
	if (ans == 1e9) ans = -1;
	cout << ans;
	return 0;
}