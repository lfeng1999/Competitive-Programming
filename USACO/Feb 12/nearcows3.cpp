#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100010];
int par[100010], dp[100010][21], n, k;

void dfs(int v, int p){
	par[v] = p;
	for (int u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		for (int i=1; i<=k; ++i){
			dp[v][i] += dp[u][i-1];
		}
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n-1; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(u); graph[u].push_back(v);
	}
	for (int i=1; i<=n; ++i){
		cin >> dp[i][0];
	}
	dfs(1, 0);

	for (int i=1; i<=n; ++i){
		int v = i, q = k;
		int ans = 0;
		while (v){
			ans += dp[v][q];
			if (q == 0) break;
			ans += dp[v][q-1];
			q--;
			v = par[v];
		}
		for (int j=0; j<q; ++j){
			ans += dp[1][j];
		}
		cout << ans << '\n';
	}


	return 0;
}