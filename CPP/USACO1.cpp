#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i=1; i<=N; ++i){
		cin >> a[i];
	}

	double L = 0, R = 1e12;
	while (R - L > 0.01){
		double mid = (L+R)/2;
		if (valid(mid))
			R = mid;
		else
			L = mid;
	}
	cout << int(L + 0.5);
	return 0;
}