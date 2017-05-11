#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1000000009;
ll dp[1010][1010], dp2[1010][1010];
ll N, M, K;
vector<ll> FJ, FP;

ll MODULO(ll &x){
	if (x < 0) x+= MOD;
	x %= MOD;
}

int main(){
	freopen("team.in","r",stdin);
	freopen("team.out","w",stdout);

	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> K;

	for (ll i=0; i<N; ++i){
		ll c; cin >> c; FJ.push_back(c);
	}
	for (ll i=0; i<M; ++i){
		ll c; cin >> c; FP.push_back(c);
	}
	FJ.push_back(-1e9);
	FP.push_back(-1e9);
	sort(FJ.begin(), FJ.end());
	sort(FP.begin(), FP.end());

	// for (ll i=0; i<1010; ++i) dp[0][i] = 1;
	// for (ll i=0; i<1010; ++i) dp[i][0] = 1;

	for (ll i=0; i<1010; ++i){
		for (ll j=0; j<1010; ++j){
			dp2[i][j] = 1;
		}
	}

	bool flag = true;

	for (ll qq=0; qq<K; ++qq){
		if (qq != 0){
			for (ll i=0; i<=N; ++i){
				for (ll j=0; j<=M; ++j){
					dp2[i][j] = dp[i][j];
				}
			}
		}
		for (ll i=1; i<=N; ++i){
			for (ll j=1; j<=M; ++j){
				dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
				MODULO(dp[i][j]);
				if (FJ[i] > FP[j])
					dp[i][j] += dp2[i-1][j-1];
				MODULO(dp[i][j]);
			// cout << setw(10) << dp[i][j];
			}
		// cout << endl;
		}
		// cout << endl;
	}
	cout << dp[N][M];
	return 0;
}