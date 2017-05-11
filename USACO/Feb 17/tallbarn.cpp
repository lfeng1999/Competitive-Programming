#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double ldouble;
lint n;
lint k;
ldouble h[100010];
lint ck[100010];

lint solve(ldouble perc){
	ldouble ret = 0;	
	for (int i=0; i<n; ++i){
		ck[i] = (lint)((-1 + sqrt(1 + 4*h[i]/perc))/2);
		ret += ck[i];
	}
	return ret;
}

int main(){
	freopen("test.txt","r",stdin);
	// freopen("tallbarn.in","r",stdin);
	// freopen("tallbarn.out","w",stdout);
	cin >> n >> k;
	k -= n;
	for (int i=0; i<n; ++i){
		cin >> h[i];
	}
	ldouble L = 0, R = 1e18; //to decrease
	for (int qq=0; qq<200; ++qq){
		ldouble mid = (L+R)/2;
		if (solve(mid) > k){
			L = mid;
		}
		else{
			R = mid;
		}
	}
	ldouble ans = 0;
	lint used = 0;
	for (int i=0; i<n; ++i){
		ans += h[i]/(ck[i]+1);
		used += ck[i];
	}
	cout << (lint)round(ans + (k-used)*L);

	return 0;
}