#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double ldouble;

int n;
double p;
double dev[100010][2];

bool valid(double tim){
	double xtim = 0;
	for (int i=0; i<n; ++i){
		double req = dev[i][0]*tim;
		if (req <= dev[i][1]) continue;
		xtim += (req - dev[i][1])/p;
	}
	return xtim <= tim;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> p;
	double totpow = 0;
	for (int i=0; i<n; ++i){
		cin >> dev[i][0] >> dev[i][1];
		totpow += dev[i][0];
	}
	if (p >= totpow){
		cout << -1;
		return 0;
	}
	//0 is power, 1 is amt stored
	double L = 0, R = 1e13;
	while ((R-L) > 1e-7){
		double mid = (L+R)/2;
		if (valid(mid)) L = mid;
		else R = mid;
	}
	printf("%.6f", L);
	return 0;
}