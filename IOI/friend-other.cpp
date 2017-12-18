#include <bits/stdc++.h>

using namespace std;

int n;
int cmd[100010][2], conf[100010];
int dp[100010][2];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> conf[i];
		dp[i][1] = conf[i];
	}
	for (int i=1; i<=n-1; ++i){
		cin >> cmd[i][0] >> cmd[i][1];
	}
	int tot = 0;
	for (int i=n-1; i>=1; --i){
		int p = cmd[i][0];
		if (cmd[i][1] == 0){
			dp[p][0] += max(dp[i][0], dp[i][1]);
			dp[p][1] += dp[i][0];
		}
		else if (cmd[i][1] == 1){
			dp[p][1] = max(dp[p][1] + max(dp[i][1], dp[i][0]), dp[p][0] + dp[i][1]);
			dp[p][0] += dp[i][0];
		}
		else if (cmd[i][1] == 2){
			dp[p][1] = max(dp[i][1] + dp[p][0], dp[i][0] + dp[p][1]);
			dp[p][0] += dp[i][0];
		}
	}
	cout << max(dp[0][0], dp[0][1]);

	return 0;
}