#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int n, k;
lint b[1010], tmp[1010], psum0[1010], psum1[1010], dp[8][1010];

lint query(int L, int R){ //L is beginning of door, R is the end position
	return psum1[R] - psum1[L] - (psum0[R] - psum0[L])*L;
}

void solve(int kk, int L, int R, int lr, int rr){
	if (R < L) return;
	int mid = (L+R)/2;
	dp[kk][mid] = 1e18;
	int bestp = -1;
	for (int i=lr; i<=min(rr, mid); ++i){
		lint tmp = dp[kk-1][i-1] + query(i, mid);
		if (tmp < dp[kk][mid]){
			dp[kk][mid] = tmp;
			bestp = i;
		}
	}
	solve(kk, L, mid-1, lr, min(bestp, mid-1));
	solve(kk, mid+1, R, bestp, rr);
}

void setup(){
	for (int i=1; i<=n; ++i)
		psum0[i] = psum0[i-1] + b[i];
	for (int i=1; i<=n; ++i)
		psum1[i] = psum1[i-1] + b[i]*i;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cbarn.in","r",stdin);
	freopen("cbarn.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=1; i<=n; ++i){
		cin >> b[i];
		// cout << b[i] << " ";
	}
	lint ans = 1e18;
	for (int i=1; i<=n; ++i){
		setup();
		// cout << query(2,2) << endl;
		for (int ed=1; ed<=n; ++ed)
			dp[1][ed] = query(1, ed);
		for (int kk=2; kk<=k; ++kk)
			solve(kk, kk, n, kk, n);
		ans = min(ans, dp[k][n]);
		rotate(b+1, b+2, b+n+1);
	}
	cout << ans;
	return 0;
}