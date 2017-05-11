#include <bits/stdc++.h>
//pruning brute force.... 
using namespace std;

typedef long long lint;

lint n, k, basic = 0, occ = 0;
vector<lint> c[100010];
vector<lint> d[100010];
lint f[100010], origbudget = 0, cost = 0;

void brute(lint i, lint budget){ //prune brute force to guarantee u find a solution each time
	if (occ >= k) return; // works lol
	i = upper_bound(f, f+i+1, budget) - f - 1; //next pos
	if (i == 0){
		occ++;
		return;
	}
	brute(i-1, budget);
	for (lint j=0; j<d[i].size() && budget >= d[i][j]; ++j){
		brute(i-1, budget - d[i][j]);
	}
}

void brute2(lint i, lint budget){
	i = upper_bound(f, f+i+1, budget) - f - 1;
	if (i == 0){
		cost += origbudget - budget; //cost of one cow
		occ++; 
		return;
	}
	brute2(i-1, budget);
	for (lint j=0; j<d[i].size() && budget >= d[i][j]; ++j){
		brute2(i-1, budget - d[i][j]);
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("roboherd.in","r",stdin);
	freopen("roboherd.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (lint i=1; i<=n; ++i){
		lint x; cin >> x;
		c[i].clear(); d[i].clear();
		for (lint qq=0; qq<x; ++qq){
			lint y; cin >> y;
			c[i].push_back(y);
		}
		sort(c[i].begin(), c[i].end());
		basic += c[i][0];
		if (x == 1){
			i--; n--;
			continue;
		}
		for (lint j=1; j<c[i].size(); ++j){
			d[i].push_back(c[i][j] - c[i][0]);
		}
	}
	if (k == 1){
		cout << basic; return 0;
	}
	sort(d+1, d+n+1);
	for (lint i=1; i<=n; ++i){
		f[i] = d[i][0];
	}
	lint L = 0, R = 1e13;
	while (L < R){
		lint mid = (L+R)/2;
		occ = 0;
		brute(n, mid);
		if (occ >= k)
			R = mid;
		else
			L = mid+1;
	}
	//L is minimum cost for that shit
	if (L > 0){
		occ = 0;
		origbudget = L-1;
		brute2(n, L-1); 
		cost += (k - occ)*L;
	}
	cout << cost + k*basic;
	return 0;
}