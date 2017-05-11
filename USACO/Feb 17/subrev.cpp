#include <bits/stdc++.h>

using namespace std;

int dp[55][55][55][55], n, a[55];

int solve(int l, int r, int minv, int maxv){
	if (minv > maxv) return -1e9;
	int &ret = dp[l][r][minv][maxv];
	if (ret >= 0) return ret;
	// if (l == r){
	// 	if (minv <= a[l] && a[l] <= maxv) return 1;
	// 	return 0;
	// }
	if (l > r) return ret = 0;
	ret = 0;
	ret = max(solve(l+1, r, minv, maxv), solve(l, r-1, minv, maxv)); //no swapping at all
	if (minv <= a[l]){
		ret = max(ret, 1 + solve(l+1, r, a[l], maxv));
	}
	if (a[r] <= maxv){
		ret = max(ret, 1 + solve(l, r-1, minv, a[r]));
	}
	if (l == r) return ret;
	bool valid1 = false, valid2 = false;
	if (minv <= a[r]){
		ret = max(ret, 1 + solve(l+1, r-1, a[r], maxv));
		valid1 = true;
	}
	if (a[l] <= maxv){
		ret = max(ret, 1 + solve(l+1, r-1, minv, a[l]));
		valid2 = true;
	}
	if (valid1 && valid2){
		ret = max(ret, 2 + solve(l+1, r-1, a[r], a[l]));
	}
	return ret;
}

int main(){
	freopen("subrev.in","r",stdin);
	freopen("subrev.out","w",stdout);
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(dp, -1, sizeof(dp));
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> a[i];
	}
	cout << solve(1, n, 1, 50);
	return 0;
}