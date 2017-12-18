#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> ps[200010];
int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int ans = 0;
	for (int qq=0; qq<n; ++qq){
		int a, b; cin >> a >> b;
		ans += b;
		ps[a].push_back(b);
	}
	priority_queue<int> Q;
	for (int i=0; i<n; ++i){
		for (int x : ps[i]) Q.push(x);
		if (!Q.empty()){
			ans -= Q.top();
			Q.pop();
		}
	}
	cout << ans;
	return 0;
}