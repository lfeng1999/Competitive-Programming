#include <bits/stdc++.h>

using namespace std;

int dp[1010][1010], cost[1010];

int main(){
	for (int i=0; i<1010; ++i){
		for (int j=0; j<1010; ++j){
			dp[i][j] = 1e9;
		}
	}
	//freopen("mytest.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int N;
	cin >> N;
	for (int i=1; i<=N; ++i)
		cin >> cost[i];
	dp[2][1] = cost[2];
	for (int i=1; i<=N; ++i){ //jump size
		for (int j=N; j>=1; --j){ //position
			if (i+j+1 <= N){
				dp[j+i+1][i+1] = min(dp[j+i+1][i+1], dp[j][i] + cost[j+i+1]);
			}
			if (j - i >= 1){
				dp[j-i][i] = min(dp[j-i][i], dp[j][i] + cost[j-i]);
			}
		}
	}
	int ans = 1e9;
	for (int i=1; i<=N; ++i){
		ans = min(ans, dp[N][i]);
	}
	cout << ans;
	return 0;
}