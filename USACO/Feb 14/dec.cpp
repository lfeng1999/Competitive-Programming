#include <bits/stdc++.h>

using namespace std;

struct Bonus{
	int p, a;
	bool operator < (const Bonus &b) const{return p < b.p;}
};
int n, nb, cows[21][21], dp[1100010];
vector<Bonus> bonus[21];
vector<int> nodes[21];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("dec.in","r",stdin);
	freopen("dec.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nb;
	for (int i=0; i<nb; ++i){
		int k, p, a;
		cin >> k >> p >> a;
		bonus[k].push_back({p, a});
	}
	for (int i=0; i<n; ++i) sort(bonus[i].begin(), bonus[i].end());
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			cin >> cows[i][j];
		}
	}
	for (int i=0; i<(1 << n); ++i){
		nodes[__builtin_popcount(i)].push_back(i);
	}
	dp[0] = 0;
	for (int i=0; i<=n; ++i){//i-th event
		for (int x : nodes[i]){
			for (auto &it : bonus[i]){
				if (dp[x] >= it.p)
					dp[x] += it.a;
			}
			bitset<20> b = x;
			for (int j=0; j<n; ++j){
				if (!b.test(j)){
					int nxt = (x | (1 << j));
					dp[nxt] = max(dp[nxt], dp[x] + cows[j][i]);
				}
			}
		}
	}
	cout << dp[(1 << n) - 1];


	return 0;
}