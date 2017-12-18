#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll sub[200010], len[200010], k[200010], N, t[200010], tlen[200010];
vector<ll> graph[200010];

void dfs(ll v, ll p){
	sub[v] = 1;
	for (ll u : graph[v]){
		if (u == p)
			continue;
		dfs(u, v);
		sub[v] += sub[u];
		len[v] += len[u] + sub[u];
	}
}
void dfs2(ll v, ll p){
	if (p != -1){
		tlen[v] = tlen[p] - sub[v] + N - sub[v]; // COOL AF
	}
	else{
		tlen[v] = len[v];
	}
	for (ll u : graph[v]){
		if (u == p){
			t[v] += (tlen[v] - len[v])*sub[v];
		}
		else{
			t[v] += (len[u] + sub[u])*(N - sub[u]);
		}
	}

	for (ll u : graph[v]){
		if (u == p)
			continue;
		dfs2(u, v);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (ll i=1; i<=N; ++i){
		cin >> k[i];
	}
	for (ll i=0; i<N-1; ++i){
		ll v, u;
		cin >> v >> u;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	dfs(1, -1);
	dfs2(1, -1);
	ll ans = 0;
	for (ll i=1; i<=N; ++i){
		ans += k[i]*t[i];
	}
	cout << ans;



	return 0;
}