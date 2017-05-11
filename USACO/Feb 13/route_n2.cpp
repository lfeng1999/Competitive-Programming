#include <bits/stdc++.h>

using namespace std;

//dp will be on edges
const int MAXN = 40010;
vector<int> graph[80020];
int nl, nr, m, val[80020];
unordered_map<int, int> dp;

int solve(int v, int p){
	int ret = 0, msk = v*MAXN + p;
	if (dp.count(msk)) return dp[msk];
	for (int i = upper_bound(graph[v].begin(), graph[v].end(), p) - graph[v].begin(); i < graph[v].size(); ++i){
		int u = graph[v][i];
		ret = max(ret, val[u] + solve(u, v));
	}
	dp[msk] = ret;
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nl >> nr >> m;
	for (int i=1; i<=nl; ++i){
		cin >> val[i];
	}
	for (int i=1; i<=nr; ++i){
		cin >> val[MAXN + i];
	}
	for (int i=0; i<m; ++i){
		int v, u; cin >> v >> u;
		graph[v].push_back(MAXN+u);
		graph[MAXN+u].push_back(v);
	}
	for (int v=1; v<MAXN*2; ++v){
		sort(graph[v].begin(), graph[v].end());
	}
	int ans = 0;
	for (int v=1; v<MAXN*2; ++v){
		ans = max(ans, val[v]);
	}
	for (int v=1; v<MAXN*2; ++v){
		for (int u : graph[v]){
			ans = max(ans, val[v] + val[u] + solve(u, v));
		}
	}
	cout << ans;
	return 0;
}