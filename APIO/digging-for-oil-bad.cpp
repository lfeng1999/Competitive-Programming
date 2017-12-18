#include <bits/stdc++.h>

using namespace std;

#define debug(x) cout << '>' << #x << " : " << x << endl
int nr, nc, len, g[1510][1510], psum[1510][1510], dp[1510][1510][2], bestcol[1510], bestrow[1510], dp2[1510][1510][2];
int bestrow2[1510], bestcol2[1510];

int area(int r1, int c1, int r2, int c2){
	return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc >> len;
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			cin >> g[i][j];
			psum[i][j] = g[i][j] + psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1];
		}
	}
	for (int i=len; i<=nr; ++i){
		for (int j=len; j<=nc; ++j){
			dp[i][j][0] = max(max(dp[i-1][j][0], dp[i][j-1][0]), area(i-len+1, j-len+1, i, j));
			bestrow[i-len+1] = max(bestrow[i-len+1], area(i-len+1, j-len+1, i, j));
			dp[i][j][1] = max(max(dp[i-1][j][1], dp[i][j-1][1]), max(dp[i-len][j][0], dp[i][j-len][0]) + area(i-len+1, j-len+1, i, j));
			bestcol[j-len+1] = max(bestcol[j-len+1], area(i-len+1, j-len+1, i, j));
		}
	}
	for (int i=nr-len+1; i>=1; --i){
		for (int j=nc-len+1; j>=1; --j){
			dp2[i][j][0] = max(max(dp2[i+1][j][0], dp2[i][j+1][0]), area(i, j, i+len-1, j+len-1));
			bestrow2[i+len-1] = max(bestrow2[i+len-1], area(i, j, i+len-1, j+len-1));
			dp2[i][j][1] = max(max(dp2[i+1][j][1], dp2[i][j+1][1]), max(dp2[i+len][j][0], dp2[i][j+len][0]) + area(i, j, i+len-1, j+len-1));
			bestcol2[j+len-1] = max(bestcol2[j+len-1], area(i, j, i+len-1, j+len-1));
		}
	}
	for (int i=max(nr, nc); i>=1; --i){
		bestrow[i] = max(bestrow[i], bestrow[i+1]);
		bestcol[i] = max(bestcol[i], bestcol[i+1]);
	}
	for (int i=1; i<=max(nr, nc); ++i){
		bestrow2[i] = max(bestrow2[i], bestrow2[i-1]);
		bestcol2[i] = max(bestcol2[i], bestcol2[i-1]);
	}
	int ans = 0;
	for (int i=len; i<=nr; ++i){
		for (int j=len; j<=nc; ++j){
			ans = max(ans, dp[i][j][1] + max(bestrow[i+1], bestcol[j+1]));
		}
	}
	for (int i=nr-len+1; i>=1; --i){
		for (int j=nc-len+1; j>=1; --j){
			ans = max(ans, dp2[i][j][1] + max(bestrow2[i-1], bestcol2[j-1]));
		}
	}
	cout << ans;

	return 0;
}