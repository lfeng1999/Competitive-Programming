#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	int t = 0;
	while(cin >> N && N){
		if (N == 1){
			printf("Case %d: %lld\n", ++t, 2);
			continue;
		}
		ll ans = 0;
		int m = sqrt(N) + 1, nf = 0;
		for (int i=2; i<=m; ++i){
			if (N%i == 0){
				ll to_add = 1;
				while (N%i == 0){
					N /= i;
					to_add *= i;
				}
				ans += to_add;
				nf++;
			}
		}
		if (N > 1){
			nf++;
			ans += N;
		}
		if (nf == 1){
			ans++;
		}
		printf("Case %d: %lld\n", ++t, ans);
	}

	return 0;
}