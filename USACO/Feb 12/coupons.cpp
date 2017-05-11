#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cout << '>' << #x << ": " << x << endl
typedef long long lint;

struct Cow{
	lint p, c, id;
};
bool sortp(Cow a, Cow b){
	return a.p < b.p;
}
bool sortd(Cow a, Cow b){
	return (a.p - a.c) > (b.p - b.c);
}
bool sortc(Cow a, Cow b){
	return a.c < b.c;
}

lint n, k, m;
vector<Cow> cows;
bool past[50010];
lint lsum[50010], rsum[50010], psum[50010];
bool valid(lint ncow){
	lint tot = 0;
	if (ncow <= k){
		return psum[ncow-1] <= m;
	}
	fill(rsum, rsum+n, 1e17);
	lint rtot = 0;
	priority_queue<lint> Q;
	for (lint i = n-1; i>n-1-(ncow-k); --i){
		rtot += cows[i].p;
		Q.push(cows[i].p);
	}
	rsum[n-1-(ncow-k)+1] = rtot;
	for (lint i=n-1-(ncow-k); i>=0; --i){
		if (cows[i].p < Q.top()){
			rtot -= Q.top(); Q.pop();
			Q.push(cows[i].p);
			rtot += cows[i].p;
		}
		rsum[i] = rtot;
	}
	tot = 2e17;
	for (int i=k-1; i<n; ++i){

		tot = min(tot, (lsum[i] + rsum[i+1]));
		if (lsum[i] < 0){
			tot = -1e9;
			continue;
		}
	}
	return tot <= m;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("coupons.in","r",stdin);
	freopen("coupons.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(lsum, lsum+50010, 1e17);
	fill(rsum, rsum+50010, 1e17);
	cin >> n >> k >> m;
	for (lint i=0; i<n; ++i){
		lint p, c; cin >> p >> c;
		cows.push_back({p, c, i});
	}
	if (k == 0){
		sort(cows.begin(), cows.end(), sortp);
		lint tot = 0;
		for (int i=0; i<n; ++i){
			tot += cows[i].p;
			if (tot > m){
				cout << i;
				return 0;
			}
		}
		cout << n;
		return 0;
	}

	sort(cows.begin(), cows.end(), sortc);
	for (lint i=0; i<n; ++i){
		psum[i] = (i>0?psum[i-1]:0) + cows[i].c;
	}
	sort(cows.begin(), cows.end(), sortd);
	priority_queue<lint> Q;
	lint ltot = 0;
	for (lint i=0; i<k; ++i){
		ltot += cows[i].c;
		Q.push(cows[i].c);
	}
	lsum[k-1] = ltot;
	bool fker = false;
	for (lint i=k; i<n; ++i){
		if (cows[i].c < Q.top()){
			ltot -= Q.top(); Q.pop();
			ltot += cows[i].c;
			Q.push(cows[i].c);
			if (ltot < 0){
				fker = true;
			}
		}
		lsum[i] = ltot;
	}
	lint L = 0, R = n;
	while (L < R){
		lint mid = (L+R)/2 + 1;
		if (valid(mid)) 
			L = mid;
		else 
			R = mid - 1;
	}
	cout << L;
	return 0;
}