#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint gcd(lint a, lint b){
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a%b);
}

lint lcm(lint a, lint b){
	lint ret = a/gcd(a, b);
	return ret*b;
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	lint ans = 1;
	for (int qq=0; qq<n; ++qq){
		lint x; cin >> x;
		ans = lcm(x, ans);
	}
	cout << ans;
	return 0;
}