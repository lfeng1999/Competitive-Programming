#include <bits/stdc++.h>

using namespace std;

int toDelete = 0, arr[1500010], N;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N; ++i){
		int x; cin >> x;
		arr[x]++;
	}
	int ans = 0;
	for (int i=0; i<=1500000; ++i){
		int val = arr[i];
		int id = i;
		arr[i] = 0;
		while (val > 0){
			arr[id] += val%2;
			id++;
			val/=2;
		}
		if (arr[i]) ans++;
	}
	cout << ans;

	return 0;
}