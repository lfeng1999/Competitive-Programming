#include <bits/stdc++.h>

using namespace std;

const long long MOD = (long long)1e9 + 7;
int n, k, a[510];
long long dp[210][210][1010];

int solve(int s, int g, int imb){
	if (imb > k) return 0;
	// cout << s << " " << g << " " << imb << endl;
	if (s == n && g == 0)
		return 1;
	if (s == n)
		return 0;
	if (dp[s][g][imb] != -1)
		return dp[s][g][imb];
	long long &ans = dp[s][g][imb] = 0;
	if (s > 0)
		imb += g*(a[s] - a[s-1]);

	ans += solve(s+1, g, imb);

	if (g >= 1)
		ans += solve(s+1, g-1, imb);
	if (n - s - g >= 2){
		ans += solve(s+1, g+1, imb);
	}
	if (g > 0)
		ans += solve(s+1, g, imb);

	return ans;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<210; ++i)
		for (int j=0; j<210; ++j)
			for (int k=0; k<1010; ++k)
				dp[i][j][k] = -1;

	cin >> n >> k;
	for (int i=0; i<n; ++i){
		cin >> a[i];
	}
	sort(a, a + n);
	cout << solve(0, 0, 0);
	return 0;
}