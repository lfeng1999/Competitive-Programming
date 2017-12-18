#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint gcd(lint a, lint b){
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main(){
	freopen("test.txt","r",stdin);
	lint n; cin >> n;
	vector<lint> Vs;
	for (lint i=0; i<n; ++i){
		lint x; cin >> x;
		Vs.push_back(x);
	}
	lint ans = 0;
	for (lint i=1; i<(1 << n);++i){
		bitset<21> b= i;
		lint mygcd = 0;
		for (lint j=0; j<n; ++j){
			if (b.test(j)){
				mygcd = gcd(mygcd, Vs[j]);
			}
		}
		if (mygcd == 1) continue;
		ans += mygcd*(__builtin_popcount(i));
	}
	cout << ans;

	return 0;
}