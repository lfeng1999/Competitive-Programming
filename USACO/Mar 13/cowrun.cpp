#include <bits/stdc++.h>


using namespace std;

typedef long long lint;
const lint inf = 1e18;
lint dp[1010][1010], n;
bool inq[1010][1010];
vector<lint> cows;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cowrun.in","r",stdin);
	freopen("cowrun.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	for (lint i=0; i<1010; ++i) fill(dp[i], dp[i] + 1010, inf);
	cin >> n;
	for (lint i=0; i<n; ++i){
		lint x; cin >> x;
		cows.push_back(x);
	}
	sort(cows.begin(), cows.end());
	lint beg = lower_bound(cows.begin(), cows.end(), 0) - cows.begin();
	queue<pair<lint,lint>> Q;
	if (beg != cows.size()){
		dp[beg][beg] = cows[beg]*n; inq[beg][beg] = true;
		Q.push(make_pair(beg, beg));
	}
	if (beg != 0){
		dp[beg-1][beg-1] = abs(cows[beg-1])*n; inq[beg-1][beg-1] = true;
		Q.push(make_pair(beg-1, beg-1));
	}
	while (!Q.empty()){
		lint l = min(Q.front().first, Q.front().second), r = max(Q.front().first, Q.front().second), v = Q.front().second;
		lint cur = dp[Q.front().first][Q.front().second];
		Q.pop();
		if (r != cows.size() - 1){
			dp[l][r+1] = min(dp[l][r+1], cur + abs(cows[v] - cows[r+1])*(n - (r-l+1)));
			if (!inq[l][r+1]){
				inq[l][r+1] = true;
				Q.push(make_pair(l, r+1));
			}
		}
		if (l != 0){
			dp[r][l-1] = min(dp[r][l-1], cur + abs(cows[v] - cows[l-1])*(n - (r-l+1)));
			if (!inq[r][l-1]){
				inq[r][l-1] = true;
				Q.push(make_pair(r, l-1));
			}
		}
	}
	cout << min(dp[0][n-1], dp[n-1][0]);
	return 0;
}