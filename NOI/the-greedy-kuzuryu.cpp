#include <bits/stdc++.h>

using namespace std;

int n, m, k, par[310], val[310];
vector<pair<int,int>> g[310];
int dp[310][3][3][310];
bool past[310][3][3];
void dfs(int v, int p){
	for (auto it : g[v]){
		int u = it.first, d = it.second;
		if (u == p) continue;
		par[u] = v; val[u] = d;
		dfs(u, v);
	}
}

void solve(int v, int curid, int pid){
	if (past[v][curid][pid]) return;
	past[v][curid][pid] = true;
	fill(dp[v][curid][pid], dp[v][curid][pid] + k + 1, 1e9);
	if (curid == 1 && pid == 1){
		dp[v][curid][pid][1] = val[v];
	}
	else if (curid == 1){
		dp[v][curid][pid][1] = 0;
	}
	else if (curid == pid){
		dp[v][curid][pid][0] = val[v];
	}
	else{
		dp[v][curid][pid][0] = 0;
	}
	int tmp[310], fin[310];
	for (auto it : g[v]){
		int u = it.first, d = it.second;
		if (u == par[v]) continue;
		fill(tmp, tmp+k+1, 1e9);
		fill(fin, fin+k+1, 1e9);
		solve(u, 0, curid);
		solve(u, 1, curid);
		for (int i=0; i<=k; ++i){
			tmp[i] = min(dp[u][0][curid][i], dp[u][1][curid][i]);
		}
		if (m > 2){
			solve(u, 2, curid);
			for (int i=0; i<=k; ++i){
				tmp[i] = min(tmp[i], dp[u][2][curid][i]);
			}
		}
		for (int tot=0; tot<=k; ++tot){
			for (int i=0; i<=tot; ++i){
				fin[tot] = min(fin[tot], dp[v][curid][pid][i] + tmp[tot-i]);
			}
		}
		for (int i=0; i<=k; ++i){
			dp[v][curid][pid][i] = fin[i];
		}
	}
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	if ((m-1) + k > n){
		cout << -1;
		return 0;
	}
	for (int qq=0; qq<n-1; ++qq){
		int v, u, d;
		cin >> v >> u >> d;
		g[v].push_back({u, d});
		g[u].push_back({v, d});
	}

	dfs(1, -1);
	solve(1, 1, 0);
	cout << dp[1][1][0][k] << '\n';
	return 0;
}