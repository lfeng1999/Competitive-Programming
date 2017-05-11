#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint MOD = 1000000007;

lint bit[751], R, C, K, grid[751][751];
vector<lint> pos[563000];
vector<lint> posbit[563000];

lint query(lint i){
	lint ret = 0;
	for (; i > 0; i -= i&(-i)) ret += bit[i];
	return ret % MOD;
}
void update(lint i, lint val){
	for (; i <= C; i += i&(-i)) bit[i] += val;
}
lint query(vector<lint> &bit, lint i){
	lint ret = 0;
	for (; i > 0; i -= i&(-i)) ret += bit[i];
	return ret % MOD;
}
void update(vector<lint> &bit, lint i, lint val){
	for (; i < bit.size(); i+=i&(-i)) bit[i] += val;
}


int main(){
	// freopen("test.txt","r",stdin);
	freopen("hopscotch.in","r",stdin);
	freopen("hopscotch.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C >> K;
	for (lint i=1; i<=R; ++i){
		for (lint j=1; j<=C; ++j){
			cin >> grid[i][j];
		}
	}
	for (lint i=1; i<=K; ++i) pos[i].push_back(0);

	for (lint j=1; j<=C; ++j){
		set<lint> here;
		for (lint i=1; i<=R; ++i){
			here.insert(grid[i][j]);
		}
		for (lint x : here) pos[x].push_back(j);
	}
	for (lint i=1; i<=K; ++i) for (lint qq=0; qq<pos[i].size(); ++qq) posbit[i].push_back(0);

	update(posbit[grid[1][1]], 1, 1);
// cout << query(posbit[grid[1][1]], 4) << endl;
	update(1, 1);
	for (lint i=2; i<=R; ++i){
		for (lint j=C; j>=2; --j){
			lint tot = query(j-1);
			lint idx = lower_bound(pos[grid[i][j]].begin(), pos[grid[i][j]].end(), j) - pos[grid[i][j]].begin();
			lint rem = query(posbit[grid[i][j]], idx-1);
			lint ans = (tot - rem + MOD*2) % MOD;

			update(posbit[grid[i][j]], idx, ans);
			update(j, ans);
			// cout << grid[i][j] << " " << i << " " << j << " " << tot << " " << rem << endl;
			if (i == R && j == C){
				cout << ans;
				return 0;
			}
		}
	}

	return 0;
}