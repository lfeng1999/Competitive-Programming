#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint MOD = 1000000007;
struct Edge{
	lint v, u;
} es[200010];
lint n, m, dp[100010][2];
bool iscycle = 0;
bool past[200010];
vector<lint> graph[100010];
vector<lint> cur;

void dfs(lint v, lint eid){
	past[v] = true;
	cur.push_back(v);
	for (lint ei : graph[v]){
		if ((ei ^ 1) == eid) continue;
		lint u = es[ei].u;
		if (past[u]){
			iscycle = true; continue;
		}
		dfs(u, ei);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("alliance.in","r",stdin);
	freopen("alliance.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (lint i=0; i<m; ++i){
		lint v, u; cin >> v >> u;
		es[i*2].v = v, es[i*2].u = u;
		graph[v].push_back(i*2);
		es[i*2+1].v = u, es[i*2+1].u = v;
		graph[u].push_back(i*2+1);
	}
	lint ans = 1;
	for (lint i=1; i<=n; ++i){
		if (!past[i]){
			// cout << i << endl;
			iscycle = false;
			cur.clear();
			dfs(i, -1);
			if (iscycle){ 
			//another way to check if there's a cycle is counting the # of edges. If the # of edges is >= the # of nodes then there's a cycle
				ans *= 2;
				ans %= MOD;
				continue;
			}
			//ok there's no cycle
			ans *= cur.size();
			ans %= MOD;
		}
	}
	cout << ans;
	return 0;
}