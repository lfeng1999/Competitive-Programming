#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll c[3000][31];

int main(){

	c[1][1] = c[1][0] = 1;
	for (int i=2; i<3000; ++i){
		c[i][0] = 1;
		for (int j=1; j<=min(30, i); ++j){
			c[i][j] = (c[i-1][j-1] + c[i-1][j]);
		}
	}
	ll ans = 0;
	for (int i=2; i<=2494; ++i){
		ans += c[i][2]*(2495 - i);
	}
	//1613327798160
	cout << ans;
	return 0;
}