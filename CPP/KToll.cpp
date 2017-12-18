#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Node{
	ll val, lazy;
} seg[400010];

void push_lazy(ll v){
	seg[v].val += seg[v].lazy;
	if (v*2 < 400000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
	return;
}

void update(ll v, ll L, ll R, ll UL, ll UR, ll val){
	push_lazy(v);
	if (R < UL || UR < L)
		return;
	if (UL <= L && R <= UR){
		seg[v].lazy += val;
		push_lazy(v);
		return;
	}
	ll mid = (L+R)/2;
	update(v*2, L, mid, UL, UR, val);
	update(v*2+1, mid+1, R, UL, UR, val);
}
ll query(ll v, ll L, ll R, ll p){
	push_lazy(v);
	if (L == R)
		return seg[v].val;
	ll mid = (L+R)/2;
	if (p <= mid)
		return query(v*2, L, mid, p);
	else
		return query(v*2+1, mid+1, R, p);
}

ll to[100010], from[100010], n_cnt = 0, par[18][100010], N, depth[100010];
vector<ll> graph[100010];

void dfs(ll v, ll p){
	if (p == -1)
		depth[v] = 0;
	else
		depth[v] = depth[p] + 1;
	to[v] = ++n_cnt;
	par[0][v] = p;
	for (ll u : graph[v]){
		if (u == p) continue;
		dfs(u, v);
	}
	from[v] = n_cnt;
}
ll lca(ll v, ll u){
	if (depth[v] < depth[u])
		swap(v, u);
	ll diff = depth[v] - depth[u];
	for (ll i=17; i >= 0; --i){
		if ((1 << i) <= diff){
			diff -= (1 << i);
			v = par[i][v];
		}
	}
	if (v == u)
		return v;
	for (ll i=17; i >= 0; --i){
		if (par[i][v] != par[i][u]){
			v = par[i][v];
			u = par[i][u];
		}
	}
	return par[0][v];
}
ll toll[100010];
int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (ll i=0; i<18; ++i){
		fill(par[i], par[i] + 100010, -1);
	}
	cin >> N;
	for (ll i=0; i<N-1; ++i){
		ll A, B; cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}
	dfs(1, -1);
	for (ll i=0; i<18; ++i){
		for (ll j=1; j<=N; ++j){
			if (par[i][j] != -1)
				par[i+1][j] = par[i][par[i][j]];
		}
	}
	ll Q;
	cin >> Q;
	for (ll qq=0; qq<Q; ++qq){
		char ch; ll a, b;
		cin >> ch >> a >> b;
		if (ch == 'Q'){
			ll ans = query(1, 1, N, to[a]) + query(1, 1, N, to[b]);
			ll c = lca(a, b);
			ans -= 2*query(1, 1, N, to[c]);
			ans += toll[c];
			ans -= toll[a] + toll[b];
			cout << ans << '\n';
		}
		else if (ch == 'T'){
			update(1, 1, N, to[a], from[a], b - toll[a]);
			toll[a] = b;
		} 
	}
	return 0;
}