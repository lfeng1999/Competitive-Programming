#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll dp[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	dp[1] = 0;

	for (ll i=2; i<=100000; ++i){
		if (i%2 == 0){
			dp[i] = i*i/4 + 2*dp[i/2];
		}
		else{
			dp[i] = ll(i/2)*ll(i/2 + 1) + dp[i/2] + dp[i/2 + 1];
		}
	}
	// cout << dp[7] << " " << dp[6] << endl;
	// cout << dp[100000];
	ll n; cin >> n;
	if (n == 0){
		cout << "ab";
		return 0;
	}
	char ch = 'a';
	for (int i=60000; i>=2; --i){
		while (n >= dp[i]){
			n -= dp[i];
			for (int j=0; j<i; ++j){
				cout << ch;
			}
			++ch;
		}
	}

	return 0;
}	