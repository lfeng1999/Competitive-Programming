#include <bits/stdc++.h>

using namespace std;

int nc, nr, nrose, k, g[255][255], psum[255][255];

int area(int r1, int c1, int r2, int c2){
	return psum[r1][c1] - psum[r1][c2-1] - psum[r2-1][c1] + psum[r2-1][c2-1];
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nc >> nr;
	cin >> nrose >> k;
	for (int qq=0; qq<nrose; ++qq){
		int c, r; cin >> c >> r;
		g[r][c]++;
	}
	for (int i=1; i<255; ++i){
		for (int j=1; j<255; ++j){
			psum[i][j] = g[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
		}
	}
	int best = 2e9;
	for (int r1=1; r1<=nr; ++r1){
		for (int c1=1; c1<=nc; ++c1){
			for (int r2 = r1; r2 <= nr; ++r2){
				for (int c2 = c1; c2 <= nc; ++c2){
					for (int r3=1; r3 <= nr; ++r3){
						for (int c3=1; c3 <= nc; ++c3){
							for (int r4=r3; r4<=nr; ++r4){
								for (int c4=c3; c4<=nc; ++c4){
									// valid rectangle
									bool isvalid = false;
									if (r1 > r4 || r3 > r2 || c1 > c4 || c3 > c2){
										if (area(r2, c2, r1, c1) == area(r4, c4, r3, c3) && area(r2, c2, r1, c1) == k){
											best = min(best, (r2 - r1 + 1)*2 + (c2 - c1 + 1)*2 + (r4 - r3 + 1)*2 + (c4 - c3 + 1)*2);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (best == 2e9){
		cout << "NO";
	}
	else{
		cout << best;
	}
	return 0;
}