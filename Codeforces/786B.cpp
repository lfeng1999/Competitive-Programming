#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
vector<pair<ll,ll>> graph[600010];
ll N, nplans, src, sdist[600010];

ll ord1[100010], ord2[100010];
ll par[600010], lef[600010], rig[600010], scnt = 0;

ll fkcounter = 0;
void build_tree(ll v, ll p, ll L, ll R){
	par[v] = p;
	if (p != -1)
		graph[v].push_back(make_pair(p, 0));
	if (L == R){
		ord1[L] = v;
		return;
	}
	ll mid = (L+R)/2;
	lef[v] = ++scnt; rig[v] = ++scnt;
	build_tree(lef[v], v, L, mid);
	build_tree(rig[v], v, mid+1, R);
}
void build_tree2(ll v, ll p, ll L, ll R){
	par[v] = p;
	if (p != -1)
		graph[p].push_back(make_pair(v, 0));
	if (L == R){
		ord2[L] = v;
		return;
	}
	ll mid = (L+R)/2;
	lef[v] = ++scnt; rig[v] = ++scnt;
	build_tree2(lef[v], v, L, mid);
	build_tree2(rig[v], v, mid+1, R);
}
// void merge_tree(ll v1, ll v2, ll L, ll R){
// 	graph[v1].push_back(make_pair(v2, 0));
// 	if (L == R) return;
// 	ll mid = (L+R)/2;
// 	merge_tree(lef[v1], lef[v2], L, mid);
// 	merge_tree(rig[v1], rig[v2], mid+1, R);
// }

void add_edge3(ll v, ll L, ll R, ll UL, ll UR, ll p, ll d){
	if (R < UL || UR < L) return;
	if (UL <= L && R <= UR){
		graph[v].push_back(make_pair(p, d));
		return;
	}
	ll mid = (L+R)/2;
	add_edge3(lef[v], L, mid, UL, UR, p, d);
	add_edge3(rig[v], mid+1, R, UL, UR, p, d);
}
void add_edge2(ll v, ll L, ll R, ll UL, ll UR, ll p, ll d){
	if (R < UL || UR < L) return;
	if (UL <= L && R <= UR){
		graph[p].push_back(make_pair(v, d));
		return;
	}
	ll mid = (L+R)/2;
	add_edge2(lef[v], L, mid, UL, UR, p, d);
	add_edge2(rig[v], mid+1, R, UL, UR, p, d);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> nplans >> src;

	ll rt1 = ++scnt; par[rt1] = -1;
	build_tree(rt1, -1, 1, N);
	ll rt2 = ++scnt; par[rt2] = -1;
	build_tree2(rt2, -1, 1, N);
	for (ll i=1; i<=N; ++i){
		graph[ord1[i]].push_back(make_pair(ord2[i], 0));
		graph[ord2[i]].push_back(make_pair(ord1[i], 0));
	}
	
	for (ll qq=0; qq<nplans; ++qq){
		ll typ;
		cin >> typ;
		if (typ == 1){
			ll v, u, w; cin >> v >> u >> w;
			graph[ord1[v]].push_back(make_pair(ord2[u], w));
		}
		else if (typ == 2){
			ll v, l, r, w; cin >> v >> l >> r >> w;
			add_edge2(rt2, 1, N, l, r, ord1[v], w);
		}
		else if (typ == 3){
			ll v, l, r, w; cin >> v >> l >> r >> w;
			add_edge3(rt1, 1, N, l, r, ord2[v], w);
		}
	}

	fill(sdist, sdist+600010, 1e18); //SET TO LONG LONG

	set<pair<ll,ll>> S; S.insert(make_pair(0, ord1[src]));
	sdist[ord1[src]] = 0;
	while (!S.empty()){
		ll v = S.begin()->second, d = S.begin()->first; S.erase(S.begin());
		for (pair<ll,ll> E : graph[v]){
			ll u = E.first, nd = d + E.second;
			if (sdist[u] > nd){
				S.erase(make_pair(sdist[u], u));
				sdist[u] = nd;
				S.insert(make_pair(sdist[u], u));
			}
		}
	}
	for (ll i=1; i<=N; ++i){
		ll v = ord2[i];
		if (sdist[v] == 1e18){
			sdist[v] = -1;
		}
		cout << sdist[v] << " ";
	}
	return 0;
}