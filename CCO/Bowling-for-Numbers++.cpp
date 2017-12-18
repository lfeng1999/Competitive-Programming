#include <bits/stdc++.h>

using namespace std;


int n, nball, w, dp[510][10510];
int psum[10510];

void solve(){
	memset(dp, 0, sizeof(dp));
	cin >> n >> nball >> w;
	for (int i=1; i<=n; ++i){
		cin >> psum[i];
		psum[i] += psum[i-1];
	}
	for (int i=n+1; i<=n+w; ++i){
		psum[i] = psum[i-1];
	}
	int ans = 0;
	for (int j=1; j<=n+w; ++j){
		dp[1][j] = psum[j] - psum[max(0, j-w)];
	}
	for (int i=2; i<=nball; ++i){
		int lefmax = 0;
		for (int j=1; j<=n+w; ++j){
		        dp[i][j] = -1e9;
			for (int k=j; k>=max(0, j - w + 1); --k){
				dp[i][j] = max(dp[i][j], dp[i-1][k] + psum[j] - psum[max(k, j - w)]);
			}
			if (j >= w){
				lefmax = max(lefmax, dp[i-1][j-w]);
				dp[i][j] = max(dp[i][j], lefmax + psum[j] - psum[j-w]);
			}
		}
	}
	for (int i=1; i<=n+w; ++i){
		ans = max(ans, dp[nball][i]);
	}
	cout << ans << '\n';
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int nq;
	cin >> nq;
	for (int qq=0; qq<nq; ++qq)
		solve();

	return 0;
}