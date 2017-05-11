#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
inline int test(long long x, long long b){return (x >> b)&1;}

int dp[9][9][1 << 3][1 << 9][2], g[9][9], boxmsk[3], rowbit[9];

int solve(int r, int c, int bmsk, int cmsk, int rbit){
	if (r == 9){
		return __builtin_popcount(cmsk);
	}
	if (c == 9){
		if (rbit != 0) return 1e9;
		if (r%3 == 2){ //goes to next row
			if (bmsk != 0) return 1e9;
			return solve(r+1, 0, boxmsk[(r+1)/3], cmsk, rowbit[r+1]);
		}
		else{
			return solve(r+1, 0, bmsk, cmsk, rowbit[r+1]);
		}
	}
	int &ret = dp[r][c][bmsk][cmsk][rbit];
	if (ret != -1) return ret;
	ret = min(solve(r, c+1, bmsk, cmsk, rbit), 1 + solve(r, c+1, bmsk ^ (1 << (c/3)), cmsk^(1 << c), rbit^1));
	return ret;
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(dp, -1, sizeof(dp));
	for (int i=0; i<9; ++i){
		int x = 0;
		for (int j=0; j<9; ++j){
			char ch; cin >> ch;
			g[i][j] = ch - '0';
			x *= 2;
			x += g[i][j];
		}
		rowbit[i] = (__builtin_popcount(x)%2);
	}
	int colmsk = 0;
	for (int j=0; j<9; ++j){
		int cur = 0;
		for (int i=0; i<9; ++i){
			cur += g[i][j];
		}
		colmsk *= 2;
		colmsk += cur%2;
	}
	for (int i=0; i<3; ++i){
		int rmsk = 0;
		for (int j=0; j<3; ++j){
			rmsk *= 2;
			int tot = 0;
			for (int k=0; k<3; ++k){
				for (int l=0; l<3; ++l){
					tot += g[i*3+k][j*3+l];
				}
			}
			rmsk += tot%2;
		}
		boxmsk[i] = rmsk;
	}
	cout << solve(0, 0, boxmsk[0], colmsk, rowbit[0]);

	return 0;
}