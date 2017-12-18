#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

int n;
lint x[300010], d[300010], C, maxlen = 0;

bool valid(lint diam){
	if (diam >= maxlen) return true;

	lint maxsum = 1e18, minsum = -1e18, maxdif = 1e18, mindif = -1e18;
	priority_queue<pair<lint, int>> Q;
	Q.push(make_pair(-x[0] + d[0], 0));
	pair<lint,lint> bestadd = make_pair(-1e18, -1e18), bestsub = make_pair(2e18, 0);
	bool tocheck = false;
	for (int i=1; i<n; ++i){
		while (!Q.empty()){
			if (Q.top().first + x[i] + d[i] <= diam) break;
			int k = Q.top().second;
			if (x[k] + d[k] > bestadd.first + bestadd.second)
				bestadd = make_pair(x[k], d[k]);
			if (x[k] - d[k] < bestsub.first - bestsub.second)
				bestsub = make_pair(x[k], d[k]);
			Q.pop();
			tocheck = true;
		}
		if (tocheck){
			// cout << i << endl;
			maxsum = min(maxsum, diam + (bestsub.first - bestsub.second) + (x[i] - d[i]) - C);
			minsum = max(minsum, (bestadd.first + bestadd.second) + (x[i] + d[i]) + C - diam);
			mindif = max(mindif,  C - (bestsub.first - bestsub.second) + (x[i] + d[i]) - diam);
			maxdif = min(maxdif, diam - (bestadd.first + bestadd.second) + x[i] - d[i] - C);
		}
		Q.push(make_pair(-x[i] + d[i], i));
	}
	if (maxdif < mindif || maxsum < minsum) return false;
	for (int i=0; i<n; ++i){
		int L = i+1, R = n-1;
		while (L < R){
			int mid = (L+R)/2;
			if (x[mid] - x[i] >= mindif)
				R = mid;
			else
				L = mid+1;
		}
		int l1 = L;
		L = i+1, R = n-1;
		while (L < R){
			int mid = (L+R)/2;
			if (x[mid] + x[i] >= minsum)
				R = mid;
			else
				L = mid+1;
		}
		int l2 = L;

		int j = max(i+1, max(l1, l2));
		if (minsum <= x[i] + x[j] && x[i]+x[j] <= maxsum && mindif <= x[j] - x[i] && x[j] - x[i] <= maxdif) return true;
	}
	return false;
}

lint find_shortcut(int _n, int *_l, int *_d, int _c){
	n = _n;
	for (int i=0; i<n-1; ++i){
		x[i+1] = x[i] + _l[i];
	}
	for (int i=0; i<n; ++i){
		d[i] = _d[i];
	}

	lint toadd = -1e18;
	for (int i=0; i<n; ++i){

		maxlen = max(maxlen, x[i] + d[i] + toadd);
		toadd = max(toadd, -x[i] + d[i]);
	}
	C = _c;
	lint L = 0, R = 2e15;
	while (R > L){
		lint mid = (L+R)/2;
		if (valid(mid)) R = mid;
		else L = mid+1;
	}
	// cout << "VALID: " << valid(60) << " " << valid(80) << endl;
	return L;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int n;
	int a1[10], a2[10], c;
	cin >> n;
	for (int i=0; i<n-1; ++i) cin >> a1[i];
	for (int i=0; i<n; ++i) cin >> a2[i];
	cin >> c;
	cout << find_shortcut(n, a1, a2, c);

	return 0;
}