#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int n;

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	vector<int> flow;
	int cur = 0;
	for (int i=0; i<n; ++i){
		int a, b; cin >> a >> b;
		cur += a - b;
		flow.push_back(cur);
	}
	sort(flow.begin(), flow.end());
	int best = flow[flow.size()/2];
	lint ans = 0;
	for (int x : flow){
		ans += abs(x - best);
	}
	cout << ans;
	return 0;
}