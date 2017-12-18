#include <bits/stdc++.h>

using namespace std;

int N, a[200010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> a[i];
	}
	sort(a+1, a+N+1);
	int mind = (2e9) + 10, cnt = 0;
	for (int i=2; i<=N; ++i){
		if (a[i] - a[i-1] < mind){
			mind = a[i] - a[i-1];
			cnt = 0;
		}
		if (a[i] - a[i-1] == mind){
			cnt++;
		}
	}
	cout << mind << " " << cnt;
	return 0;
}