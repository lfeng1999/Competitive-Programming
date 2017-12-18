#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll shops[1010][6], nshop, N, T, ans = 1e18, mval[6];
set<ll> S[6];

void solve(int t){

	if (t == 0){
		int pcnt = 0;
		for (int i=0; i<nshop; ++i){
			bool flag = true;
			for (int j=1; j<=T; ++j){
				if (shops[i][j] > mval[j]){
					flag = false;
				}
			}
			if (flag)
				pcnt++;
		}
		ll tot =  0;
		for (int i=1; i<=T; ++i)
			tot += mval[i];
		if (pcnt >= N)
			ans = min(ans, tot*N);
		return;
	}
	for (ll x : S[t]){
		mval[t] = x;
		solve(t-1);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nshop >> N >> T;
	for (int i=0; i<nshop; ++i){
		for (int j=1; j<=T; ++j){
			cin >> shops[i][j];
			S[j].insert(shops[i][j]);
		}
	}
	solve(T);
	cout << ans;

	return 0;
}