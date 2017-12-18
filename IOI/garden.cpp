#include <bits/stdc++.h>

using namespace std;

int nc, nr, nrose, k, g[255][255], psum[255][255];
int bestv[255][2], besth[255][2];

int area(int r1, int c1, int r2, int c2){
	return psum[r1][c1] - psum[r1][c2-1] - psum[r2-1][c1] + psum[r2-1][c2-1];
}
int min3(int a, int b, int c){return min(min(a, b), c);}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nc >> nr;
	cin >> nrose >> k;
	for (int qq=0; qq<nrose; ++qq){
		int c, r; cin >> c >> r;
		g[r][c]++;
	}
	for (int i=1; i<=nr; ++i){
		for (int j=1; j<=nc; ++j){
			psum[i][j] = g[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
		}
	}
	for (int i=0; i<255; ++i) bestv[i][0] = bestv[i][1] = besth[i][0] = besth[i][1] = 1e9;
	for (int r1=1; r1<=nr; ++r1){
		for (int c1=1; c1<=nc; ++c1){
			int c2 = 1;
			for (int r2 = r1; r2 >= 1; --r2){
				while (c2 + 1 <= c1 && area(r1, c1, r2, c2+1) >= k){
					c2++;
				}
				if (area(r1,c1,r2,c2) == k){
					int perim = (r1 - r2 + 1)*2 + (c1 - c2 + 1)*2;
					besth[r1][0] = min(besth[r1][0], perim);
					besth[r2][1] = min(besth[r2][1], perim);
					bestv[c1][0] = min(bestv[c1][0], perim);
					bestv[c2][1] = min(bestv[c2][1], perim);
				}
			}
		}
	}
	for (int r=1; r<=nr; ++r){
		besth[r][0] = min(besth[r][0], besth[r-1][0]);
		bestv[r][0] = min(bestv[r][0], bestv[r-1][0]);
	}
	for (int r=253; r>=1; --r){
		besth[r][1] = min(besth[r][1], besth[r+1][1]);
		bestv[r][1] = min(bestv[r][1], bestv[r+1][1]);
	}

	int ans = 2e9;
	for (int i=1; i<253; ++i){
		ans = min(ans, besth[i][0] + besth[i+1][1]);
		ans = min(ans, bestv[i][0] + bestv[i+1][1]);
	}
	if (ans > 1e9){
		cout << "NO";
	}
	else{
		cout << ans;
	}
	return 0;
}