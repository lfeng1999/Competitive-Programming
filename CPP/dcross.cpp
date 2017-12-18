#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000009;
vector<ll> col[10010], row[10010];
ll R, C, N;
set<pair<ll,ll>> S;

ll graph[1010][1010], graph2[1010][1010];

struct Node{
	ll sum = 0, lazy = 0, lazy2 = 0;
} seg[600010];

void fix(ll &a){
	a = (a + MOD * MOD)%MOD;
}

void push_lazy(ll v, ll L, ll R){
	seg[v].sum += seg[v].lazy*(L+R)*(R-L+1)/2;
	fix(seg[v].sum);
	if (v*2 < 600000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;


	seg[v].sum += seg[v].lazy2*(R-L+1);
	fix(seg[v].sum);
	if (v*2 < 600000){
		seg[v*2].lazy2 += seg[v].lazy2;
		seg[v*2+1].lazy2 += seg[v].lazy2;
	}
	seg[v].lazy2 = 0;
}

ll query(ll v, ll L, ll R, ll p){
	push_lazy(v, L, R);
	if (R <= p){
		return seg[v].sum;
	}
	ll mid = (L+R)/2;
	if (p <= mid)
		return query(v*2, L, mid, p);
	else
		return query(v*2+1, mid+1, R, p);
}

void update(ll v, ll L, ll R, ll p, ll val){
	push_lazy(v, L, R);
	if (R <= p){
		
		seg[v].sum += (L+R)*(R-L+1)*val/2;
		fix(seg[v].sum);
		if (v*2 < 600000){
			seg[v*2].lazy += val;
			seg[v*2+1].lazy += val;
		}
		return;
	}
	ll mid = (L+R)/2;
	update(v*2, L, mid, p, val);
	if (mid+1 <= p)
		update(v*2+1, mid+1, R, p, val);
	push_lazy(v*2, L, mid);
	push_lazy(v*2+1, mid+1, R);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
	fix(seg[v].sum);
}
void updater(ll v, ll L, ll R, ll p, ll val){
	push_lazy(v, L, R);
	if (p <= L){
		seg[v].sum += (R-L+1) * val;
		fix(seg[v].sum);
		if (v*2 < 600000){
			seg[v*2].lazy2 += val;
			seg[v*2+1].lazy2 += val;
		}
		return;
	}
	ll mid = (L+R)/2;
	updater(v*2+1, mid+1, R, p, val);
	if (p <= mid)
		updater(v*2, L, mid, p, val);
	push_lazy(v*2, L, mid);
	push_lazy(v*2+1, mid+1, R);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
	fix(seg[v].sum);
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C;
	cin >> N;
	for (ll i=0; i<N; ++i){
		ll r, c; cin >> r >> c;
		row[r].push_back(c);
		col[c].push_back(r);
		S.insert(make_pair(r, c));
	}
	for (ll i=1; i<=R; ++i){
		row[i].push_back(0);
		row[i].push_back(C+1);
		sort(row[i].begin(), row[i].end());
	}
	for (ll i=1; i<=C; ++i){
		col[i].push_back(0);
		col[i].push_back(R+1);
		sort(col[i].begin(), col[i].end());
	}

	vector<ll> V;
	ll ans = 0;

	for (ll j=1; j<=C; ++j){
		V.clear();
		for (ll i=1; i<=R; ++i){
			if (S.count(make_pair(i, j))){
				V.push_back(0);
				continue;
			}
			ll p = upper_bound(row[i].begin(), row[i].end(), j) - row[i].begin();
			V.push_back(min(row[i][p] - j, j - row[i][p-1]));
		}
		V.push_back(0);
		ll beg = 0, ed = 0;
		for (ll i=0; i<=R; ++i){
			if (V[i] == 0){
				ed = i-1;
				if (ed - beg >= 4){

					for (ll k=beg+3; k<=ed-1; ++k){
						if (V[k-2] != 1){
							update(1, 1, C/2 + 1, V[k-2]-1, k - beg - 3 + 1);
							updater(1, 1, C/2 + 1, V[k-2], (k - beg - 3 + 1)*(V[k-2]-1));
						}
						if (V[k] >= 3){
							ans += query(1, 1, C/2+1, V[k]-2)*(ed-k);
							fix(ans);
						}
					}
					for (ll k=beg+3; k<=ed-1; ++k){
						if (V[k-2] != 1){
							update(1, 1, C/2 + 1, V[k-2]-1, (k - beg - 3 + 1)*(-1));
							updater(1, 1, C/2 + 1, V[k-2], (k - beg - 3 + 1)*(V[k-2]-1)*(-1));
						}
					}
				}
				beg = i+1;
			}
		}
	}

	cout << ans;


	return 0;
}