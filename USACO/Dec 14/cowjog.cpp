#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint n, T;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cowjog.in","r",stdin);
	freopen("cowjog.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> T;
	multiset<lint> S;
	for (lint i=0; i<n; ++i){
		lint p, s;
		cin >> p >> s;
		lint np = p + s*T;
		auto it = S.lower_bound(np);
		if (it != S.begin()){
			S.erase(--it);
		}
		S.insert(np);
	}
	cout << S.size();

	return 0;
}