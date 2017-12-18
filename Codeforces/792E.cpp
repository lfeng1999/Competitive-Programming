#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int n;
lint a[510];
vector<lint> test;
unordered_set<int> used;

lint solve (lint sz){
	if (sz <= 0) return 1e18;
	lint ret = 0;
	for (int i=0; i<n; ++i){
		lint p = a[i] / (sz + 1);
		lint rem = a[i] - p*(sz + 1);
		if (rem == 0){
			ret += p; continue;
		}
		else if (p + rem >= sz){
			ret += p + 1;
		}
		else{
			return 1e18;
		}
	}
	return ret;
}

set<int> Q;

int main(){
	// freopen("test.txt","r",stdin);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> a[i];
	}
	sort(a, a+n); reverse(a, a+n);
	lint best = 1e18;
	for (int i=1; i<=33000; ++i){
		best = min(best, solve(i));
	}
	for (int i=1; i<=33000; ++i){
		best = min(best, solve(a[0]/i));
		best = min(best, solve(a[0]/i - 1));
	}
	cout << best;

	return 0;
}