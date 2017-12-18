#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<pair<ll,ll>, ll> piipi;

ll ml = 1, mr = 1, a[100010], N, Q, gsize, fin_ans[100010];
unordered_map<ll,ll> comp;
ll bit[100010];

void update(ll i, ll val){
	for (; i < 100010; i += i&(-i))
		bit[i] += val;
}
ll query(ll i){
	ll tot = 0;
	for (; i > 0; i -= i&(-i))
		tot += bit[i];
	return tot;
}



bool mycomp(piipi &a, piipi &b){
	if (a.first.first/gsize < b.first.first/gsize)
		return true;
	else if (a.first.first/gsize == b.first.first/gsize)
		return a.first.second < b.first.second;
	return false;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	set<ll> S;
	cin >> N;
	gsize = 200;
	for (ll i=1; i<=N; ++i){
		cin >> a[i];
		S.insert(a[i]);
	}
	ll cnt = 1;
	for (ll x : S){
		comp[x] = cnt++;
	}
	for (ll i=1; i<=N; ++i){
		a[i] = comp[a[i]];
	}
	vector<piipi> queries;
	cin >> Q;
	for (ll i=1; i<=Q; ++i){
		ll L, R; cin >> L >> R;
		queries.push_back(make_pair(make_pair(L, R), i));
	}
	sort(queries.begin(), queries.end(), mycomp);
	ll ans = 0;
	update(a[1], 1);
	for (ll i=0; i<Q; ++i){
		ll L = queries[i].first.first, R = queries[i].first.second;
		while (mr < R){
			ans += (mr - ml + 1) - query(a[++mr]);
			update(a[mr], 1);
		}
		while (L < ml){
			ans += query(a[--ml] - 1);
			update(a[ml], 1);
		}
		while (ml < L){
			update(a[ml], -1);
			ans -= query(a[ml++] - 1);
		}
		while (R < mr){
			update(a[mr], -1);
			ans -= (mr - ml) - query(a[mr--]);
		}
		fin_ans[queries[i].second] = ans;
	}
	for (ll i=1; i<=Q; ++i){
		cout << fin_ans[i] << '\n';
	}
	return 0;
}