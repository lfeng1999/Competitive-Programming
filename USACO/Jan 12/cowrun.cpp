#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
lint n, m, k;
lint cs[210];
char cmd[210];

lint calc(lint i, lint d, lint t1, lint t2){
	return (d + d*cs[i*8 + t1*4 + t2*2] + cs[i*8 + t1*4 + t2*2 + 1])%m;
}

bool solve_or(lint i, lint dist);
bool solve_and(lint i, lint dist, lint take){
	int x = rand()%2;
	return solve_or(i+1, calc(i, dist, take, x)) && solve_or(i+1, calc(i, dist, take, 1^x));
}

bool solve_or(lint i, lint dist){
	if (i == n){
		return (dist <= k || dist+k >= m);
	}
	return solve_and(i, dist, 0) || solve_and(i, dist, 1);
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (lint i=0; i<n; ++i){
		cin >> cmd[i];
	}
	for (lint i=0; i<8*n; ++i){
		cin >> cs[i];
	}
	lint cur = 0;
	for (lint i=0; i<n; ++i){
		if (solve_and(i, cur, 0)){//if left works
			cout << "T";
			cur = calc(i, cur, 0, (cmd[i] == 'T')?0:1);
		}
		else{
			cout << "B";
			cur = calc(i, cur, 1, (cmd[i] == 'T')?0:1);
		}
	}
	return 0;
}