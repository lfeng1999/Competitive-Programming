#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

lint GCD(lint X, lint Y) {
    if (Y > X) swap(X, Y);
    lint tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}
lint nr, nc, nq;
lint g[110][110];

int main(){
	freopen("test.txt","r",stdin);
	freopen("test3.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc >> nq;
	if (nr > 100 || nc > 100){
		return 0;
	}
	for (lint qq=0; qq<nq; ++qq){
		lint typ; cin >> typ;
		if (typ == 1){
			lint r, c; lint val;
			cin >> r >> c >> val;
			g[r][c] = val;
		}
		else{
			lint r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			lint ret = 0;
			for (int i=r1; i<=r2; ++i){
				for (int j=c1; j<=c2; ++j){
					ret = GCD(ret, g[i][j]);
				}
			}
			cout << ret << endl;
		}
	}
	return 0;
}