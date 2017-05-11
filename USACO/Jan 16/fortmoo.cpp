#include <bits/stdc++.h>

using namespace std;

int down[210][210];
int n, m;
char grid[210][210];

int query(int r1, int r2, int c){
	return down[r2][c] - down[r1-1][c];
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("fortmoo.in","r",stdin);
	freopen("fortmoo.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=m; ++j){
			cin >> grid[i][j];
			down[i][j] = (grid[i][j] == 'X')?1:0;
		}
	}
	for (int j=1; j<=m; ++j){
		for (int i=2; i<=n; ++i){
			down[i][j] += down[i-1][j];
		}
	}
	int best = 0;
	for (int r1 = 1; r1<=n; ++r1){
		for (int r2 = r1; r2<=n; ++r2){
			int beg = 1;
			for (int ed = 1; ed<=m; ++ed){
				if (query(r1, r2, beg) != 0 || grid[r1][ed] == 'X' || grid[r2][ed] == 'X'){
					beg = ed+1;
					continue;
				}
				if (query(r1, r2, ed) == 0){
					best = max(best, (r2-r1+1)*(ed-beg+1));
				}
			}
		}
	}
	cout << best;


	return 0;
}