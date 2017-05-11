#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef pair<lint,lint> pii;
lint n, k, m, cow[50010][2];
bool past[50010];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("coupons.in","r",stdin);
	freopen("coupons.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k >> m;
	priority_queue<pii, vector<pii>, greater<pii>> coup, nocoup;
	priority_queue<lint, vector<lint>, greater<lint>> retcoup;
	for (lint i=1; i<=n; ++i){
		cin >> cow[i][0] >> cow[i][1];
		coup.push(make_pair(cow[i][1], i));
		nocoup.push(make_pair(cow[i][0], i));
	}
	for (lint qq=0; qq<k; ++qq) retcoup.push(0);
	lint ans = 0;
	while (!coup.empty() && !nocoup.empty()){

		if (coup.top().first + retcoup.top() < nocoup.top().first){
			lint tot = coup.top().first + retcoup.top();
			if (tot > m) break;
			m -= tot;
			past[coup.top().second] = true;
			retcoup.push(cow[coup.top().second][0] - cow[coup.top().second][1]);
			coup.pop();
			retcoup.pop();
		}
		else{
			lint tot = nocoup.top().first;
			if (tot > m) break;
			m -= tot;
			past[nocoup.top().second] = true;
			nocoup.pop();
		}
		ans++;
		while (!coup.empty() && past[coup.top().second]) coup.pop();
		while (!nocoup.empty() && past[nocoup.top().second]) nocoup.pop();
	}
	cout << ans;
	return 0;
}