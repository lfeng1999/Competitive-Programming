#include <bits/stdc++.h>

using namespace std;

int nr, nc, budget, psum[510][510], g[510][510];

int area(int r1, int c1, int r2, int c2){
	return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nc >> nr >> budget;
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			cin >> g[i][j];
			psum[i][j] = g[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
		}
	}
	int ans = 0;
	for (int c1=1; c1<=nc; ++c1){
		for (int c2=c1; c2<=nc; ++c2){
			int r2 = 0;
			for (int r1=1; r1<=nr; ++r1){
				r2 = max(r2, r1 - 1);
				while (r2+1 <= nr && area(1, c1, nr, c2) + area(r1, 1, r2+1, nc) - area(r1, c1, r2+1, c2) <= budget){
					++r2;
				}
				if (r2 >= r1){
					ans = max(ans, (r2-r1+1)*nc + (c2-c1+1)*nr - (r2 - r1 + 1)*(c2 - c1 + 1));
				}
			}
		}
	}
	cout << ans;
	return 0;
}