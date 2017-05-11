#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
int ncows[3000010], n, k;
bool used[3000010];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("empty.in","r",stdin);
	freopen("empty.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (lint i=0; i<k; ++i){
		lint x, y, a, b; cin >> x >> y >> a >> b;
		for (lint j=1; j<=y; ++j){
			ncows[(a*j+b)%n]+=x;
		}
	}
	for (lint i=0; i<n; ++i){
		if (i > 0){
			ncows[i] += ncows[i-1];
			ncows[i-1] = 0;
		}
		if (!used[i] && ncows[i] >= 1){
			ncows[i]--;
			used[i] = true;
		}
	}
	ncows[0] = ncows[n-1];
	ncows[n-1] = 0;
	for (lint i=0; i<n; ++i){
		if (i > 0) ncows[i] = ncows[i-1];
		if (used[i]) continue;
		if (ncows[i] == 0 && !used[i]){
			cout << i; return 0;
		}
		ncows[i]--;
		used[i] = true;
	}
	return 0;
}