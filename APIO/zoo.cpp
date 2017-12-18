#include <bits/stdc++.h>

using namespace std;
//finish later
int n, nc;
int dp[32][10010], val[32][10010];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nc;
	for (int qq=0; qq<nc; ++qq){
		int idx, nf, nl;
		cin >> idx >> nf >> nl;
		int fear = 0;
		for (int i=0; i<nf; ++i){
			int x; cin >> x;
			int dif;
			if (x >= e) dif = x - e;
			else dif = x + n - e;
			if (dif >= 5) continue;
			fear |= (1 << dif);
		}
		int love = 0;
		for (int i=0; i<nl; ++i){
			int x; cin >> x;
			int dif;
			if (x >= e) dif = x - e;
			else dif = x + n - e;
			if (dif >= 5) continue;
			love |= (1 << dif);
		}
	}
	return 0;
}