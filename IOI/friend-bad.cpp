#include <bits/stdc++.h>

using namespace std;

bool g[21][21];
int n;
int conf[1000];
int cmd[1000][2];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> conf[i];
	}
	for (int i=1; i<=n-1; ++i){
		cin >> cmd[i][0] >> cmd[i][1];
		int p = cmd[i][0];
		if (cmd[i][1] == 1 || cmd[i][1] == 2){
			for (int j=0; j<=20; ++j){
				if (g[p][j]){
					g[i][j] = g[j][i] = true;
				}
			}
		}
		if (cmd[i][1] == 0 || cmd[i][1] == 2){
			g[i][p] = g[p][i] = true;
		}
	}
	int ans = 0;
	for (int i=0; i<(1 << n); ++i){
		bitset<21> b = i;
		bool works = true;
		int tot = 0;
		for (int j=0; j<21; ++j){
			if (b.test(j)) tot += conf[j];
			else continue;
			for (int k=0; k<21; ++k){
				if (b.test(j) && b.test(k) && g[j][k]){
					works = false;
				}
			}
		}
		if (!works) continue;
		ans = max(ans, tot);
	}
	cout << ans;

	return 0;
}