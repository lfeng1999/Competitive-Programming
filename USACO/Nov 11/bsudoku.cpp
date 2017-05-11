#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
inline int test(long long x, long long b){return (x >> b)&1;}

int dp[3][610], g[10][10], nxt[610][610], tomsk[610];
bool invalid[610];

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<3; ++i) fill(dp[i], dp[i] + 610, 1e8);

	for (int i=0; i<9; ++i){
		for (int j=0; j<9; ++j){
			char ch; cin >> ch;
			g[i][j] = ch - '0';
		}
	}
	for (int i=0; i< (1 << 9); ++i){
		for (int j=0; j<(1 << 9); ++j){
			if (__builtin_popcount(j) % 2 == 1){
				nxt[i][j] = 1e8;
				invalid[j] = true;
				continue;
			}
			bitset<10> b1 = i, b2 = j;
			for (int k=0; k<10; ++k){
				if ((b1.test(k) && !b2.test(k)) || (!b1.test(k) && b2.test(k)))
					nxt[i][j]++;
			}
		}
	}
	for (int i=0; i<(1 << 9); ++i){
		tomsk[i] = 0;
		for (int j=0; j<9; ++j){
			if (test(i, j)){
				tomsk[i] ^= (1 << (j%3));
				tomsk[3+j/3] ^= (1 << (3+j/3));
			}
		}
	}
	for (int ndp = 0; ndp < 3; ++ndp){
		vector<pair<int,int>> v[3];
		for (int i=0; i<3; ++i){ //row
			int msk = 0;
			for (int j=2; j>=0; --j){ //row 
				for (int k=2; k>=0; --k){ //col
					msk *= 2;
					msk += g[i*3+j][ndp*3+k]; 
				}
			}
			//msk is original state
			//I got a mask now...
			for (int j=0; j < (1 << 9); ++j){
				if (invalid[j]) continue;
				v[i].push_back(make_pair(tomsk[j], nxt[msk][j])); //there's some dupes in tomsk[j] 
			}
		}
		for (auto &p1 : v[0]){
			for (auto &p2 : v[1]){
				for (auto &p3 : v[2]){
					int col = (p1.first % 8)^(p2.first % 8)^(p3.first % 8);
					if (col != 0) continue;
					int r1 = (p1.first >> 3), r2 = (p2.first >> 3), r3 = (p3.first >> 3);
					int row = r1 + (r2 << 3) + (r3 << 6);
					dp[ndp][row] = min(dp[ndp][row], p1.second + p2.second + p3.second);
				}
			}
		}
	}
	int ans = 1e9;
	for (int i=0; i<(1<<9); ++i){
		for (int j=0; j<(1<<9); ++j){
			ans = min(ans, dp[0][i] + dp[1][j] + dp[2][i^j]);
		}
	}
	cout << ans;

	return 0;
}