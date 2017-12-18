#include <bits/stdc++.h>

using namespace std;

int h[51], n;
set<int> S[510];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int qq=0; qq<n; ++qq){
		int x; cin >> x;
		h[x]++;
	}
	S[0].insert(0);
	int cur = 0;
	for (int i=50; i>=1; --i){
		for (int j=n - 1; j>=cur; --j){
			for (int k=j+1; k<=n; ++k){
				for (int x : S[j]){
					S[k].insert((k-j)*)
				}
			}
		}
		cur += h[i];
	}


	return 0;
}