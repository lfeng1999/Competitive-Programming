#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = (ll)1e9 + 7;
string S, S2;
ll dp[5010][5010];
int last[500];
ll choose[5010][5010];


int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0);
	cin >> S;
	S2 = S[0];
	for (int i=1; i<S.length(); ++i){
		if (S[i] != S[i-1])
			S2 = S2 + S[i];
	}
	fill(choose[0], choose[0] + 5010, 1);
	for (int i=1;i<=5000; ++i){
		fill(choose[i], choose[i] + 5010, 1);
		choose[i][0] = 1;
		for (int j=1; j<=5000; ++j)
			choose[i][j] = (choose[i-1][j-1] + choose[i-1][j]) % MOD;
	}

	dp[0][0] = 1;

	for (int i=1; i<=S2.length(); ++i){
		for (int j=1; j<=S2.length(); +	+j){
			dp[i][j] = (dp[i-1][j] + dp[i-1][j-1] - dp[last[S2[i-1]]][j] + MOD)%MOD;
		}
		last[S2[i]] = i;
	}
	long long ans = 0;
	ll n = S.length();
	for (int i=1; i<=S2.length(); ++i){
		ans = (ans + dp[S2.length()][i] * choose[n-1][n-i]) % MOD;
	}
	cout << ans;


	return 0;
}