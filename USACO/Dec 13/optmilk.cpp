#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint n, nd, l0r0[160010], l0r1[160010], l1r0[160010], l1r1[160010], arr;

lint max3(lint a, lint b, lint c){return max(a, max(b,c));}

void update(lint v, lint L, lint R, lint p, lint val){
	if (L == R){
		l0r0[v] = val;
		l0r1[v] = l1r0[v] = l1r1[v] = 0;
		return;
	}
	lint mid = (L+R)/2;
	if (p <= mid) update(v*2, L, mid, p, val);
	else update(v*2+1, mid+1, R, p, val);
	l0r0[v] = max3(l0r0[v*2] + l1r0[v*2+1], l0r1[v*2] + l0r0[v*2+1], l0r1[v*2] + l1r0[v*2+1]);
	l0r1[v] = max3(l0r0[v*2] + l1r1[v*2+1], l0r1[v*2] + l0r1[v*2+1], l0r1[v*2] + l1r1[v*2+1]);
	l1r0[v] = max3(l1r0[v*2] + l1r0[v*2+1], l1r1[v*2] + l0r0[v*2+1], l1r1[v*2] + l1r0[v*2+1]);
	l1r1[v] = max3(l1r0[v*2] + l1r1[v*2+1], l1r1[v*2] + l0r1[v*2+1], l1r1[v*2] + l1r1[v*2+1]);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("optmilk.in","r",stdin);
	freopen("optmilk.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> nd;
	for (lint i=1; i<=n; ++i){
		lint x; cin >> x;
		update(1, 1, n, i, x);
	}
	lint ans = 0;
	for (lint qq=0; qq<nd; ++qq){
		lint p, val; cin >> p >> val;
		update(1, 1, n, p, val);
		ans += max(l0r0[1], max3(l1r1[1], l0r1[1], l1r0[1]));
	}
	cout << ans;
	return 0;
}