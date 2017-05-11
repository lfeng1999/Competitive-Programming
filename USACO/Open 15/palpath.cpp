#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint MOD = 1000000007;

lint dp[510][510], dp2[510][510];
int n;
char grid[510][510];

int mv[4][4] = {{0, 1, 0, -1}, {1, 0, -1, 0}, {0, 1, -1, 0}, {1, 0, 0, -1}};

int main(){
	// freopen("test.txt","r",stdin);
	freopen("palpath.in","r",stdin);
	freopen("palpath.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=n; ++j){
			cin >> grid[i][j];
		}
		dp[i][i] = 1;
	}
	map<pair<pair<int,int>, pair<int,int>>, int> M;
	for (int len = n-1; len >= 1; --len){
		for (int i=1; i<=n; ++i){
			for (int j=1; j<=n; ++j){
				dp2[i][j] = dp[i][j];
				dp[i][j] = 0;
			}
		}
		for (int r1=1; r1<=n; ++r1){
			int c1 = (len+1-r1);
			if (c1 < 1) continue;
			for (int r2=r1; r2<=n; ++r2){
				int c2 = 2*n+1-r2-len;
				if (c2 > n) continue;
				if (grid[r1][c1] != grid[r2][c2]) continue;
				for (int i=0; i<4; ++i){
					int nr1 = r1 + mv[i][0], nr2 = r2 + mv[i][2], nc1 = c1 + mv[i][1], nc2 = c2 + mv[i][3];
					if (nr1 > nr2 || nc1 > nc2) continue;
					dp[r1][r2] += dp2[nr1][nr2];
					dp[r1][r2] %= MOD;
				}
			}
		}
	}
	cout << dp[1][n];
	return 0;
}