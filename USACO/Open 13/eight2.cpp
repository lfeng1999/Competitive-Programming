#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ": " << x << endl
typedef long long lint;

short n, g[310][310];
short dp[310][310];
lint marea[310][310];

lint area(lint r1, lint c1, lint r2, lint c2){
	return (r2 - r1 - 1)*(c2 - c1 - 1);
}
bool isempty(lint r, lint i, lint j){
	return (g[r][j] - g[r][i-1]) == 0;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("eight.in","r",stdin);
	freopen("eight.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(dp, 0, sizeof(dp));
	cin >> n;
	for (lint i=1; i<=n; ++i){
		for (lint j=1; j<=n; ++j){
			char ch; cin >> ch;
			g[i][j] = (ch == '*')?1:0;
			g[i][j] += g[i][j-1];
		}
	}
	lint ans = 0;
	for (int j=3; j<=n; ++j){
		for (lint r = 1; r <= n; ++r){
			for (lint i=j-2; i>=1; --i){
				if (!isempty(r, i, i) || !isempty(r, j, j)){
					dp[r][i] = 0;
				}
				else if (dp[r-1][i] == 0){
					dp[r][i] = isempty(r, i, j)?1:0;
				}
				else{
					dp[r][i] = dp[r-1][i] + 1;
				}
				if (isempty(r, i, j)){
					if (dp[r][i] > 2){
						int r1 = r-dp[r][i]+1, c1 = i, r2 = r, c2 = j;
						marea[r][i] = max(marea[r][i], area(r1, c1, r2, c2));
					}
				}
				marea[r][i] = max(marea[r][i], marea[r][i+1]);
			}
		}
		memset(dp, 0, sizeof(dp));

		for (lint r = n; r >= 1; --r){
			for (lint i=j-2; i>=1; --i){
				if (!isempty(r, i, i) || !isempty(r, j, j)){
					dp[r][i] = 0;
				}
				else if (dp[r+1][i] == 0){
					dp[r][i] = isempty(r, i, j)?1:0;
				}
				else{
					dp[r][i] = dp[r+1][i] + 1;
				}
				if (isempty(r, i, j)){
					if (dp[r][i] > 2){
						int r2 = r+dp[r][i]-1, c2 = j, r1 = r, c1 = i;
						ans = max(ans, area(r1, c1, r2, c2)*marea[r][i]);
					}
				}
			}
		}

	}
	if (ans == 0) ans = -1;
	cout << ans;
	return 0;
}