#include <bits/stdc++.h>

using namespace std;

int psum[31][31][31], g[31][31][31];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	while (true){
		memset(psum, 0, sizeof(psum));
		memset(g, 0, sizeof(g));
		int len; cin >> len;
		if (len == -1) return 0;
		for (int i=1; i<=len; ++i){
			for (int j=1; j<=len; ++j){
				for (int k=1; k<=len; ++k){
					cin >> g[i][j][k];
					psum[i][j][k] = g[i][j][k]+ psum[i][j][k-1];
				}
			}
		}
		for (int i=1; i<=len; ++i){
			for (int k=1; k<=len; ++k){
				for (int j=1; j<=len; ++j){
					psum[i][j][k] += psum[i][j-1][k];
				}
			}
		}
		for (int j=1; j<=len; ++j){
			for (int k=1; k<=len; ++k){
				for (int i=1; i<=len; ++i){
					psum[i][j][k] += psum[i-1][j][k];
				}
			}
		}
		int ans = -1e9;
		for (int x1=1; x1<=len; ++x1){
			for (int y1=1; y1<=len; ++y1){
				for (int x2=x1; x2<=len; ++x2){
					for (int y2=y1; y2<=len; ++y2){
						int curbest = 0;
						for (int z=1; z <= len; ++z){
							ans = max(ans, psum[x2][y2][z] - psum[x1-1][y2][z] - psum[x2][y1-1][z] + psum[x1-1][y1-1][z] - curbest);
							curbest = min(curbest, psum[x2][y2][z] - psum[x1-1][y2][z] - psum[x2][y1-1][z] + psum[x1-1][y1-1][z]);
						}
					}
				}
			}
		}
		cout << ans << '\n';
	}
	return 0;
}