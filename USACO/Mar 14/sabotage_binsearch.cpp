#include <bits/stdc++.h>

using namespace std;

int n;
double cows[100010], tmp[100010], dp[100010], psum[100010];

bool valid(double avg){
	for (int i=1; i<=n; ++i){
		tmp[i] = cows[i] - avg;
		psum[i] = tmp[i] + psum[i-1];
	}
	dp[1] = tmp[1];
	for (int i=2; i<=n; ++i){
		dp[i] = min(dp[i-1], psum[i]);
	}
	double best = 1e9;
	double cur = tmp[n];
	best = tmp[n] + dp[n-2];
	for (int i=n-1; i>=3; --i){
		cur = min(cur, psum[n] - psum[i-1]);
		best = min(best, cur + dp[i-2]);
	}
	return best < 0;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("sabotage.in","r",stdin);
	freopen("sabotage.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> cows[i];
	}
	double L = 0, R = 10010;
	while ((R - L) > 1e-6){
		double mid = (L+R)/2;
		if (valid(mid)) R = mid;
		else L = mid;
	}
	printf("%.3f\n", L); //does rounding
	// or cout << fixed << setprecision(3) << L << '\n';

	return 0;
}