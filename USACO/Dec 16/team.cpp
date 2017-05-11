#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint dp[1010][1010][11];
const lint MOD = 1000000009;
int a[1010], b[1010], n, m, k;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("team.in","r",stdin);
	freopen("team.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i=1; i<=n; ++i){
		cin >> a[i];
	}
	for (int i=1; i<=m; ++i){
		cin >> b[i];
	}
	sort(a+1, a+n+1); sort(b+1, b+m+1);
	for (int i=0; i<=n; ++i){
		for (int j=0; j<=m; ++j)
			dp[i][j][0] = 1;
	}
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=m; ++j){
			for (int l=1; l<=k; ++l){
				dp[i][j][l] = dp[i-1][j][l] + dp[i][j-1][l] - dp[i-1][j-1][l];
				if (a[i] > b[j]){
					dp[i][j][l] += dp[i-1][j-1][l-1];
				}
				dp[i][j][l] = (dp[i][j][l] + MOD)%MOD;
			}
		}
	}
	cout << dp[n][m][k];

	return 0;
}