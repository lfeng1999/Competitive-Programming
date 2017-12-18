#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = (ll)1e9 + 1;
int N;

int getsize(ll st){
	int sz = 1;
	while (st%2 == 0 && (st/2)*3 <= N){
		st *= 3;
		st /= 2;
		sz++;
	}
	return sz;
}

void add(ll &a, ll b){
	a += b;
	a %= MOD;
}

ll dp[100048], dp2[100048];
ll solve(int st){
	// ll dp[2048], dp2[2048];
	for (int i=0; i<2048; ++i)
		dp[i] = dp2[i] = 0;
	int origst = st;
	while (st*2 <= N){
		st *= 2;
	}
	int sz = getsize(st);
	for (int i=0; i<(1 << sz); ++i)
		dp[i] = 1;

	int oldsz = sz;
	st /=2;

	while (st >= origst){
		sz = getsize(st);
		for (int i=0; i<(1 << sz); ++i)
			dp2[i] = 0;

		for (int i=0; i<(1 << oldsz); ++i){
			if (dp[i] != 0){
				int ans = (1 << sz) - 1;
				if (i == 0){
					// dp2[ans] += dp[i];
					add(dp2[ans], dp[i]);
					continue;
				}
				for (int j=0; j<min(oldsz, sz); ++j){
					ans -= (((i >> j) | (i >> (j+1)))&1) << j;
				}
				// dp2[ans] += dp[i];
				add(dp2[ans], dp[i]);
			}
		}
		for (int i=0; i < (1 << sz); ++i)
			dp[i] = dp2[i];
		for (int i=(1 << sz) - 1; i >= 0; --i){
			if (dp2[i] == 0) continue;
			vector<int> Q;
			Q.push_back(i);
			for (int j=0; j < sz; ++j){
				if (i & (1 << j)){
					for (int v : Q){
						Q.push_back(v^(1 << j));

						// dp2[v^(1 << j)] += dp[i];
						add(dp2[v^(1<<j)], dp[i]);
					}
				}
			}
		}
		for (int i=0; i < (1 << sz); ++i)
			dp[i] = dp2[i];
		oldsz = sz;
		st/=2;
	}


	return dp[0] + dp[1];
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	ll ans = 1;
	for (int i=1; i<=N; ++i){
		if (i%2 && i%3){
			int st = i;
			for (int i=0; i<2048; ++i)
				dp[i] = dp2[i] = 0;
			int origst = st;
			while (st*2 <= N){
				st *= 2;
			}
			int sz = getsize(st);
			for (int i=0; i < (1 << sz); ++i)
				dp[i] = 1;

			int oldsz = sz;
			st /= 2;

			while (st >= origst){
				sz = getsize(st);
				for (int i=0; i<(1 << sz); ++i)
					dp2[i] = 0;

				for (int i=0; i<(1 << oldsz); ++i){
					if (dp[i] != 0){
						int ans = (1 << sz) - 1;
						if (i == 0){
							// dp2[ans] += dp[i];
							add(dp2[ans], dp[i]);
							continue;
						}
						for (int j=0; j<min(oldsz, sz); ++j){
							ans -= (((i >> j) | (i >> (j+1)))&1) << j;
						}
						// dp2[ans] += dp[i];
						add(dp2[ans], dp[i]);
					}
				}
				for (int i=0; i < (1 << sz); ++i)
					dp[i] = dp2[i];
				for (int i=(1 << sz) - 1; i >= 0; --i){
					if (dp2[i] == 0) continue;
					vector<int> Q;
					Q.push_back(i);
					for (int j=0; j < sz; ++j){
						if (i & (1 << j)){
							int msz = Q.size();
							for (int k=0; k<msz; ++k){
								int v = Q[k];
								Q.push_back(v^(1 << j));

								// dp2[v^(1 << j)] += dp[i];
								add(dp2[v^(1<<j)], dp[i]);
							}
						}
					}
				}
				for (int i=0; i < (1 << sz); ++i)
					dp[i] = dp2[i];
				oldsz = sz;
				st/=2;
			}
			// cout << dp[0] << " " << dp[1] << endl;
			ans *= dp[0] + dp[1];
			ans %= MOD;
		}
	}
	cout << ans;

	return 0;
}