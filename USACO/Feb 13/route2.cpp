#include <bits/stdc++.h>

using namespace std;

//dp will be on edges
typedef long long lint;
const lint MAXN = 40010;
lint nl, nr, m, val[80020];
lint dp[80020];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nl >> nr >> m;
	for (lint i=1; i<=nl; ++i){
		cin >> val[i];
		dp[i] = val[i];
	}
	for (lint i=1; i<=nr; ++i){
		cin >> val[MAXN + i];
		dp[MAXN + i] = val[MAXN + i];
	}
	vector<pair<lint,lint>> edges;
	for (lint i=0; i<m; ++i){
		lint v, u; cin >> v >> u;
		edges.push_back(make_pair(v, MAXN + u)); //v ->MAXN + u usable before v+1 -> MAXN + u
	}
	sort(edges.begin(), edges.end());
	for (auto &it : edges){
		lint v = it.first, u = it.second;
		lint n1 = max(dp[v], dp[u] + val[v]);
		lint n2 = max(dp[u], dp[v] + val[u]);
		dp[v] = n1; dp[u] = n2;
	}
	lint ans = *max_element(dp, dp+80020);
	cout << ans;
	return 0;
}