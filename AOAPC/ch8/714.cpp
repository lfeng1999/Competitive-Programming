#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll m, k, book[510], dp[510][510], min_ans;

bool valid(ll len){
	ll tot = 0;
	int cnt = 1;
	for (int i=1; i<=m; ++i){
		if (cnt > k)
			return false;
		tot += book[i];
		if (tot > len){
			tot = 0;
			--i;
			cnt++;
		}
	}
	return true;
}

bool is_last[510];

void trace(ll len){
	memset(is_last, false, sizeof(is_last));
	ll tot = 0;
	int cnt = 1;
	for (int i=m; i>=1; --i){

		if (i == k-cnt){
			for (; i>=1; --i)
				is_last[i] = true;
			continue;
		}
		tot += book[i];
		if (tot > len){
			is_last[i] = true;
			tot = 0;
			++i;
			cnt++;
		}
	}
	for (int i=1; i<m; ++i){
		printf("%d ", book[i]);
		if (is_last[i]){
			printf("/ ");
		}
	}
	printf("%d\n", book[m]);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	ll t = 0;
	cin >> t;
	for (ll qq=0; qq<t; ++qq){
		cin >> m >> k;
		for (ll i=1; i<=m; ++i){
			cin >> book[i];
		}
		ll L = 1, R = 5e9;
		while (L < R){
			ll mid = (L+R)/2;
			if (valid(mid)){
				R = mid;
			}
			else{
				L = mid+1;
			}
		}
		// cout << L << endl;
		trace(L);
	}

	return 0;
}