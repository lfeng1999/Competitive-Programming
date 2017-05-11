#include <bits/stdc++.h>

using namespace std;

int main(){
	// freopen("test.txt","r", stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int N;
	cin >> N;
	while (N != 0){
		priority_queue<int, vector<int>, greater<int>> Q;
		for (int i=0; i<N; ++i){
			int x; cin >> x;
			Q.push(x);
		}
		int tot = 0, ans = 0;
		while (Q.size() != 1){
			tot = Q.top();
			Q.pop();
			tot += Q.top();
			Q.pop();
			ans += tot;
			Q.push(tot);
		}
		cout << ans << '\n';
		cin >> N;
	}
	return 0;
}