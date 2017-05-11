#include <bits/stdc++.h>

using namespace std;

char s1[10010], s2[10010];
int dp[2][10010];

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	int N, M;
	cin >> M >> N;
	for (int i=1; i<=M; ++i){
		cin >> s2[i];
	}
	for (int i=1; i<=N; ++i){
		cin >> s1[i];
	}
	for (int i=0; i<=M; ++i){
		dp[0][i] = i;
	}

	int ans = 0, idx = 1;
	for (int i=1; i<=N-1; ++i){
		for (int j=0; j<=M; ++j){
			if (j == 0){
				dp[idx][j] = i;
				continue;
			}
			if (s1[i] == s2[j]){
				dp[idx][j] = dp[idx^1][j-1];
			}
			else{
				dp[idx][j] = 1 + min(dp[idx][j-1], min(dp[idx^1][j], dp[idx^1][j-1]));
			}
		}
		ans += dp[idx][M];
		idx^=1;
	}
	cout << ans;

	return 0;
}