#include <bits/stdc++.h>

using namespace std;

int N, dp[52][52], cut[52], L;

int solve(int i, int j){
	int &ans = dp[i][j];
	if (ans != -1) return ans;
	if (j - i == 1) return ans = 0;
	ans = 1e9;

	for (int k=i+1; k<j; ++k)
		ans = min(ans, cut[j] - cut[i] + solve(i, k) + solve(k, j));

	return ans;
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	
	cin >> L;
	while (L != 0){
		for (int i=0; i<52; ++i)
			fill(dp[i], dp[i] + 52, -1);
		int N;
		cin >> N;

		cut[0] = 0, cut[N+1] = L;
		for (int i=1; i<=N; ++i)
			cin >> cut[i];
		sort(cut+1, cut+1+N);
		printf("The minimum cutting is %d.\n", solve(0, N+1));

		cin >> L;
	}

	return 0;
}