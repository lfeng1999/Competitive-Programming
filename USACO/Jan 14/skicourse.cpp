#include <bits/stdc++.h>

using namespace std;

int R, C, dpr[110][110], dps[110][110];
bool isr[110][110], iss[110][110];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("skicourse.in","r",stdin);
	freopen("skicourse.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C;
	for (int i=1; i<=R; ++i){
		for (int j=1; j<=C; ++j){
			char ch; cin >> ch;
			isr[i][j] = (ch == 'R');
			iss[i][j] = (ch == 'S');
		}
	}
	int ans = 1e9;
	while (true){
		int best = -1;
		int bestr = -1, bestc = -1;
		memset(dpr, 0, sizeof(dpr)); memset(dps, 0, sizeof(dps));
		for (int r=R; r>=1; --r){
			for (int c=C; c>=1; --c){
				dpr[r][c] = isr[r][c]?min(dpr[r+1][c], min(dpr[r+1][c+1], dpr[r][c+1]))+1:0;
				dps[r][c] = iss[r][c]?min(dps[r+1][c], min(dps[r+1][c+1], dps[r][c+1]))+1:0;
				if (dpr[r][c] != dps[r][c]){ //not both blank
					int sqsize = max(dpr[r][c], dps[r][c]);
					if (sqsize > best){
						best = sqsize;
						bestr = r, bestc = c;
					}
				}
			}
		}
		if (best == -1) break;
		ans = min(ans, best);
		for (int r=bestr; r<bestr+best; ++r){
			for (int c=bestc; c<bestc+best; ++c){
				isr[r][c] = iss[r][c] = true;
			}
		}
	}
	cout << ans;
	return 0;
}