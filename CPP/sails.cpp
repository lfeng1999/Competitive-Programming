#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll ans[100010];

struct Node{
	ll val = 0, lazy = 0;
} seg[300010];

void push_lazy(ll v){
	seg[v].val += seg[v].lazy;
	if (v*2 < 300000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
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

void expandtree(ll v, ll L, ll R){
	push_lazy(v);
	if (L == R){
		ans[L] = seg[v].val;
		return;
	}
	ll mid = (L+R)/2;
	expandtree(v*2, L, mid);
	expandtree(v*2+1, mid+1, R);
}

ll N;
vector<pair<ll,ll>> V;
set<ll> S;
const ll MAXH = 100000;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (ll i=0; i<N; ++i){
		ll a, b; cin >> a >> b;
		V.push_back(make_pair(a, b));
	}
	sort(V.begin(), V.end());
	set<ll> S;
	S.insert(1);
	for (ll i=0; i<N; ++i){
		// expandtree(1, 1, MAXH);
		// for (ll j=1; j<=5; ++j)
		// 	cout << ans[j] << " ";
		// cout << endl;


		ll H = V[i].first, origK = V[i].second, K = V[i].second;
		auto it = S.lower_bound(H - K + 1);
		ll v1, v2;
		ll p;

		if (it != S.end()){
			p = *it;
			update(1, 1, MAXH, p, H, 1);
			if (p != 1){
				v1 = query(1, 1, MAXH, p-1), v2 = query(1, 1, MAXH, p);
				if (v1 == v2)
					S.erase(p);
			}
			K -= H - p + 1;
			S.insert(H+1);
			if (K == 0)
				continue;
		}

		it = --S.lower_bound(H - origK + 1);

		p = *it;
		update(1, 1, MAXH, p, p + K - 1, 1);
		if (p != 1){
			v1 = query(1, 1, MAXH, p-1), v2 = query(1, 1, MAXH, p);
			if (v1 == v2)
				S.erase(p);
		}
		S.insert(p+K);
	}
	expandtree(1, 1, MAXH);
	ll tot = 0;
	for (ll i=1; i<=MAXH; ++i){
		tot += (ans[i])*(ans[i]-1)/2;
		// cout << ans[i] << endl;
	}
	cout << tot;

	return 0;
}