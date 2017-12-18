#include <bits/stdc++.h>

using namespace std;

int n, m;
int path[100010];
int dp[100010][330];
int furthest[100010];

vector<int> go[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(path, path + 100010, 1e9);
	cin >> n >> m;
	for (int qq=0; qq<m; ++qq){
		int v, u; cin >> v >> u;
		--v; --u;
		go[v].push_back(u);
		path[u] = v;
	}
	int bsize = sqrt(n);
	for (int j = bsize; j < n; j += bsize){
		stack<int> stk;	
		for (int i = j; i >= 0; --i){
			furthest[i] = i;
			int maxd = i;
			for (auto &e : go[i]){
				if (e <= j) maxd = max(maxd, e);
			}
			while (!stk.empty() && stk.top() <= maxd){
				maxd = max(maxd, dp[stk.top()][j/bsize]);
				stk.pop();
			}
			dp[i][j/bsize] = maxd;
			stk.push(i);
		}
	}
	int nq; cin >> nq;
	for (int qq=0; qq<nq; ++qq){
		int l, r; cin >> l >> r;
		l--; r--;
		int ans;
		if (r-l <= bsize){
			ans = l;
			for (int i=l+1; i<=r; ++i){
				if (l <= path[i] && path[i] <= ans){
					ans = i;
				}
			}
		}
		else{
			ans = dp[l][r/bsize];
			for (int i = bsize*int(r/bsize); i <= r; ++i){
				// cout << i << " " << path[i] << " " << ans << endl;
				if (l <= path[i] && path[i] <= ans){
					ans = i;
				}
			}
		}

		cout << ans + 1 << '\n';
	}


	return 0;
}