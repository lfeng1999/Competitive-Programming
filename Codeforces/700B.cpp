#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<ll> graph[200010];
ll n, k, subsz[200010], ans = 0;
bool uni[200010];

void dfs(ll v, ll p){
	if (uni[v])
		subsz[v] = 1;
	for (ll u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
		subsz[v] += subsz[u];
		ans += min(2*k-subsz[u], subsz[u]);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (ll i=0; i<2*k; ++i){
		ll x; cin >> x; uni[x] = true;
	}
	for (ll i=0;i<n-1; ++i){
		ll v, u; cin >> v >> u;
		graph[v].push_back(u); graph[u].push_back(v);
	}
	dfs(1, -1);
	cout << ans;
	return 0;
}