#include <bits/stdc++.h>

using namespace std;

int q, nOrb;
double k;
double p;
double choose[1010][1010];

double solve(int day){
	double x = 1;
	for (int i=1; i<=nOrb; ++i){
		if (i%2 == 1){
			x -= choose[nOrb][i] * pow((k-i)/k, day);
		}
		else{
			x += choose[nOrb][i] * pow((k-i)/k, day);
		}
	}
	return x;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	choose[0][0] = 1;
	for (int i=1; i<=1000; ++i){
		choose[i][0] = 1;
		for (int j=1; j<=i; ++j){
			choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
		}
	}

	cin >> k >> q;
	nOrb = (k + 1e-8);

	double pmiss = (double)(k-1)/(k);
	for (int i=0; i<q; ++i){
		int pr; cin >> pr;
		p = (double)(pr - 1e-8)/2000.0;
		if (k == 1){
			cout << 1 << '\n';
			continue;
		}
		int L = 1, R = 1000000000;
		while (L < R){
			int mid = (L+R)/2;
			if (solve(mid) >= p){
				R = mid;
			}
			else{
				L = mid+1;
			}
		}
		cout << L << '\n';
	}

	return 0;
}