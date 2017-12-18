#include <bits/stdc++.h>

using namespace std;

int psum[210], dp[210][210], N, val[210];

int solve(int a, int b){
	int &ret = dp[a][b];
	if (ret != -1)
		return ret;
	if (a == b)
		return ret = val[a];
	ret = 0;

	return ret = max(val[a] + psum[b] - psum[a] - solve(a+1, b), val[b] + psum[b-1] - psum[a-1] - solve(a, b-1));
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<210; ++i)
		fill(dp[i], dp[i] + 210, -1);

	cin >> N;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		val[i] = x%2;
		val[N+i] = x%2;
	}
	for (int i=1; i<=N*2; ++i){
		psum[i] += psum[i-1];
	}
	int ans = 0;
	for (int i=1; i<=N; ++i){
		if (val[i] + psum[N] - solve(i+1, i+N-1) > psum[N]/2){
			ans++;
		}
	}
	cout << ans;

	return 0;
}