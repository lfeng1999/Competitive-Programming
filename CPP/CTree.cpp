#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N, M, K;
ll dp[110][110][110], col[110], cost[110][110];
//current pos, last color, beauty

ll solve(ll v, ll c, ll b){
	ll &ans = dp[v][c][b];
	if (ans != -1)
		return ans;
	if (b > K)
		return ans = 1e18;
	if (v == N){
		if (b == K)
			return 0;
		else
			return 1e18;
	}
	ans = 1e18;

	if (col[v+1] != 0){
		if (col[v+1] == c)
			return ans = solve(v+1, c, b);
		else
			return ans = solve(v+1, col[v+1], b+1);
	}
	if (c != 109)
		ans = min(ans, cost[v+1][c] + solve(v+1, c, b));
	for (ll i=1; i<=M; ++i){
		if (i != c)
			ans = min(ans, cost[v+1][i] + solve(v+1, i, b+1));
	}
	return ans;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (ll i=0; i<110; ++i)
		for (ll j=0; j<110; ++j)
			fill(dp[i][j], dp[i][j] + 110, -1);

	cin >> N >> M >> K;
	for (ll i=1; i<=N; ++i){
		cin >> col[i];
	}
	for (ll i=1; i<=N; ++i){
		for (ll j=1; j<=M; ++j){
			cin >> cost[i][j];
		}
	}
	ll ans = solve(0, 109, 0);
	if (ans < 1e18)
		cout << ans;
	else
		cout << -1;

	return 0;
}