#include <bits/stdc++.h>

using namespace std;

int main(){
cin.sync_with_stdio(0); cin.tie(0);
int a, b, c, d;
cin >> a >> b >> c >> d;
int maxbeg = max(a, c);
int mined = min(b, d);
	int ans = max(0, mined - maxbeg);
	cout << ans;
return 0;
}