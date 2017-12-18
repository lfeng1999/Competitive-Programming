#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> ps;
	int m = -1;
	for (int i=0; i<n; ++i){
		int p; cin >> p;
		if (m == -1) m = p%k;
		else{
			if (p%k != m){
				cout << -1;
				return 0;
			}
		}
		ps.push_back(p);
	}
	sort(ps.begin(), ps.end());
	int res = ps[0];
	lint ans = 0;
	for (int i=0; i<n; ++i){
		ans += abs(ps[i] - res)/k;
	}
	cout << ans;

	return 0;
}