#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const int MOD = 2012;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("bbreeds.in","r",stdin);
	freopen("bbreeds.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	string S; cin >> S;
	vector<int> dp(S.length()/2 + 2, 0);
	dp[0] = 1;
	int tot = 0;
	for (int i=0; i<S.length(); ++i){
		vector<int> nxt(S.length()/2 + 2, 0);
		if (S[i] == '('){
			for (int i=0; i<=tot; ++i){
				nxt[i] += dp[i];
				nxt[i] %= MOD;
				nxt[i+1] += dp[i];
				nxt[i+1] %= MOD;
			}
			tot++;
		}
		else{
			tot--;
			for (int i=0; i <= tot; ++i){
				nxt[i] += dp[i];
				nxt[i] += dp[i+1];
				nxt[i] %= MOD;
			}
		}
		dp = nxt;
	}
	cout << dp[0];
	return 0;
}