#include <bits/stdc++.h>

using namespace std;

int rdist[2010], psumc[2010][210], psumr[2010][210], g[2010][210];
int dp[2010][2][2010][2];
int nr, nc;


void setup(){
	for (int i=0; i<=nr; ++i){
		for (int j=0; j<=nr; ++j){
			for (int k=0; k<2; ++k){
				for (int l=0; l<2; ++l){
					dp[i][k][j][l] = 1e9;
				}
			}
		}
	}
	int botrow = 1e9;
	for (int i=nr; i>=1; --i){
		botrow += g[i][1] + g[i][nc];
		botrow = min(botrow, rdist[i]);
		dp[i][0][i][1] = dp[i][1][i][0] = botrow;
		dp[i][0][i][0] = g[i][1];
		dp[i][1][i][1] = g[i][nc];
	}
	int toprow = 1e9;
	for (int j=1; j<=nr; ++j){
		toprow += g[j][1] + g[j][nc];
		toprow = min(toprow, rdist[j]);
		dp[j][0][j][1] = dp[j][1][j][0] = min(dp[j][0][j][1], toprow);
		// cout << j << " " << dp[j][0][j][1] << endl;
	}
	for (int j=1; j<=nr; ++j){
		for (int i=j+1; i<=nr; ++i){
			dp[i][0][j][1] = dp[j][1][i][0] = min(g[i][1] + dp[i-1][0][j][1], dp[i][0][i][1] + dp[i-1][1][j][1]);
			dp[i][0][j][0] = dp[j][0][i][0] = min(g[i][1] + dp[i-1][0][j][0], dp[i][0][i][1] + dp[i-1][1][j][0]);
			dp[i][1][j][0] = dp[j][0][i][1] = min(g[i][nc] + dp[i-1][1][j][0], dp[i][1][i][0] + dp[i-1][0][j][0]);
			dp[i][1][j][1] = dp[j][1][i][1] = min(g[i][nc] + dp[i-1][1][j][1], dp[i][1][i][0] + dp[i-1][0][j][1]);
		}
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc;
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			cin >> g[i][j];
			psumc[i][j] = g[i][j] + psumc[i-1][j];
			psumr[i][j] = g[i][j] + psumr[i][j-1];
		}
		rdist[i] = psumr[i][nc];
	}
	setup();
	int nq; cin >> nq;

	long long ans = g[1][1]; //default
	int r1 = 1, c1 = 1;
	for (int qq=0; qq<nq; ++qq){
		int r2, c2; cin >> r2 >> c2;
		ans -= g[r1][c1];
		int dist = 1e9;

		if (r1 == r2){
			dist = min(dist, psumr[r1][max(c2,c1)] - psumr[r1][min(c2,c1) - 1]);
		}
		dist = min(dist, psumr[r1][c1] + psumr[r2][c2] + dp[r1][0][r2][0] - g[r1][1] - g[r2][1]);
		dist = min(dist, (rdist[r1] - psumr[r1][c1-1]) + psumr[r2][c2] + dp[r1][1][r2][0] - g[r1][nc] - g[r2][1]);
		dist = min(dist, (rdist[r1] - psumr[r1][c1-1]) + (rdist[r2] - psumr[r2][c2-1]) + dp[r1][1][r2][1] - g[r1][nc] - g[r2][nc]);
		dist = min(dist, psumr[r1][c1] + (rdist[r2] - psumr[r2][c2-1]) + dp[r1][0][r2][1] - g[r1][1] - g[r2][nc]);
		ans += dist;
		r1 = r2; c1 = c2;
	}
	cout << ans;
	return 0;
}