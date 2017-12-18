#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000009;
ll R, C, N, bit1[10010], bit2[10010];

void update(ll *bit, ll p, ll arral){
	for (; p < 10010; p += p&(-p))
		bit[p] += arral;
}
ll query(ll *bit, ll p){
	ll tot = 0;
	for (; p > 0; p -= p&(-p))
		tot += bit[p];
	return tot;
}

vector<ll> col[10010], row[10010];
ll arr[10010];
set<pair<ll,ll>> S;

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C >> N;
	for (ll qq=0; qq<N; ++qq){
		ll r, c; cin >> r >> c;
		col[c].push_back(r);
		row[r].push_back(c);
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

	ll ans = 0;
	for (ll j=1; j<=C; ++j){

		for (ll i=1; i<=R; ++i){
			if (S.count(make_pair(R, C))){
				arr[i] = 0;
				continue;
			}
			ll id = upper_bound(row[i].begin(), row[i].end(), j) - row[i].begin();
			arr[i-1] = min(row[i][id] - j, j - row[i][id-1]);
		}
		arr[R] = 0;
		ll beg = 0, ed = 0;
		for (ll i=0; i<=R; ++i){
			if (arr[i] == 0){
				ed = i - 1;

				if (ed - beg >= 4){

					for (ll k = beg + 3; k <= ed - 1; ++k){
						if (arr[k-2] > 1){
							update(bit1, 1, (k - (beg + 3) + 1));
							update(bit1, arr[k-2], -(k - (beg + 3) + 1));
							update(bit2, arr[k-2], (k - (beg + 3) + 1)*(arr[k-2] - 1));
						}
						if (arr[k] > 2){
							ans += (query(bit1, arr[k] - 2)*(1 + arr[k] - 2)*(arr[k] - 2)/2 + query(bit2, arr[k] - 2))*(ed - k);
							ans %= MOD;
						}
					}
				}

				beg = i+1;
			}
		}
	}
	cout << ans % MOD;


	return 0;
}