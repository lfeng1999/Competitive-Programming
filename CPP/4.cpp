#include <bits/stdc++.h>

using namespace std;

int n, t[100010], dp[100010], cur_cost[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; ++i){
		cin >> t[i];
	}
	t[0] = t[1];
	int p1 = 1, p2 = 1, s1 = 0, s2 = 0;

	for (int i=1; i<=n; ++i){
		dp[i] = dp[i-1] + 20;
		cur_cost[i] = 20;
		while (t[i] - t[p1] > 89){
			s1 -= cur_cost[p1];
			p1++;
		}
		while (t[i] - t[p2] > 1439){
			s2 -= cur_cost[p2];
			p2++;
		}
		if (dp[i] > dp[p1-1] + 50){
			cur_cost[i] = max(0, 50 - s1);
			dp[i] = dp[p1-1] + 50;
		}
		if (dp[i] > dp[p2-1] + 120){
			cur_cost[i] = max(0, 120 - s2);
			dp[i] = dp[p2-1] + 120;
		}

		s1 += cur_cost[i];
		s2 += cur_cost[i];
		cout << cur_cost[i] << '\n';
	}

	
	return 0;
}