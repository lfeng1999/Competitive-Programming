#include <bits/stdc++.h>

using namespace std;

int n;
int cmd[100010][2], conf[100010];
int dp[100010][2];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> conf[i];
	}
	for (int i=1; i<=n-1; ++i){
		cin >> cmd[i][0] >> cmd[i][1];
	}
	int ans = 0;
	for (int i=n-1; i>=1; --i){
		int p = cmd[i][0];
		if (cmd[i][1] == 0){
			ans += conf[i];
			conf[p] -= conf[i];
			conf[p] = max(conf[p], 0);
		}
		else if (cmd[i][1] == 1){
			conf[p] += conf[i];
		}
		else if (cmd[i][1] == 2){
			conf[p] = max(conf[p], conf[i]);
		}
	}
	cout << ans + conf[0];
	return 0;
}