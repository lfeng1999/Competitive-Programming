#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const int inf = 1e9;
int k, n, coins[17], dp[1 << 16], psum[100010];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("nochange.in","r",stdin);
	freopen("nochange.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> k >> n;
	for (int i=0; i<k; ++i){
		cin >> coins[i];
	}
	for (int i=1; i<=n; ++i){
		cin >> psum[i];
		psum[i] += psum[i-1];
	}
	lint ans = -1;
	for (int i=0; i<(1 << k); ++i){
		bitset<16> b = i;
		if (dp[i] >= n){
			lint tmp = 0;
			for (int i=0; i<k; ++i){
				if (!b.test(i))
					tmp += coins[i];
			}
			// cout << b.to_string() << endl;
			ans = max(ans, tmp);
			continue;
		}
		for (int j=0; j<k; ++j){
			if (!b.test(j)){
				int nxt = (i | (1 << j));
				dp[nxt] = max(dp[nxt], (int)(upper_bound(psum, psum+n+1, psum[dp[i]] + coins[j]) - psum - 1));
			}
		}
	}
	cout << ans;

	return 0;
}