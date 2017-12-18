#include <bits/stdc++.h>

using namespace std;


int n, nball, w, dp[510][10510], bt[510][10510];
int psum[10510], pins[10510];
bool used[10510];

void solve(){
	memset(dp, 0, sizeof(dp));
	cin >> n >> nball >> w;
	for (int i=1; i<=n; ++i){
		cin >> psum[i];
		pins[i] = psum[i];
		psum[i] += psum[i-1];
	}
	for (int i=n+1; i<=n+w; ++i){
		psum[i] = psum[i-1];
	}
	int ans = 0;
	for (int i=1; i<=nball; ++i){
		for (int j=1; j<=n+w; ++j){
			for (int k=j; k>=0; --k){
				if (dp[i-1][k] + psum[j] - psum[max(k, j - w)] > dp[i][j])
					bt[i][j] = k;
				dp[i][j] = max(dp[i][j], dp[i-1][k] + psum[j] - psum[max(k, j - w)]);
				// ans = max(ans, dp[i][j]);
			}
		}
	}
	for (int i=1; i<=n+w; ++i){
		if (dp[nball][i] == 74966){
			int x = nball;
			int p = i;
			int tot = 0;
			int tot2 = 0;
			while (x){
				// cout << p << " ";
				// for (int j=max(p-w+1, bt[x][p]+1); j <=p; ++j){
				// 	// tot += pins[j];
				// 	used[j] = true;
				// 	cout << max(p-w+1, bt[x][p]+1) << " TO " << p << endl;
				// }
				// tot2 += psum[p] - psum[max(bt[x][p], p - w)];
				cout << "RANGE: " << p << " to " << bt[x][p]<< "   CURRENT SUM: " << tot << endl;
				p = bt[x][p];
				x--;
			}
			cout << tot << "@EWAE" << '\n';
			cout << tot2 << "FASU" << endl;
		}
		ans = max(ans, dp[nball][i]);
	}
	int total = 0;
	for (int i=1; i<=n; ++i){
		if (used[i]){
			cout << pins[i] << " ";
			total += pins[i];
		}
	}
	cout << total << endl;
	cout << ans << '\n';
}

int main(){
	freopen("test.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	int nq;
	cin >> nq;
	for (int qq=0; qq<nq; ++qq)
		solve();

	return 0;
}