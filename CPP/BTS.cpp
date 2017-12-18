#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = ll(1e9) + 7;
unordered_map<ll,int> comp;
int decomp[4500010];

struct Book{
	ll b, e, w;
} b[500010];

struct Node{
	ll val = 0, lazy = -1, mval = 0;
} seg[4500010];

void push_lazy(ll v, ll L, ll R){
	if (seg[v].lazy == -1)
		return;
	seg[v].val = ((decomp[R] - decomp[L-1])*seg[v].lazy) % MOD;
	seg[v].mval = seg[v].lazy;
	if (v*2 < 4500000){
		seg[v*2].lazy = seg[v].lazy;
		seg[v*2+1].lazy = seg[v].lazy;
	}
	seg[v].lazy = -1;
}

void update(ll v, ll L, ll R, ll UL, ll UR, ll val){
	push_lazy(v, L, R);
	if (UR < L || R < UL)
		return;
	if (UL <= L && R <= UR){
		seg[v].val = ((decomp[R] - decomp[L-1])*val) % MOD;
		seg[v].mval = val;
		if (v*2 < 4500000){
			seg[v*2].lazy = val;
			seg[v*2+1].lazy = val;
		}
		return;
	}
	ll mid = (L+R)/2;
	update(v*2, L, mid, UL, UR, val);
	update(v*2+1, mid+1, R, UL, UR, val);
	seg[v].val = (seg[v*2].val + seg[v*2+1].val) % MOD;
	seg[v].mval = max(seg[v*2].mval, seg[v*2+1].mval);
}

ll querym(ll v, ll L, ll R, ll QL, ll QR){
	push_lazy(v, L, R);
	if (QR < L || R < QL)
		return -1e9;
	if (QL <= L && R <= QR){
		return seg[v].mval;
	}
	ll mid = (L+R)/2;
	return max(querym(v*2, L, mid, QL, QR), querym(v*2+1, mid+1, R, QL, QR));
}

ll querys(ll v, ll L, ll R, ll QL, ll QR){
	push_lazy(v, L, R);
	if (QR < L || R < QL)
		return 0;
	if (QL <= L && R <= QR){
		return seg[v].val;
	}
	ll mid = (L+R)/2;
	return (querys(v*2, L, mid, QL, QR) + querys(v*2+1, mid+1, R, QL, QR)) % MOD;
}

ll N;


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	set<ll> S;
	for (ll i=1; i<=N; ++i){
		cin >> b[i].b >> b[i].e >> b[i].w;
		b[i].e += b[i].b - 1;
		S.insert(b[i].b);
		S.insert(b[i].b - 1);
		S.insert(b[i].e);
	}
	S.insert(-1);
	ll cnt = -1;
	for (ll x : S){
		comp[x] = ++cnt;
		decomp[cnt] = x;
	}
	ll ans = 0;
	for (ll i=1; i<=N; ++i){
		ll beg = comp[b[i].b], ed = comp[b[i].e], w = b[i].w;
		// cout << beg << " " << ed << endl;
		ll qm = querym(1, 1, cnt, beg, ed);
		ll qs = querys(1, 1, cnt, beg, ed);
		ans += (b[i].e - b[i].b + 1)*qm - qs;
		ans += MOD*MOD;
		ans %= MOD;

		update(1, 1, cnt, beg, ed, qm + w);
	}

	cout << ans;



	return 0;
}