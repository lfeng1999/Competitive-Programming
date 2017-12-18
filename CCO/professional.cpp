#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> ps[200010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int qq=0; qq<n; ++qq){
		int a, b; cin >> a >> b;
		ps[a].push_back(b);
	}
	priority_queue<int, vector<int>, greater<int>> Q;
	int tot = n, ans = 0;
	for (int i=n; i>=1; --i){
		tot -= ps[i].size();
		for (int x : ps[i]){
			Q.push(x); 
		}
		if (Q.empty()) continue;
		while (tot < i){
			ans += Q.top();
			Q.pop();
			tot++;
		}
	}
	cout << ans;
	return 0;
}