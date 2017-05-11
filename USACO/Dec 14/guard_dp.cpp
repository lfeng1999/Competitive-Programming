#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

struct Cow{
	lint w, h, s;
} cow[21];

lint dp[1100010], n, H;
bool past[1100010];
lint wsum[1100010], hsum[1100010];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> H;
	for (lint i=0; i<n; ++i){
		cin >> cow[i].h >> cow[i].w >> cow[i].s;
	}
	for (lint mask=1; mask < (1 << n); ++mask){
		bitset<20> b = mask;
		for (lint i=0; i<n; ++i)
			if (b.test(i)){ 
				wsum[mask] += cow[i].w;
				hsum[mask] += cow[i].h;
			}
	}
	memset(dp, -1, sizeof(dp));
	dp[0] = 1e9;
	queue<lint> Q;
	Q.push(0);
	while (!Q.empty()){
		lint mask = Q.front(); Q.pop();
		bitset<20> b = mask;
		for (lint i=0; i < n; ++i){
			lint nxt = (mask | (1 << i));
			if (nxt == mask) continue;
			dp[nxt] = max(dp[nxt], min(dp[mask], cow[i].s - wsum[mask]));
			if (!past[nxt]){
				past[nxt] = true;
				Q.push(nxt);
			}
		}
	}
	lint ans = -1e9;
	for (lint mask=1; mask < (1<<n); ++mask){
		if (dp[mask] >= 0 && hsum[mask] >= H){
			ans = max(ans, dp[mask]);
		}
	}
	if (ans < 0){
		cout << "Mark is too tall";
	}
	else{
		cout << ans;
	}
	return 0;
}