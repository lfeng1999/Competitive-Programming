//Dominator Tree
//Based on Codeforces 757F - Team Rocket Rises Again
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<ll,ll>> graph[200010];
vector<ll> tree[200010], dag[200010], rdag[200010];
ll N, M, src;
ll dist[200010], par[200010];

ll ord[200010], revord[200010], t = 0;

void dfs(ll v){
	ord[v] = ++t; revord[t] = v;
	// cout << v << " " << ord[v] << endl;
	for (ll u : dag[v]){
		if (ord[u] == 0){
			par[u] = v;
			dfs(u);
		}
	}
}

ll root[200010], sdom[200010], dom[200010], locat[200010];
vector<ll> rdom[200010]; //root of sdoms

ll fix(ll v, ll x = 0){ //does path compression + sets up locat
	if (v == root[v]){ //skips root
		return -1;
	}
	ll u = fix(root[v], x+1);
	if (u < 0) return v; //we want the second highest
	if (sdom[locat[v]] > sdom[locat[root[v]]]) //compress path
		locat[v] = locat[root[v]];
	root[v] = u; //haha loser root[v]
	return u;
}

ll dompar[200010];
ll omg[200010];
void solve(){
	for (ll i=1; i<=N; ++i){
		root[i] = sdom[i] = dom[i] = locat[i] = i;
	}
	for (ll v=N; v>=1; --v){
		for (ll u : rdag[v]){
			fix(u);
			sdom[v] = min(sdom[v], sdom[locat[u]]);
			// cout << sdom[v] << endl;
		}
		if (v != 1){
			rdom[sdom[v]].push_back(v);
		}
		for (ll u : rdom[v]){
			fix(u); 
			if (sdom[locat[u]] == sdom[u]){
				dom[u] = sdom[u];
			}
			else
				dom[u] = v;
		}
		root[v] = par[v]; //add it to path
	}
	revord[src] = 1;
	for (ll i=2; i<=N; ++i){
		if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
		// cout << revord[dom[i]] << " " << revord[i] << endl;
		tree[revord[dom[i]]].push_back(revord[i]);
		// dompar[revord[i]] = revord[dom[i]];
	}
}

ll domsz[200010];

ll dfs2(ll v){
	domsz[v]++;
	for (ll u : tree[v]){
		dfs2(u);
		domsz[v] += domsz[u];
	}
}

int main(){
	// freopen("test.txt", "r", stdin);
	cin >> N >> M >> src;
	for (ll i=0; i<M; ++i){
		ll v, u, d; cin >> v >> u >> d;
		graph[v].push_back(make_pair(u, d));
		graph[u].push_back(make_pair(v, d));
	}
	set<pair<ll,ll>> S;
	fill(dist, dist+200010, 1e18); //1e18 for long long
	S.insert(make_pair(0, src));
	dist[src] = 0;
	while (!S.empty()){
		ll v = S.begin()->second, d = S.begin()->first;
		S.erase(S.begin());
		for (pair<ll,ll> E : graph[v]){
			ll u = E.first, nd = E.second + d;
			if (nd < dist[u]){
				S.erase(make_pair(dist[u], u));
				dist[u] = nd;
				S.insert(make_pair(dist[u], u));
			}
		}
	}
	//ok...
	for (ll i=1; i<=N; ++i){
		ll v = i;
		for (pair<ll,ll> E : graph[v]){
			ll u = E.first, d = E.second;
			if (dist[v] + d == dist[u]){
				// cout << v << " " << u << endl;
				dag[v].push_back(u); //dag of shortest path
			}
		}
	}
	//create dominator tree now
	dfs(src);
	for (ll i=1; i<=N; ++i){
		for (ll u : dag[i]){
			rdag[ord[u]].push_back(ord[i]);
		}
	}
	solve();
	dfs2(src);
	ll ans = 0;
	for (ll u : tree[src]){
		ans = max(ans, domsz[u]);
	}
	cout << ans;
	return 0;
}